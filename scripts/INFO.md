
## verify

通常の改善サイクルでは、まず高速な repository check と影響範囲の確認を行う。

```bash
python3 scripts/codex_self_check.py
python3 scripts/verify_changed.py --list
```

`verify_changed.py` は working tree の staged / unstaged / untracked file を集め、quoted include を再帰的にたどって直接・間接に影響する `test/*.test.cpp` を選ぶ。branch 上の commit も含める場合は base を指定する。

```bash
python3 scripts/verify_changed.py --base origin/main --list
```

一覧が妥当なら、fast self-check と選択された verify をまとめて実行する。

```bash
python3 scripts/verify_changed.py
```

個別には以下を使う。

```bash
python3 scripts/codex_self_check.py
oj-verify run -j 8 test/aoj0273.test.cpp
```

`-j 8` は全 test file の同時実行数ではなく、verification timestamp の依存解析と各 `oj test` の testcase 並列数に使われる。性能値を取るときは後述の measurement を `--oj-jobs 1` で使う。

`oj-verify all` は judge verify の後に docs 全体も生成する。共通基盤・compiler 設定など影響を限定できない変更、または統合確認でのみ使う。

```bash
python3 scripts/codex_self_check.py
oj-verify all -j 8
```

再帰が深い verify をローカルで回すときは、stack size を上げて実行するとよい。

```bash
python3 scripts/codex_self_check.py
scripts/with_unlimited_stack.sh oj-verify run -j 8 test/yosupo_scc.test.cpp
scripts/with_unlimited_stack.sh oj-verify all -j 8
```

通常の self-check は dashboard の HTML contract までを含む高速版である。dashboard renderer / asset / screenshot capture を変更したときだけ視覚回帰も実行する。

```bash
python3 scripts/codex_self_check.py --full
```

`scripts/*.py` は公開 command を保つ薄い wrapper で、本体は `.scripts/*_impl.py` に置く。`oj-verify docs` が可視 Python file の import graph を解析する固定コストを避けるためである。

性能計測と可視化は verify とは分け、以下を使う。

```bash
python3 scripts/measure_verify.py
python3 scripts/measure_verify.py test/aoj0273.test.cpp
python3 scripts/measure_verify.py -j 16 --oj-jobs 1
```

計測も同様に wrapper 経由でよい。

```bash
scripts/with_unlimited_stack.sh python3 scripts/measure_verify.py test/yosupo_scc.test.cpp
```

`python3 scripts/measure_verify.py test/...` は指定した test だけを対象に measurement dashboard を更新する。ローカルでの改善サイクル用。

`-j` は同時に測る test 数で、既定値は論理コア数。`--oj-jobs` は各 `oj test` に渡す `-j` で、既定値は `1`。

`python3 scripts/run_verify.py` は後方互換のため残してあり、内部で `scripts/measure_verify.py` を呼ぶ。

verify testcase cache は自動削除しない。現在の容量と削除候補を確認するには以下を使う。

```bash
python3 scripts/prune_verify_cache.py --max-size-gb 5
python3 scripts/prune_verify_cache.py --max-size-gb 5 --apply
python3 scripts/prune_verify_cache.py --all --apply
```

既定は dry-run。`--apply` を付けたときだけ、最終更新が古い問題のcacheから削除する。

## verify measurement dashboard

measurement dashboard は `oj test` の出力から各 verify テストの実行時間を集計し、JSON を逐次更新しながらブラウザで見られる HTML を生成する。

部分計測では既存結果を保持し、現在存在するtest数と計測済み件数を別々に表示する。未計測が残る場合は `measured` が警告表示になる。

生成先:

- `.verify-helper/measure-dashboard.html`
- `.verify-helper/measure-dashboard.json`
- `.verify-helper/docs/static/measure-dashboard.html`
- `.verify-helper/docs/static/measure-dashboard.json`

既定の `python3 scripts/measure_verify.py` / `python3 scripts/generate_verify_dashboard.py --render-only` は docs デプロイ用の `.verify-helper/docs/static/` にも同じ内容を同期する。トップページの `verify measurement dashboard` リンクから開ける。

ローカルで見る手順:

```bash
python3 -m http.server -d .verify-helper 8000
python3 scripts/measure_verify.py
```

先に `http://127.0.0.1:8000/measure-dashboard.html` を開いておけば、`python3 scripts/measure_verify.py` の実行中に 2 秒ごとに自動更新される。更新中も選択中 test と detail tab は維持する。

単体確認なら次でよい。

```bash
python3 -m http.server -d .verify-helper 8000
python3 scripts/measure_verify.py test/aoj0273.test.cpp
```

画面では以下を見られる。

- テストごとの最遅ケース時間
- 平均時間
- メモリ使用量
- 選択中 test のケースごとの実行時間
- 選択中 test の `oj test` 生ログ
