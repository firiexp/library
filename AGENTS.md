# Repository Guidelines

## Working Principles

このリポジトリは競技プログラミング向け C++17 ライブラリである。検証量は変更リスクに合わせ、短い改善サイクルを優先する。

- 作業前後に `git status --short` と差分を確認し、既存の未コミット変更を保持する。
- 既存 API との後方互換性の維持は不要。改善に必要な API・型の変更は、関連コード・verify・docs をまとめて更新する。互換性維持だけを理由に追加実装やユーザーへの確認をしない。
- コマンド一覧を一律に全部実行しない。変更箇所、include 関係、失敗時の影響から必要な検証を選ぶ。
- 反復中は fast self-check と対象 verify を使う。`python3 scripts/run_verify.py` は通常の反復コマンドにしない。
- 検証済みの内容を変更していなければ、同じ重いコマンドを繰り返さない。
- 失敗した検証は原因を切り分ける。ネットワーク、judge、既存変更による失敗を実装不良と混同しない。
- 改善候補の調査や issue 作成では [issue 作成ガイド](meta/issue_creation_guide.md) を読み、採用基準・調査手順・本文の形式に従う。

## Project Structure

- ライブラリ: `datastructure/`, `graph/`, `math/`, `string/`, `tree/`, `geometry/`, `flow/`, `fps/`, `util/`
- verify: `test/*.test.cpp`
- コンポーネント別 docs: `_md/<domain>/*.md`
- docs タイトルの正: `meta/doc_titles.yml`
- 開発スクリプトの公開入口: `scripts/`
- Python スクリプトの実装: `.scripts/`
- verify metadata / 生成 docs: `.competitive-verifier/`

新しいライブラリは最も具体的な domain に置き、対応する `_md/<domain>/*.md` と少なくとも1本の verify を追加する。

検証対象は C++ ファイルに限定する。Python の本体は `.scripts/*_impl.py` に置き、`scripts/*.py` は既存形式の薄い wrapper に保つ。

## Documentation Style

- `README.md` は GitHub Pages や clone したコードからライブラリを使う人向けの説明に限定する。AI 向けの開発方針は `AGENTS.md`、検証・計測ツールの詳細は [scripts/INFO.md](scripts/INFO.md) に置く。
- `_md/**/*.md` は簡潔な常体で書く。
- 見出しは `## 説明`、`## できること`、`## 使い方` を優先し、必要なら `## 例`、`## 実装上の補足` を足す。
- API は短い箇条書きで、何をするかと失敗時の返り値がすぐ分かる形にする。
- 文体と構成は `_md/tree/dynamic_tree/link_cut_tree.md` を基準にする。
- 数式は MathJax を使う。インラインは `$...$`、別行は `$$...$$` とし、体裁は `meta/doc_example.md` に合わせる。
- `.cpp` の `@brief` を直接タイトル管理に使わず、`meta/doc_titles.yml` を編集する。
- タイトル変更後は `python3 scripts/sync_doc_titles.py` で確認し、必要なら `--write` で反映する。
- タイトルは短い日本語主体とし、必要な英語だけ括弧で補う。

## Coding Style

- C++17、4 spaces、tab なし。周辺コードの形式に合わせる。
- コードコメントは書かない。
- ファイル名は lowercase、空白なし、`.cpp` とする。
- interface は小さく再利用可能に保ち、問題固有ロジックを library に入れない。
- 利用側の記述量を重視する。成功が保証される問題では返り値をそのまま使える API を優先し、失敗を空配列や番兵値で自然に表せるならそれを使う。`optional` を一律には採用しない。
- 入出力は原則 `util/fastio.cpp` の `Scanner` / `Printer` を使う。
- `assert` の条件式は無効時には評価されないため、必要な更新処理を入れない。
- test 名は `<judge>_<problem>.test.cpp` または `yosupo_<task>.test.cpp` を基本とする。
- test の先頭付近に `#define PROBLEM "<url>"` または `#define STANDALONE` を1つ置く。自己テストは STANDALONE とし、A+B の入出力を付けない。
- 利用可能な judge は Library Checker、yukicoder、AOJ。AtCoder は使わない。

