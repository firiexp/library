
## verify

通常の verify は以下でまとめて実行できる。

```bash
python3 scripts/codex_self_check.py
oj-verify all
```

一括 verify をラップする専用スクリプトは置かず、`oj-verify all` をそのまま使う。

個別には以下を使う。

```bash
python3 scripts/codex_self_check.py
oj-verify run test/aoj0273.test.cpp
```

性能計測と可視化は verify とは分け、以下を使う。

```bash
python3 scripts/measure_verify.py
python3 scripts/measure_verify.py test/aoj0273.test.cpp
python3 scripts/measure_verify.py -j 16 --oj-jobs 1
```

`python3 scripts/measure_verify.py test/...` は指定した test だけを対象に measurement dashboard を更新する。ローカルでの改善サイクル用。

`-j` は同時に測る test 数で、既定値は論理コア数。`--oj-jobs` は各 `oj test` に渡す `-j` で、既定値は `1`。

`python3 scripts/run_verify.py` は後方互換のため残してあり、内部で `scripts/measure_verify.py` を呼ぶ。

## verify measurement dashboard

measurement dashboard は `oj test` の出力から各 verify テストの実行時間を集計し、JSON を逐次更新しながらブラウザで見られる HTML を生成する。

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
