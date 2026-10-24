---
title: 永続キュー
documentation_of: //datastructure/persistent_queue.cpp
---

## 説明
過去の任意のバージョンから末尾追加・先頭削除を分岐できるキュー。
バージョン 0 は空であり、更新は元のバージョンを変更せず新しいバージョン番号を返す。

## できること
対象バージョンの要素数を $L$ とし、要素コピーを $O(1)$ とする。

- `PersistentQueue<T> q`：空のバージョン0を作る。$O(1)$
- `push(version, value)`：末尾に追加した新しいバージョンを返す。追加後の要素数を $L$ として償却 $O(\log L)$
- `pop(version)`：先頭を削除した新しいバージョンを返す。空でないことが前提。償却 $O(1)$
- `front(version)`：先頭要素のコピーを返す。空でないことが前提。$O(\log L)$
- `get(version, k)`：`version` の `k` 番目の要素を返す。$O(\log L)$
- `back(version)`：末尾要素のコピーを返す。空でないことが前提。$O(1)$
- `size(version)` / `empty(version)`：要素数 / 空かを返す。$O(1)$

## 使い方
以前返されたバージョン番号を更新・取得操作に渡す。
`get` の位置は先頭を0とし、`0 <= k < size(version)` を満たすものとする。

```cpp
PersistentQueue<int> q;
int a = q.push(0, 10);
int b = q.push(a, 20);
int c = q.pop(b);
int d = q.push(a, 30);
```

`b` は `{10,20}`、`c` は `{20}`、`d` は `{10,30}` を保持する。
`get(b, 1)` と `back(b)` はどちらも `20` を返す。

## 実装上の補足
末尾nodeと長さをバージョンごとに保持し、先頭や途中の要素はpush履歴の祖先を倍増法で辿って求める。
空になったバージョンは末尾を切り離し、次のpushを新しい履歴の根にする。
祖先情報は1本の連続配列に格納し、nodeごとの小さな配列確保を行わない。

更新数を $Q$、各 `push` で作るキューの要素数を $L_i$ とすると、総領域は $O(Q+\sum_i\log L_i)$。
