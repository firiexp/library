## verify

検証基盤は `competitive-verifier==4.2.2` を使う。環境を作る手順は README を参照する。

```bash
python3 scripts/codex_self_check.py
python3 scripts/verify_changed.py --list
python3 scripts/verify_changed.py
python3 scripts/verify_changed.py --base origin/master --list
python3 scripts/run_verify.py -j 8 test/yosupo_unionfind.test.cpp
```

`verify_changed.py` は staged / unstaged / untracked file と quoted include の直接・間接依存から対象を選び、self-check と検証を実行する。`run_verify.py` は未追跡の C++ テストも含めて依存解析し、competitive-verifier の入力 JSON を生成する。コンパイラ設定、検証スクリプト、依存パッケージの変更時は全件が対象になる。

`-j` は test file の同時実行数で、既定値は8。各 test のケースは逐次実行する。stack size はスクリプト内で上限まで引き上げる。成功済みでソース・依存・設定・コンパイラ・testcase が変わっていない test は hash 判定で再実行を省く。`--force` で強制実行できる。

通常の verify と CI は `-DLOCAL -UNDEBUG` を指定し、ライブラリ内・自己テスト内の `assert` を有効にする。提出用テンプレートは `-DLOCAL` があるときだけ `assert` を有効にする。

```bash
python3 scripts/run_verify.py --list
python3 scripts/run_verify.py --no-download test/yosupo_unionfind.test.cpp
python3 scripts/run_verify.py --force -j 8
python3 scripts/build_verify_docs.py --require-success
```

`--no-download` は既存 testcase cache だけを使う。cache がない問題は失敗する。通常実行は testcase を取得するため、yukicoder では `YUKICODER_TOKEN` が必要になる。Library Checker の問題リポジトリも通常実行時に同期する。

全件検証と docs 生成は別コマンドである。`build_verify_docs.py` は Jekyll 用ソースを `.competitive-verifier/_jekyll/` に生成し、既存の `_md/`、タイトル、結合済みソース、コピー機能、計測ダッシュボードを取り込む。`--require-success` は不足・古い・失敗した結果がある場合に停止する。省略時は未検証として表示し、成功扱いにはしない。

ライブラリの目次はディレクトリごとに1階層の折りたたみで表示する。表示名は `.competitive-verifier/docs/_config.yml` の `directory_titles` で管理し、キーには末尾の `/` を含む実ディレクトリを指定する。表示名は短い名詞句とし、使い方は各ファイルの docs に書く。ファイルを移動するときは include、対応する `_md` の配置と `documentation_of`、`meta/doc_titles.yml` のパスも更新する。

GitHub Actions は4分割で検証し、結果を統合して docs を生成する。既定ブランチ（現在は `master`）への push で GitHub Pages に公開する。リポジトリの Settings → Pages → Source は **GitHub Actions** を選ぶ。`GH_PAT` は不要で、`GITHUB_TOKEN` と `YUKICODER_TOKEN` を使う。テストデータは各ジョブで取得し、前回の検証結果だけを cache する。

`.competitive-verifier/result.json` は検証結果、`verify-files.json` は依存・実行定義である。生成物は git 管理しない。docs のソースと公開する計測結果は git 管理する。旧 `.verify-helper/cache/` は自動削除しない。

`scripts/*.py` は公開コマンドの薄い wrapper、本体は `.scripts/*_impl.py` に置く。resolver は固定バージョンの competitive-verifier の C++ 解析・結合処理を利用するため、バージョン更新時は統合テストも実行する。

## repository check

通常は高速な policy / docs 同期 / dashboard HTML 構造検査を使う。dashboard の renderer / asset / screenshot を変更した場合は視覚回帰も実行する。

```bash
python3 -m unittest discover -s .scripts -p 'test_*.py'
python3 scripts/codex_self_check.py
python3 scripts/codex_self_check.py --full
```

`_md/**/*.md` ではコード・数式内も含めて Liquid の開始記号を検査する。C++ の入れ子の初期化子は `{ {1, 2}, {3, 4}}` のように開き波括弧を離す。連続した記号が必要なら Liquid の `raw` / `endraw` タグで囲む。

## 性能計測

```bash
python3 scripts/measure_verify.py test/yosupo_unionfind.test.cpp
python3 scripts/measure_verify.py --no-download test/yosupo_predecessor_problem_fast_set.test.cpp
python3 -m http.server -d .competitive-verifier 8000
```

計測は成功済みの test も必ず再実行する。比較用の既定は `-j 1 --compile-jobs 1` で、ケースも逐次実行する。`-j` を増やした計測値は他のテストの負荷を受ける。

計測対象は `PROBLEM` を指定したテストで、`-ULOCAL -DNDEBUG` を追加して `assert` を無効にする。デバッグ用 verify とは実行ファイルと実行環境の記録を分ける。自己テスト（`STANDALONE`）は条件式内の処理まで消えることを防ぐため計測から除外し、明示指定した場合も skip を表示する。自己テストの確認には `run_verify.py` を使う。

ダッシュボードは competitive-verifier の結果 JSON から各ケースの時間・メモリ・成否を読み取る。コンパイル時間と実行時間を分けて記録する。失敗時はコマンドも非ゼロで終了する。

生成先は以下の4ファイルである。

- `.competitive-verifier/measure-dashboard.html`
- `.competitive-verifier/measure-dashboard.json`
- `.competitive-verifier/docs/static/measure-dashboard.html`
- `.competitive-verifier/docs/static/measure-dashboard.json`

部分計測では未選択の過去の結果を保持する。ブラウザで `http://127.0.0.1:8000/measure-dashboard.html` を開くと、計測中は2秒ごとに更新される。最遅・平均時間、メモリ、ケースごとの結果、コンパイル・検証ログを確認できる。

```bash
python3 scripts/generate_verify_dashboard.py --render-only
python3 scripts/prune_verify_cache.py --max-size-gb 5
python3 scripts/prune_verify_cache.py --max-size-gb 5 --apply
```

cache 整理は既定で dry-run、`--apply` で削除する。AOJ / yukicoder は問題単位、Library Checker は問題リポジトリ全体が1項目になる。削除後は通常実行で再取得する。
