---
title: modintの共通基底実装
documentation_of: //math/modular/modint_base.cpp
---

## 説明
`math/modular/modint.cpp` が使用する固定 MOD の `modint<Mod>` の本体定義。
通常は `MOD` を定義した上で `math/modular/modint.cpp` を使う。

## 実装上の補足
事前に定義した `MOD` に依存しないテンプレート構造体 `modint<Mod>` だけを分離している。
`math/modular/modint.cpp` 側で `using mint = modint<MOD>;` を定義する。
`inv()` と除算は拡張ユークリッド互除法で逆元を求めるため、合成数の MOD でも互いに素なら計算できる。
