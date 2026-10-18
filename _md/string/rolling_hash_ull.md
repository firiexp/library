---
title: Rolling Hash(mod 2^61-1)
documentation_of: //string/rolling_hash_ull.cpp
---
## 説明
`mod 2^61 - 1` の Rolling Hash。
前計算した prefix hash から部分文字列ハッシュを $O(1)$ で取れる。

## できること
- `rolling_hash_ull rh(s)`
  文字列 `s` の prefix hash を構築する
- `rolling_hash_ull rh(n)`
  `p[n]` まで前計算する
- `ull get(int l, int r)`
  `s[l, r)` のハッシュを返す
- `static ull val(string& s)`
  文字列全体のハッシュを $O(|s|)$ 時間・追加領域 $O(1)$ で返す
- `static ull& B()`
  使用中の base を返す
- `static vector<ull>& p()`
  base の $i$ 乗を `p[i]` に格納した配列を返す

## 使い方
```cpp
rolling_hash_ull rh(s);
if (rh.get(l1, r1) == rh.get(l2, r2)) {
    // 高確率で同じ文字列
}
```

## 実装上の補足
base は初回利用時に乱択で 1 回だけ決まる。
`p` を明示的に伸ばす場合は整数コンストラクタを使う。文字列コンストラクタも必要な長さまで伸ばす。
比較は高確率一致であり、理論上は衝突しうる。
