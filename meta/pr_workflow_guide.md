# PR 運用ガイド

このリポジトリでは、エージェントが人間のレビュー待ちで止まらないように、GitHub PR を非同期のレビューキュー（赤ペン・suggestion の受け渡し場）として使う。実装・ドキュメント・検証の共通ルールは [AGENTS.md](../AGENTS.md)、コマンドの詳細は [scripts/INFO.md](../scripts/INFO.md) に従う。

## 基本方針

- 1 issue につき 1 ブランチ・1 PR を基本とする。PR 作成またはレビュー指摘への修正を push したら、人間の確認を待たずに完了報告して次の作業へ移ってよい。
- エージェントは PR をマージしない。最終承認とマージ（原則 Squash merge）は人間が行う。
- PR 上の CI（[verify.yml](../.github/workflows/verify.yml)）は `check`（`.scripts` の単体テストと `codex_self_check.py`）のみを実行する。judge verify と docs 公開は `master` へのマージ後に CI が担うため、変更対象に対するローカル verify は PR 作成・更新前に必ず通す。
- 並列 PR での競合を避けるため、`.competitive-verifier/docs/static/measure-dashboard.{html,json}` は明示的な依頼がない限り PR にコミットしない。`measure_verify.py` を実行した場合は結果だけ PR 本文へ記載し、dashboard 生成物の差分は戻す。
- `meta/doc_titles.yml` は変更が必要な場合のみ `python3 scripts/sync_doc_titles.py --write` で更新して含める。

## ブランチと worktree

- 新規 issue の作業は最新の `origin/master` から新しいブランチを切って始める（例: `issue/123-short-topic`、`feat/short-topic`、`fix/short-topic`）。
- 既存 PR の修正を始めるときは、作業前に `git fetch origin` を実行し、リモートブランチに最新のコミット（人間が GitHub UI で suggestion を適用したコミットなど）がないか確認してから取り込む。古いローカルブランチで上書きしない。
- 作業前後に `git status --short` を確認し、無関係なファイルや未追跡の生成物をコミットしない。

## PR の作成手順

1. `AGENTS.md` の変更種別ルールに従い、`python3 scripts/codex_self_check.py`、影響範囲の verify（`verify_changed.py` / `run_verify.py`）、必要なら性能計測（`measure_verify.py`）をローカルで通す。
2. push 前に `git diff origin/master...HEAD` を見直し、API の簡潔さ、不要なコメントの有無、意図しない dashboard 差分がないかを確認する。`_md/` を追加・更新した場合は [doc_example.md](doc_example.md) と照合し、自明な予防線、境界値だけの計算量分岐、証明調の長い補足、特殊ケースの使用例、既存ファイルとの書式・用語のずれを削る。
3. ブランチを `origin` へ push し、`gh pr create --base master` で PR を作成する。
4. PR タイトルは対象と変更内容が分かる短い日本語または英語にする。本文は次の構成を基準とし、不要な項目は省く。

```markdown
## 関連 issue

Closes #<番号>

## 変更概要

- 何をどう変えたか（API や設計上の判断を含む）

## 検証

- `python3 scripts/codex_self_check.py`: pass
- `python3 scripts/run_verify.py -j 8 test/...`: pass
- 未実行範囲があればその理由

## 性能

- 対象 test、最遅時間、比較対象（計測した場合のみ）

## レビュー観点

- 判断が分かれそうな点や特に見てほしい点（ある場合のみ）
```

issue の一部だけ対応する場合や調査 PR で自動クローズしたくない場合は、`Closes #` の代わりに `Refs #` を使う。

## レビュー指摘の回収と修正手順

PR に付いた赤ペン（インラインコメント・suggestion・レビュー本文）は `gh` CLI で漏れなく取得する。

### 1. 指摘の取得

PR の概要・通常コメントと、未解決のインラインレビュースレッドを確認する。

```bash
gh pr view <PR番号> --comments
gh api graphql \
  -F owner='{owner}' -F repo='{repo}' -F pr=<PR番号> \
  -f query='
query($owner: String!, $repo: String!, $pr: Int!) {
  repository(owner: $owner, name: $repo) {
    pullRequest(number: $pr) {
      reviewThreads(first: 100) {
        nodes {
          id
          isResolved
          path
          line
          comments(first: 20) {
            nodes {
              databaseId
              author { login }
              body
            }
          }
        }
      }
    }
  }
}'
```

`isResolved == false` のスレッドと、最新のレビュー本文・通常コメントをすべて確認対象とする。

### 2. 修正と同期

- `git fetch origin` のうえ対象 PR のブランチをチェックアウトし、リモートに新しいコミットがあれば取り込む。
- `suggestion` ブロックがある場合は、その意図を反映しつつ周囲のコード・テスト・docs との整合性を確認する。
- 設計や正しさの理由で指摘どおりにできない場合、または意図が曖昧な場合は、推測で押し切らず該当スレッドへ理由や確認事項を返信する。
- `origin/master` とのコンフリクト（`meta/doc_titles.yml` など）がある場合は `git rebase origin/master` で解消する。

### 3. 再検証と push

- 修正内容に応じて `codex_self_check.py`、対象 verify、必要な性能計測を再実行する。
- 通常はレビュー指摘対応を追加コミットとして push する（前回レビューからの差分を追いやすくするため）。`rebase` で履歴を書き換えた場合だけ `git push --force-with-lease` を使う。

### 4. 返信と報告

- 対応した各インラインスレッドに、対応内容とコミット短縮ハッシュを簡潔に返信する。

```bash
gh api repos/{owner}/{repo}/pulls/<PR番号>/comments/<comment_databaseId>/replies \
  -f body='対応しました (<commit>)。...'
```

- スレッドの Resolve は原則人間が行う（明示的な指示がある場合のみエージェントが Resolve する）。
- 全体として修正した内容・再検証結果・未解決の確認事項があれば簡潔に報告して完了とする。
