---
title: manacher
date: 2019-12-07
category: 文字列
tags: 文字列
---

## 説明
与えられた文字列について、各位置を中心とする奇数長・偶数長回文の最大半径を求める。

## できること
文字列長を $N$ とする。

- `manacher(s)` : 各文字を中心とする奇数長回文の最大半径を返す。中心自身を半径に含む。時間・領域は $O(N)$
- `PalindromeRadii(s)` : 奇数長・偶数長の両方の半径を構築する。時間・領域は $O(N)$
- `odd[i]` : `s[i]` 中心の半径。最大長は $2\,odd[i]-1$
- `even[i]` : `s[i-1]` と `s[i]` の間を中心とする半径。最大長は $2\,even[i]$
- `is_palindrome(l, r)` : 半開区間 $[l,r)$ が回文かを返す。空区間は `true`。$O(1)$

## 使い方
`PalindromeRadii radii(s);` とし、`radii.is_palindrome(l, r)` で判定する。
$0\le l\le r\le N$ を前提とする。構築後の文字列更新には対応しない。
区切り文字は不要で、NUL や任意の byte を含む文字列にも使える。
