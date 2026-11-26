---
title: スライド最小値(最大値)
documentation_of: //datastructure/slidingwindow.cpp
---

## 説明
順に追加する値や配列の区間について、最小値・最大値とその添字を求める。

## できること
比較関数 `f(a, b)` は先に追加した `a` を後から追加した `b` より優先するときに `true` を返す。
最小値 なら `less<T>` 、最大値 なら`greater<T>` を使う。同値なら最後に追加した要素を選ぶ。

### 値を順に追加する場合
$W$ を窓内の要素数とする。必要な領域は $O(W)$。

- `monotonic_queue<T, F> q(f)`
  空の窓を作る。F のデフォルトは `less<T>`。$O(1)$
- `void push(T value)`
  `value` を追加する。償却 $O(1)$
- `void push(int index, T value)`
  添字 `index` で `value` を追加する。 `index` は直前に入れたものより大きい必要がある。償却 $O(1)$
- `void pop()`
  残っている要素のうち、最初に追加した要素を除く。使用前に空であってはいけない。$O(1)$
- `void pop_until(int min_index)`
  添字が `min_index` 未満の要素をすべて除く。最悪 $O(W)$、償却 $O(1)$
- `bool empty() const`
  空なら `true` を返す。$O(1)$
- `const pair<int, T>& front() const`
  最良要素の組 `(添字, 値)` への参照を返す。空であってはいけない。$O(1)$

### 配列の区間を動かす場合
配列長を $N$ とし、区間を `[l, r)` とする。

- `sliding_window<T, F> sw(v, f)`
  配列 `v` をコピーし、区間 `[0, 0)` から始める。$O(N)$
- `void slideR()`
  `v[r]` を加え、`r` を 1 つ進める。`r < N` で使う。償却 $O(1)$
- `void slideL()`
  空でない区間の左端を 1 つ進める。$O(1)$
- `int get_index() const`
  最良要素の添字を返す。$O(1)$
- `T value() const`
  最良値を返す。$O(1)$
- `void reset()`
  配列を破棄せずの区間 `[0, 0)` に戻す。最悪 $O(N)$
- `void set(const vector<T>& u)`
  配列を `u` に置き換え、区間を `[0, 0)` に戻す。`u` の長さを $M$ として $O(N+M)$

## 使い方
値を順に追加しながら最小値を求めるときは `monotonic_queue<long long> q;`、最大値なら `monotonic_queue<long long, greater<long long>> q;` を使う。
次の例では、直前の $k$ 個の DP 値から最小値を選び、今回のコストを加えながら窓へ追加する。

```cpp
vector<long long> cost{4, 1, 7};
int k = 2;
monotonic_queue<long long> q;
long long dp = 0;
q.push(dp);
for (int i = 1; i <= int(cost.size()); ++i) {
    q.pop_until(i - k);
    dp = q.front().second + cost[i - 1];  // 順に 4, 1, 8
    q.push(dp);
}
```

配列上の区間を動かす場合は `sliding_window sw(v, less<long long>{});` のように配列と比較関数を渡す。
