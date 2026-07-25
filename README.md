# library

[![Actions Status](https://github.com/firiexp/library/workflows/verify/badge.svg)](https://github.com/firiexp/library/actions)
[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://firiexp.github.io/library/)

競技プログラミング向けの C++17 ライブラリ。各モジュールは提出コードへ直接 `#include` する `.cpp` として管理する。

## 使い方

標準ライブラリ、`ll` / `uint` / `ull`、`INF<T>` などの共通定義は利用側で用意する。標準の構成は `snippets/template.cpp` を参照する。

```cpp
#include "datastructure/unionfind.cpp"
```

モジュールごとのAPI、前提条件、計算量は [GitHub Pages](https://firiexp.github.io/library/) に掲載する。

## 開発

検証ツールをインストールする。

```bash
pip3 install -r requirements-dev.txt
```

ライブラリの正しさは `oj-verify` で確認する。`codex_self_check.py` は docs 同期や repository policy を確認する高速な補助ツールであり、judge verify とは役割が異なる。

```bash
python3 scripts/codex_self_check.py
python3 scripts/verify_changed.py --list
oj-verify run -j 8 test/yosupo_unionfind.test.cpp
```

`python3 scripts/verify_changed.py` は working tree の直接・間接依存を調べ、self-check と影響する verify だけを実行する。`oj-verify all` は docs 生成も含むため、共通基盤の変更や統合確認に限定する。

## 性能計測

指定したverifyを実行し、measurement dashboardを更新する。

```bash
python3 scripts/measure_verify.py test/yosupo_unionfind.test.cpp
python3 -m http.server -d .verify-helper 8000
```

ダッシュボードは現在のテスト数と計測済み件数を分けて表示する。部分計測後に未計測のテストがあっても、過去の結果は保持する。

ローカルのtestcase cacheは自動削除しない。容量を確認して古い項目を整理するには次を使う。既定はdry-run。

```bash
python3 scripts/prune_verify_cache.py --max-size-gb 5
python3 scripts/prune_verify_cache.py --max-size-gb 5 --apply
```

詳細なコマンドは `scripts/INFO.md` を参照する。
