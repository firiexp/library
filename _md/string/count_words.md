---
title: 有限状態DPの長さNの文字列数
documentation_of: //string/count_words.cpp
---

## 説明
`DFA<W>` が受理する長さ $N$ の文字列数を、mod 998244353 の `mint` で求める。

## できること
状態数を $S$、文字種数を $W$、集約後の辺数を $E$ とする。

- `mint count_words(const DFA<W>& a, ll n)`
  長さ `n` の受理文字列数を返す。時間 $O(WS^2+S\log S\log N)$。$N<2S$ では通常の DP を使い、$O(NWS)$ 時間
- `DFAWordCounter<W> counter(a)`
  構築時の DFA に対応する初期項と漸化式・母関数を保持する。準備は $O(WS^2+S^2+S\log S)$ 時間
- `mint counter.count(ll n) const`
  長さ `n` の受理文字列数を返す。既知の項は $O(1)$、未知の項は漸化式の次数を $K$ として $O(K\log K\log N)$ 時間。

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aa"});
mint answer = count_words(a, 1000000000000000000LL);
DFAWordCounter<2> counter(a);
mint first = counter.count(1000000000000000000LL);
mint second = counter.count(123456789);
```

禁止語の例には `string/avoid_patterns.cpp` も include する。
固定長文字列なので先頭 0 も一文字として数える。数値の正規表記には `math/digit_dp.cpp` を使う。

## 実装上の補足
受理文字列数の列は次数 $S$ 以下の線形漸化式を満たす。最初の $2S$ 項を DP で生成し、Berlekamp-Massey で漸化式を求める。
NTT の変換長上限は既存 FPS に従う。`n == 0` では空列を受理するなら `1`、拒否するなら `0` を返す。

DP の遷移は64 bit整数に加算してから状態ごとに剰余を取る。加算が収まる文字数ごとに区切る。
非零の状態が少ない場合は、それらからの遷移先だけを更新する。全状態の値が 0 になれば以後も 0。
1状態の場合は有効な文字数の累乗で計算する。

同じ状態への文字遷移が多い場合は、行先と文字数の組にまとめる。異なる文字は別の文字列として数え、拒否遷移 `-1` は除く。
生成項数が32以下、文字種数が4以下、または活動状態が少ない間は集約しない。
活動状態が $\max(8,\lfloor S/8\rfloor)$ 個に達し、残りの生成項数が32を超える場合に最大16行を標本に取る。辺数が3/4以下になる場合だけ集約表を作り、全行の集約率も確認する。
行先を数える配列を使うため準備は $O(SW)$、残りの項（高々 $2S$ 項）の生成は $O(S^2+SE)$ 時間である。
準備前の項生成には従来の費用がかかり、Berlekamp-Massey とその後の計算量は変わらない。
64 bitで全文字分をまとめて加算できる場合だけ集約し、文字数を掛ける前に拡幅する。活動状態・遷移先だけを処理する経路も維持する。

`DFAWordCounter` は同じ DP で初期項を作り、Berlekamp-Massey と母関数の構築を1回だけ行う。照会順は任意で、別の DFA を使う場合は新しいオブジェクトを作る。
単発の `count_words` は短い長さで必要な項だけを計算する。反復用オブジェクトの前計算は強制しない。
`string/dfa_minimize.cpp` の `minimize(a)` を前もって使うと、不要な状態による前計算を減らせる。
