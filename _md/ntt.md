---
layout: post
title: Number Theoretic Transform
date: 2019-08-16
category: 数学
tags: 数学
---

## 説明
素数$p$が$p = q \cdot 2^{k}+1$の形で表され、原始根$g$が存在するとき、$g^q$が1の$2^k$乗根となる。それゆえ、$i \le k$について、$2^i$乗根が簡単に求められるので、$2^i$要素の数列について$\mod p$でFFTと同様にして畳み込みができる。
原始根は、よく使われるものに関してはコードに記載したが、例にないものが必要なら、Wolfram|Alphaなどで計算すればよい。 

この実装は `mod = 998244353`, `root = 3` を使った NTT と、形式的冪級数 (FPS) の基本演算を提供する。
`poly::pow(long long k, int deg)` により、FPS の k 乗（切り詰め次数付き）も扱える。
`poly::sqrt(int deg)` は Newton 法で FPS の平方根（存在しない場合は空多項式）を返す。