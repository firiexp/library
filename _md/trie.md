---
category: "\u6587\u5B57\u5217"
date: 2018-04-28
layout: post
tags: "\u6587\u5B57\u5217"
title: "Trie \u6728"
---

## 説明
文字列をprefixでまとめた木。文字列挿入、prefix 検索が$O(|S|)$でできる。

##  機能
- add(s, x) : sという文字列をxというidで挿入する。
- find(s) : sを検索し、見つかればid, 見つからなければ-1を返す。
{% include a.html code="trie.cpp" %}