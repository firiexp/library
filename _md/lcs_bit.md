## 説明
bitset を使って 2 文字列の LCS 長を求める。
文字列長を `N`, `M` とすると計算量は `O(256 * ceil(M / 64) + N * ceil(M / 64))`。

## できること
- `int LCS_bit(string& s, string& t)`
  `s` と `t` の最長共通部分列の長さを返す。空文字列を含んでも `0` を返す

## 使い方
```cpp
string s, t;
int len = LCS_bit(s, t);
```

## 実装上の補足
ASCII 相当の 256 文字を前提にしている。
復元は行わず、長さだけを返す。
