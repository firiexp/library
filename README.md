# library

[![Actions Status](https://github.com/firiexp/library/workflows/verify/badge.svg)](https://github.com/firiexp/library/actions)
[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://firiexp.github.io/library/)

競技プログラミング向けの C++17 ライブラリ。

各ライブラリの使い方、前提条件、計算量は [GitHub Pages](https://firiexp.github.io/library/) で確認できる。

## 使い方

各ライブラリは [snippets/template.cpp](snippets/template.cpp) に貼り付けて使うことを想定している。
テンプレートには標準ライブラリ、`ll` / `uint` / `ull`、`INF<T>` などの共通定義と、高速入出力の `din` / `dout` が含まれる。
別のテンプレートを使う場合は、これらの定義が足りずコンパイルエラーになることがある。

### GitHub Pages からコピーする

1. [テンプレートのページ](https://firiexp.github.io/library/snippets/template.cpp) からコードをコピーし、`main.cpp` として保存する。
2. 使いたいライブラリのページからコードをコピーし、テンプレートの共通定義の後、`main` 関数の前に貼り付ける。依存先がある場合は、依存先も含む `bundled` のコードを使う。
3. `main` 関数に問題を解く処理を書く。

## コンパイルとデバッグ

テンプレートは通常 `assert` を無効にする。手元でデバッグするときは、コンパイル時に `-DLOCAL` を付けると有効になる。

```bash
g++ -std=c++17 -O2 -DLOCAL main.cpp -o main-debug
g++ -std=c++17 -O2 main.cpp -o main
```

