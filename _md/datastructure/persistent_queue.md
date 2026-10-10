---
title: 永続キュー
documentation_of: //datastructure/persistent_queue.cpp
---

## 説明
過去の任意versionから末尾追加・先頭削除を分岐できるキュー。
version 0 は空であり、更新は元versionを変更せず新しいversion番号を返す。

## できること
- `PersistentQueue<T> q`：空のversion 0を作る
- `push(version, value)`：末尾に追加した新versionを返す
- `pop(version)`：先頭を削除した新versionを返す。空でないことが前提
- `front(version)`：先頭要素のコピーを返す。空でないことが前提
- `size(version)` / `empty(version)`：要素数 / 空かを返す

## 使い方
操作数の先読みやbuildは不要で、以前返されたversion番号をそのまま使う。

```cpp
PersistentQueue<int> q;
int a = q.push(0, 10);
int b = q.push(a, 20);
int c = q.pop(b);
int d = q.push(a, 30);
```

`b` は `{10,20}`、`c` は `{20}`、`d` は `{10,30}` を保持する。

## 実装上の補足
末尾nodeと長さをversionごとに保持し、先頭はpush履歴の祖先を倍増法で辿って求める。
空になったversionは末尾を切り離し、次のpushを新しい履歴の根にする。
祖先情報は1本の連続配列に格納し、nodeごとの小さな配列確保を行わない。

これまでの更新数を $Q$、push数を $P$ とし、要素コピーを $O(1)$ とすると、`front` は最悪 $O(\log(P+2))$、`size/empty` は最悪 $O(1)$。
`push` は償却 $O(\log(P+2))$、`pop` は償却 $O(1)$。償却は配列の幾何拡張に由来し、過去versionへの分岐回数によって崩れない。
総領域は $O(Q+P\log(P+2))$。
