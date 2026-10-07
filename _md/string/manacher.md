---
category: "\u6587\u5B57\u5217"
date: 2019-12-07
tags: "\u6587\u5B57\u5217"
title: manacher
---

## 説明
固定文字列の奇数長・偶数長回文の最大半径を求める。
構築は時間・領域ともに $O(N)$、区間の回文判定は $O(1)$。

## できること
- `manacher(s)` : 各文字を中心とする奇数長回文の最大半径を返す。中心自身を半径に含む
- `PalindromeRadii(s)` : 奇数長・偶数長の両方の半径を構築する。空文字列も扱える
- `odd[i]` : `s[i]` 中心の半径。最大長は $2\,odd[i]-1$
- `even[i]` : `s[i-1]` と `s[i]` の間を中心とする半径。最大長は $2\,even[i]$
- `is_palindrome(l, r)` : 半開区間 $[l,r)$ が回文かを返す。空区間は `true`

## 使い方
`PalindromeRadii radii(s);` とし、`radii.is_palindrome(l, r)` で判定する。
$0\le l\le r\le N$ を前提とする。構築後の文字列更新には対応しない。
区切り文字は不要で、NUL や任意の byte を含む文字列にも使える。