問題用の verify はその問題を解く処理だけを書く。固定ケース・乱択・愚直解との比較などの自己テストは `test/yosupo_aplusb_<component>.test.cpp` に分離し、既に対応する自己テストがあればそこへ追加する。ファイル名の `yosupo_aplusb_` は従来の命名を引き継いでいるが、`STANDALONE` の自己テストは judge に接続せず1回だけ実行する。

## Fast Development Commands

コマンドの詳細、検証キャッシュ、docs 生成、性能計測の仕様は [scripts/INFO.md](scripts/INFO.md) を参照する。

依存関係は必要なときだけ pinned requirements から入れる。

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r requirements-dev.txt
```

通常の静的検査は高速版を使う。dashboard の HTML 構造検査は高速版に含まれる。

```bash
python3 scripts/codex_self_check.py
```

現在の差分から直接・間接に影響する verify を確認する。

```bash
python3 scripts/verify_changed.py --list
python3 scripts/verify_changed.py --base origin/master --list
```

影響範囲が妥当なら self-check と対象 verify をまとめて実行できる。

```bash
python3 scripts/verify_changed.py
```

反復中に1本または少数を明示する場合は `-j 8` を目安にする。これは test file を並列実行する。

```bash
python3 scripts/run_verify.py -j 8 test/<name>.test.cpp
```

## Validation by Change Type

- docs / `meta/doc_titles.yml` のみ: fast self-check。judge verify は不要。
- library: include 関係を確認し、変更 API・境界値・失敗系を覆う verify を選ぶ。新規アルゴリズムには verify を追加する。
- test のみ: fast self-check と変更した test。共通 library を触っていなければ全件は不要。
- `scripts/` / `.scripts/`: fast self-checkに加え、変更した CLI の `--help`、list/dry-run、代表的な非破壊実行を確認する。
- dashboard の asset / renderer / screenshot script: `python3 scripts/codex_self_check.py --full` を使う。Chromium がない環境では skip を明記する。
- 共通基盤 (`util/fastio.cpp` など)、compiler 設定、広い include graph: 影響テスト一覧を確認し、代表 verify で早く失敗を検出した後、必要なら全件へ進む。

編集が一まとまりになった時点で self-check を1回通してから judge verify へ進む。途中で self-check 対象を変えていなければ、各 verify の前に繰り返す必要はない。

## Full Verification

`python3 scripts/run_verify.py` は全 test を検証するため時間がかかる。docs は `python3 scripts/build_verify_docs.py` で別途生成する。次の場合に限定する。

- ユーザーが全件確認を求めた。
- 共通基盤や build / verify 設定を変更し、対象の限定が安全でない。
- CI が使えず、統合前の全件結果が必要である。

```bash
python3 scripts/codex_self_check.py
python3 scripts/run_verify.py -j 8
python3 scripts/build_verify_docs.py --require-success
```

PR 前という理由だけでローカル全件を必須にしない。CI が全件を担当する場合は、ローカルでは影響テストと未実行範囲を報告する。

## Performance Checks

新規アルゴリズム、計算量・メモリ配置・hot path を変えた場合は、代表的な大入力で性能を確認する。docs、test harness、コメント、明らかに性能非依存の変更では不要。

```bash
python3 scripts/measure_verify.py test/<name>.test.cpp
```

- measurement は dashboard 生成物を更新するため、更新が意図した差分か確認する。
- 性能比較では `-j 1` の既定を保つ。`python3 scripts/run_verify.py -j 8` の並列 wall time を性能値として使わない。
- 最遅ケース 1 秒以下は目標であり、judge や問題特性を無視した絶対条件ではない。既存値からの regression と明らかな定数倍改善を優先する。
- 計測した test、最遅時間、比較対象を報告する。

dashboard は次で確認できる。

```bash
python3 -m http.server -d .competitive-verifier 8000
```

## Handoff

完了時は変更概要、実行した検証と結果、性能値、未実行の重い検証とその理由を簡潔に報告する。AC だけでなく warning、skip、既存失敗も区別する。
