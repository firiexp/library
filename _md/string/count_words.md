---
title: 有限状態DPの長さNの文字列数
documentation_of: //string/count_words.cpp
---

## 説明
`DFA<W>` が受理する長さ $N$ の文字列数を、mod 998244353 の `mint` で求める。

## できること
状態数を $S$、文字種数を $W$ とする。

- `mint count_words(const DFA<W>& a, ll n)`
  長さ `n` の受理文字列数を返す。`n >= 0` が必要。時間 $O(WS^2+S\log S\log N)$、作業領域 $O(S)$。$N<2S$ では通常の DP を使い、$O(NWS)$ 時間

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aa"});
mint answer = count_words(a, 1000000000000000000LL);
```

禁止語の例には `string/avoid_patterns.cpp` も include する。
固定長文字列なので先頭 0 も一文字として数える。数値の正規表記には `math/digit_dp.cpp` を使う。

## 実装上の補足
受理文字列数の列は次数 $S$ 以下の線形漸化式を満たす。最初の $2S$ 項を DP で生成し、Berlekamp-Massey で漸化式を求める。
NTT の変換長上限は既存 FPS に従う。`n == 0` では空列を受理するなら `1`、拒否するなら `0` を返す。

DP の遷移は64 bit整数に加算してから状態ごとに剰余を取る。加算が収まる文字数ごとに区切る。
非零の状態が少ない場合は、それらからの遷移先だけを更新する。全状態の値が 0 になれば以後も 0。
1状態の場合は有効な文字数の累乗で計算する。
`string/dfa_minimize.cpp` の `minimize(a)` を前もって使うと、不要な状態による前計算を減らせる。
