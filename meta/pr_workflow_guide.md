# ローカルレビュー・バッチ PR 運用ガイド

このリポジトリでは、GitHub issue を課題管理の正としつつ、個々の issue の実装・レビュー・赤ペン往復はローカルの Web レビューキュー（`scripts/local_review.py`）で完結させる。承認済みの変更を **1 issue = 1 コミット** でローカル統合ブランチ（`batch/*`）へ積み上げ、まとまった単位（作業時間単位や複数 issue 単位）で 1 本のバッチ PR として GitHub へ出荷する。

実装・ドキュメント・検証の共通ルールは [AGENTS.md](../AGENTS.md)、コマンドの詳細は [scripts/INFO.md](../scripts/INFO.md) に従う。

## 基本方針

- **issue 単位では `git push` や `gh pr create` を行わない。** 実装エージェントはローカルの `issue/<番号>-<topic>` ブランチに commit し、ローカルレビューキューへ提出した時点で次の作業へ移ってよい。
- レビュー状態とコメントは共通 Git ディレクトリ（`<git-common-dir>/local-review/state.json`）に保存され、すべての worktree から共有される。リポジトリの追跡ファイルは汚さない。
- 承認（`approved`）された issue ブランチは、ローカル統合ブランチ（例: `batch/YYYYMMDD`）へ `git merge --squash` により **1 issue = 1 コミット** として積み上げる。
- 最終出荷はバッチ単位で 1 本の PR を作成し、人間の承認後に **Rebase and merge**（または **Merge commit**）でマージする。Squash merge を使うと 1 issue = 1 コミットの履歴が潰れるため、バッチ PR では使わない。
- PR 上の CI（[verify.yml](../.github/workflows/verify.yml)）は `check` のみを実行し、judge verify と docs 公開は `master` へのマージ後に 1 回だけ走る。変更対象に対するローカル verify は各 issue の提出前に必ず通す。
- 並列作業での競合を避けるため、`.competitive-verifier/docs/static/measure-dashboard.{html,json}` は明示的な依頼がない限りコミットしない。`measure_verify.py` を実行した場合は結果だけレビューメタデータ・PR 本文へ記載し、dashboard 生成物の差分は戻す。
- `meta/doc_titles.yml` は変更が必要な場合のみ `python3 scripts/sync_doc_titles.py --write` で更新して含める。

## ブランチと worktree

- 新規 issue の作業は最新の `master`（必要に応じて `git fetch origin` 後の `origin/master`）から `issue/<番号>-<short-topic>` ブランチを切って始める。並列実行する実装エージェント間では極力別ドメインの issue を割り当てる。
- 作業前後に `git status --short` を確認し、無関係なファイルや未追跡の生成物をコミットしない。
- 統合が完了した `issue/*` ブランチと worktree は順次削除し、古いブランチを溜めない。

## 1. 実装とローカルレビュー提出（実装エージェント）

1. `AGENTS.md` の変更種別ルールに従い、`python3 scripts/codex_self_check.py`、影響範囲の verify（`verify_changed.py` / `run_verify.py`）、必要なら性能計測（`measure_verify.py`）をローカルで通す。
2. 提出前に `git diff master...HEAD` を見直し、API の簡潔さ、不要なコメントの有無、意図しない dashboard 差分がないかを確認する。`_md/` を追加・更新した場合は [doc_example.md](doc_example.md) と照合する。
3. ローカルブランチへ commit し、レビューキューへ登録する（`--issue` はブランチ名 `issue/<番号>-...` から自動抽出される）。

```bash
python3 scripts/local_review.py submit \
  --title "対象と変更内容の短いタイトル" \
  --summary "何をどう変えたか（API や設計判断を含む）" \
  --verify "python3 scripts/codex_self_check.py: pass" \
  --verify "python3 scripts/run_verify.py -j 8 test/...: pass" \
  --perf "対象 test、最遅時間、比較対象（計測時のみ）" \
  --notes "レビュー観点（ある場合のみ）"
```

