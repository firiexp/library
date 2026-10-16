---
title: 上下限付き桁DPの個数と総和
documentation_of: //math/digit_dp.cpp
---

## 説明
非負整数の閉区間 $[L,R]$ で、十進表記が `DFA<10>` に受理される整数の個数・総和を求める。
上下限は文字列のまま扱い、`L-1` や機械語整数への変換は不要。

## できること
- `digit_count<T>(lower, upper, a)` : 個数を返す。総和用の乗算は行わない
- `digit_count_sum<T>(lower, upper, a)` : `{count, sum}` を `pair<T,T>` で返す
- 入力の先頭 0 は無視する。`lower > upper` や全拒否の DFA では 0 件・総和 0

## 使い方
上下限は空でない十進数字列とする。DFA は直接与えても、条件の factory から作ってもよい。
数値の余分な先頭 0 は DFA に渡さず、数値 0 だけは一文字 `"0"` を渡して判定する。
空列の受理とは異なり、0 を含む条件や禁止語にもこの規則を適用する。

```cpp
auto a = no_equal_adjacent();
auto count = digit_count<long long>("123", "321", a);
auto b = required_digits((1 << 0) | (1 << 1));
auto [number, sum] = digit_count_sum<mint>("1", "104", b);
```

数字条件には `math/digit_dfa.cpp`、禁止語には `string/avoid_patterns.cpp` を追加で include する。
`T` は `T(0)`、`T(1)`、`+=`、零との `==` を持つ型とする。
総和版はさらに `T(d)`、`T(10)`、加算・乗算を使う。
整数型では途中結果も型に収め、巨大な上限には modint 等を指定する。

## 実装上の補足
上限の正規化後の桁数を $D$、状態数を $S$ とすると、DP は $O(10D(S+1))$ 時間、作業領域 $O(S+1)$。
入力の先頭 0 の読み飛ばしには入力長に比例する時間を使うが、上下限のコピーは作らない。
上下限との一致フラグと未開始状態を2層で管理する。
総和版の遷移は `new_sum += 10 * sum + digit * count`。
剰余上で個数が 0 でも総和が非零になりうるため、総和版では両方が 0 のときだけ遷移を省く。
