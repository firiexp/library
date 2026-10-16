---
title: 有限状態DPの長さNの文字列数
documentation_of: //string/count_words.cpp
---

## 説明
`DFA<W>` が受理する長さ $N$ の文字列数を、998244353 を法とする `mint` で求める。
長い列には Berlekamp-Massey と線形漸化式を使う。

## できること
- `count_words(a, n)` : 長さ `n` で受理される文字列数を返す。`0 <= n <= LLONG_MAX`
- `n == 0` は初期状態が受理するかで決まる。全拒否、拒否遷移、受理状態なしにも対応する
- 同じ行き先を持つ別の文字も、それぞれ別の列として数える

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aa"});
mint answer = count_words(a, 1000000000000000000LL);
```

禁止語の例には `string/avoid_patterns.cpp` も include する。
手書きの遷移表や `intersect` の結果も使え、追加の build は不要。
固定長文字列なので先頭 0 も一文字として数える。数値の正規表記には `math/digit_dp.cpp` を使う。
`mint` は既存 FPS と同じ 998244353 専用で、他の法や一般半環には対応しない。

## 実装上の補足
状態数を $S$ とすると、受理状態への個数の和は Cayley-Hamilton により次数 $S$ 以下の線形漸化式を満たす。
最初の $2S$ 項を文字別の DP で生成すれば、既存の Berlekamp-Massey で十分であり、確率的な推測ではない。
短い $N$ は通常 DP で終了する。

長い $N$ の時間は $O(WS^2+S\log S\log N)$、短い $N$ は $O(S+NWS)$。
DP と漸化式の作業領域は $O(S)$。状態数は `int` に収まる範囲とし、NTT の変換長上限は既存 FPS に従う。