issue の一部だけ対応する場合や調査変更で自動クローズしたくない場合は `--refs` を付ける（`Closes #` の代わりに `Refs #` が使われる）。

## 2. 非同期ローカルレビュー（人間）

ローカル Web レビュー UI を起動し、ブラウザで `http://127.0.0.1:8765/` を開く。

```bash
python3 scripts/local_review.py serve
```

- 左サイドバーのキューから `Ready` のブランチを選び、Unified / Split 差分で確認する。
- 行の `+` ボタンからインラインコメントや `Insert suggestion` を投稿できる。
- レビュー結果として **`Approve`** / **`Request Changes`** / **`Comment`** / **`Reject`** を記録する。
- 再提出されたブランチは Range セレクタの `Since last review` で前回レビュー以降の差分だけ確認できる。

## 3. レビュー指摘の回収と修正（オーケストレーター・実装エージェント）

オーケストレーターは `list` で `changes_requested` や `approved` のブランチを確認する。

```bash
python3 scripts/local_review.py list --status changes_requested --json
```

指摘が付いたブランチでは、未解決スレッドとレビュー本文を取得して対応する。

```bash
python3 scripts/local_review.py comments <branch> --json
```

1. 未解決スレッド（`suggestion` ブロック含む）と最新のレビュー本文をすべて確認する。
2. 設計や正しさの理由で指摘どおりにできない場合、または意図が曖昧な場合は、推測で押し切らず該当スレッドへ理由や確認事項を返信する。
3. 修正は追加コミットとして積み（`Since last review` で差分を追いやすくするため）、必要な `codex_self_check.py` / verify / 性能計測を再実行する。
4. 対応した各スレッドへ返信し、ブランチを再提出する。スレッドの Resolve は原則人間が行う（明示的な指示がある場合のみ `--resolve` を付ける）。

```bash
python3 scripts/local_review.py reply <branch> \
  --thread <thread_id> \
  --with-head-commit \
  --body "対応しました。..."

python3 scripts/local_review.py submit --branch <branch>
```

## 4. ローカル統合ブランチへの積み上げ（1 issue = 1 コミット）

`approved` になったブランチは、オーケストレーターまたは Web UI の `Batch Ship` タブからローカル統合ブランチ（例: `batch/YYYYMMDD`）へ統合する。

```bash
python3 scripts/local_review.py integrate <branch> --batch batch/YYYYMMDD --delete-branch
```

- 内部で一時 worktree 上に `git merge --squash` を実行し、件名・概要・`Closes #<番号>`（または `Refs #<番号>`）を含む 1 コミットを作成する。メインの作業ツリーは切り替えない。
- 競合ファイルが `meta/doc_titles.yml` のみの場合は、`python3 scripts/sync_doc_titles.py --write` で自動解消を試みる。
- 複数 issue が同じライブラリヘッダを触っていた場合は、統合後に影響範囲の verify を再実行する。

## 5. バッチ PR の出荷（作業時間単位・まとまった件数単位）

良いコミットが集まったタイミングで、バッチ全体を 1 本の PR として GitHub へ出荷する。

1. `git fetch origin` のうえ、必要なら `batch/YYYYMMDD` を最新の `origin/master` へ rebase する。
2. バッチ全体に対して `python3 scripts/codex_self_check.py` を実行する（複数 issue 間で共有ファイルを触っていた場合は `python3 scripts/verify_changed.py --base origin/master` も確認する）。
3. PR 本文を確認して push・PR 作成を行う。

```bash
python3 scripts/local_review.py prepare-pr --batch batch/YYYYMMDD
python3 scripts/local_review.py prepare-pr --batch batch/YYYYMMDD --create
```

4. 人間は GitHub 上でバッチ PR を確認し、**Rebase and merge**（または **Merge commit**）でマージする。エージェントは PR をマージしない。

不採用（`rejected`）になったブランチはバッチへ統合せず、必要に応じて GitHub issue に理由をコメントしてクローズまたは保留とし、ローカルブランチを破棄する。
