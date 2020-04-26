---
layout: post
title: Dynamic Connectivity (オフライン)
date: 2020-02-26
category: グラフ
tags: グラフ
---

## 説明

次の形のクエリをオフライン、$O(q\log ^ 2 q)$で求める。
- 決まった辺を追加、削除する
- 連結成分についての情報を取得
{% include a.html code="offlinedynamicconnectivity.cpp" %}