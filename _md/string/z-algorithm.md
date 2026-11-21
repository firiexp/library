---
title: Z-Algorithm
documentation_of: //string/z-algorithm.cpp
---

## 説明
文字列や配列について、列全体と各位置から始まる接尾辞の最長共通接頭辞長を求める。
別の列 `pattern` と `text` の各接尾辞の最長共通接頭辞長も求められる。

## できること
- `vector<int> Z_algorithm(const string& s)`, `vector<int> Z_algorithm(const vector<T>& s)`
  各位置 `i` の最長共通接頭辞長を `res[i]` に格納して返す。空列なら空列を返し、それ以外では `res[0] = s.size()` となる。配列の要素は `==` で比較する。比較1回が $O(1)$ なら時間は $O(|s|)$、返り値を含む領域は $O(|s|)$。
- `vector<int> z_match(pattern, text)`
  `LCP(pattern, text[i..))` を各位置について返す。引数は `string` 同士、または同じ要素型の `vector<T>` 同士。時間・領域は $O(|pattern|+|text|)$

## 使い方
```cpp
auto z = Z_algorithm(vector<int>{1, 2, 1, 2, 1});  // {5, 0, 3, 0, 1}
```

部分文字列検索には `z_match(pattern, text)` を使う。

```cpp
string pattern = "aba", text = "abacaba";
auto common = z_match(pattern, text);
vector<int> positions;
for (int i = 0; i < (int)text.size(); ++i) {
    if (common[i] == (int)pattern.size()) positions.push_back(i);
}
```

## 実装上の補足
- `z_match` は等値比較だけを使い、NUL や `0xff` も通常の要素として扱う
- `z_match` の返却長は `text.size()` で、空の `pattern` なら全要素が `0` になる
- 空の `pattern` でも位置 $N$ の要素は返さない。空列の一致位置を列挙する場合の末尾は別に扱う
