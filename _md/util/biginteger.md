---
title: 多倍長整数(BigInteger)
documentation_of: //util/biginteger.cpp
date: 2026-03-20
category: 数学
tags: 数学
---

## 説明
符号付き多倍長整数を扱う。
`BigInteger` は $10^8$ 基数、`HexBigInteger` は $2^{32}$ 基数の little endian limb 列を持つ。
limb は 32 bit、基礎演算の中間値は 64 bit で扱う。符号処理と符号なしの桁配列演算を分離している。

## できること
- `BigInteger()`
  `0` を作る
- `BigInteger(long long x)`
  `x` から作る
- `BigInteger(const string& s, int base = 10)`
  `s` から作る。`base` は $2$ 以上 $36$ 以下。不正な文字列なら assertion failure
- `x.assign(const string& s, int base = 10)`
  `s` を代入する。成功なら `true`、不正な文字列なら値を `0` にして `false`
- `HexBigInteger(const string& s)`
  16 進文字列から作る
- `x.is_zero()`
  `x == 0` なら `true`
- `x.to_string(int base = 10)`
  `base` 表記の文字列にする。英字は小文字で返す
- `x += y`, `x -= y`, `x *= y`, `x /= y`, `x %= y`
  四則演算と余りを計算する。`/` は 0 方向に切り捨て、`%` は dividend と同符号の余りを返す。0 除算は assertion failure
- `x << k`, `x >> k`
  $k \ge 0$ に対して 2 の冪でのシフトを行う。右シフトは負の無限大方向に丸める
- `x < y`, `x <= y`, `x > y`, `x >= y`, `x == y`, `x != y`
  比較する
- `divmod(x, y)`
  `/` と `%` の結果を同時に返す。0 除算は assertion failure
- `floor_divmod(x, y)`
  商を負の無限大方向に丸め、divisor と同符号の余りを返す。0 除算は assertion failure

## 使い方
`Scanner` と `Printer` から直接入出力できる。

```cpp
BigInteger a, b;
sc.read(a, b);
auto [q, r] = divmod(a, b);
pr.println(q, r);
```

10 進中心なら `BigInteger`、16 進中心なら `HexBigInteger` を使う。
異なる基数の文字列も扱えるが、主基数以外の変換には追加コストがかかる。

## 実装上の補足

乗算は入力の短辺と面積で筆算、Karatsuba 法、2 素数の exact NTT を切り替える。
Karatsuba 法は長辺が短辺の 2 倍以下の中規模入力に使う。切り替えは 10 進版と 16 進版で分ける。
NTT では各 limb を $10^4$ または $2^{16}$ 基数の 2 桁に分割する。必要な変換長は $2^{21}$ 以下とする。

除算は除数が 1 limb なら線形走査、小規模や除数・商が短い場合は Knuth 法を使う。
中規模では Burnikel–Ziegler 法で除算を再帰的に分割し、部分的な積に高速乗算を使う。
大規模では整数の Newton 法で逆数を作り、ブロックごとに商と余りを求める。
逆数の精度は除数の半分程度に抑え、各ブロックで再利用する。商が短ければ、さらに精度を落とす。
浮動小数点の初期推定や、補正失敗時の筆算へのフォールバックは使わない。

基数を $\beta$、正規化した $n$ limb の除数を $b$ とすると、逆数 $R$ は次を満たす。

$$
0 \le \frac{\beta^{2n}}{b} - R < 2
$$

小さい逆数は筆算で求める。それ以外では $h=\lceil n/2\rceil+1$ とし、除数の上位 $h$ limb の逆数から始める。
その逆数を 4 減らして $\beta^{n-h}$ 倍した初期値 $X$ は、真の逆数以下で、誤差は $6\beta^{n-h}$ 未満になる。
Newton 更新を切り捨てて行った後の誤差は $1+36\beta^{n-2h}<2$ となるため、各段階の乗算は 2 回で済む。
商の推定には必要な上位部分を使い、余りを計算して高々 1 回の減算補正と 2 回の加算補正を行う。

大きい逆数更新と余り計算では、変換長が短くなる場合に循環畳み込みを使う。
$s>n$ を満たす 2 の冪を取り、$\beta^s-1$ を法として積と差を計算する。
逆数更新で必要な差は $6\beta^n$ 未満、商の補正前の余りは $-b$ より大きく $3b$ 未満なので、法を取った値から元の差を復元できる。
上位から折り返す繰り上がりも全桁処理する。これにより、不要な上位桁まで通常の積を計算する必要がなくなる。

16 進版のシフトは limb 移動とビット操作で行う。
10 進版の大きいシフトは $2^k$ を二乗法で作って乗除算する。
主基数での入出力は桁数に比例する。主基数以外の変換は逐次乗除算であり、大入力では遅くなる。
