---
title: 有限オートマトンの最小化
documentation_of: //string/dfa_minimize.cpp
---

## 説明
同じ文字列を受理する最小の `DFA<W>` を作る。
到達不能状態を除き、後ろに付けるどの文字列に対しても受理結果が同じ状態をまとめる。

## できること
- `minimize(a)` : 最小化した DFA を返す。全拒否なら空の表と `initial == -1`、それ以外は `initial == 0`
- 受理状態へ到達できない状態は表に残さず、その状態への遷移を `-1` にする
- 空列の受理、文字ごとの遷移、拒否遷移を保つ。状態番号は振り直す

## 使い方
```cpp
auto a = minimize(digit_value_mod(100));
auto answer = digit_count<mint>("1", upper, a);
```

数字条件と桁 DP の include は別途行う。
`intersect` や禁止語から作った DFA、手書きの表にも使える。
前計算を繰り返さないよう、同じ条件の DP には返却した DFA を再利用する。
factory や DP は自動では最小化しない。

## 実装上の補足
[Hopcroft の分割法](https://www.cs.cmu.edu/~cdm/resources/Hopcroft1971.pdf)を使い、分割で小さくなった側を次の処理対象に追加する。
入力状態数を $S$、到達状態数を $R$、文字種数を $W$ とすると、時間 $O(S+W(R+1)\log(R))$、作業領域 $O(S+W(R+1))$。
内部で拒否状態を1つ追加するため、`R < INT_MAX` とする。
最小化後の状態数を $M$ とすると返却表は $O(WM)$ 領域。
文字の違いを保存する最小化であり、文字列の個数だけを保存する重み付き DP への圧縮は行わない。
