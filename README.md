# library

[![Actions Status](https://github.com/firiexp/library/workflows/verify/badge.svg)](https://github.com/firiexp/library/actions)
[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://firiexp.github.io/library/)

競技プログラミング向けの C++17 ライブラリ。各モジュールは提出コードへ直接 `#include` する `.cpp` として管理する。

## 使い方

標準ライブラリ、`ll` / `uint` / `ull`、`INF<T>` などの共通定義は利用側で用意する。標準の構成は `snippets/template.cpp` を参照する。

テンプレートは通常、全ヘッダーの前で `NDEBUG` を定義して `assert` を無効にする。手元のデバッグではコンパイル時に `-DLOCAL` を付けると有効になる。`LOCAL` はソースに定義せず、提出前の動作確認・性能計測では付けない。テンプレートを使わない場合は、提出コードの全ヘッダーの前に `#define NDEBUG` を置く。

```bash
g++ -std=c++17 -O2 -DLOCAL main.cpp -o main-debug
g++ -std=c++17 -O2 main.cpp -o main
```

`assert` の条件式は無効時には評価されないため、必要な更新処理を入れない。

```cpp
#include "datastructure/unionfind.cpp"
```

モジュールごとのAPI、前提条件、計算量は [GitHub Pages](https://firiexp.github.io/library/) に掲載する。

## 開発

検証ツールをインストールする。

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r requirements-dev.txt
```

ライブラリの正しさは `competitive-verifier` で確認する。`codex_self_check.py` は docs 同期や repository policy を確認する高速な補助ツールであり、judge verify とは役割が異なる。

通常の verify と CI は `-DLOCAL -UNDEBUG` でコンパイルし、ライブラリ内と自己テスト内の `assert` を有効にする。

```bash
python3 scripts/codex_self_check.py
python3 scripts/verify_changed.py --list
python3 scripts/run_verify.py -j 8 test/yosupo_unionfind.test.cpp
```

`python3 scripts/verify_changed.py` は working tree の直接・間接依存を調べ、self-check と影響する verify だけを実行する。全件検証は `python3 scripts/run_verify.py`、docs 生成は `python3 scripts/build_verify_docs.py` で別々に実行する。全件検証は共通基盤の変更や統合確認に限定する。

CI と `run_verify.py` は、テスト本体・間接 include・検証設定・コンパイラのハッシュが前回の成功結果と一致するテストを再利用する。変更・追加・未成功のテストだけ、テストデータの取得と検証を行う。CI の分割先はファイル名で固定し、テストの追加・削除で既存テストのキャッシュが外れないようにする。一部が失敗した場合も、完了した成功結果を次回に引き継ぐ。初回やキャッシュ消失時、検証基盤・コンパイラの変更時は全件を実行する。

変更のないテストでは judge 側のテストデータ更新を確認しない。データを更新して成功済みのテストも再実行する場合は `python3 scripts/run_verify.py --force` を使う。CI では Actions の手動実行で `force` を有効にする。docs は再利用した結果も含め、現在のソースに対する成功を確認してから生成する。

問題用の verify はその問題を解く処理だけを書く。固定ケース・乱択・愚直解との比較などの self-test は、`test/yosupo_aplusb_<component>.test.cpp` に分離する。既に対応する self-test があればそこへ追加する。自己テストには `#define STANDALONE` を指定し、A+B の入出力は書かない。ファイル名の `yosupo_aplusb_` は従来の命名を引き継いでいるが、実行時は judge に接続せず1回だけ実行する。問題用のテストには `#define PROBLEM "<url>"` を指定する。

## 性能計測

指定した問題用の verify を `assert` 無効で実行し、measurement dashboard を更新する。計測では `-ULOCAL -DNDEBUG` を追加する。自己テスト（`STANDALONE`）は計測対象から除外し、通常の verify で確認する。

```bash
python3 scripts/measure_verify.py test/yosupo_unionfind.test.cpp
python3 -m http.server -d .competitive-verifier 8000
```

ダッシュボードは現在の問題用テスト数と計測済み件数を分けて表示する。部分計測後に未計測のテストがあっても、過去の結果は保持する。以前の assert 有効時の結果も残るため、比較するテストは再計測する。

ローカルのtestcase cacheは自動削除しない。容量を確認して古い項目を整理するには次を使う。既定はdry-run。

```bash
python3 scripts/prune_verify_cache.py --max-size-gb 5
python3 scripts/prune_verify_cache.py --max-size-gb 5 --apply
```

詳細なコマンドは `scripts/INFO.md` を参照する。
