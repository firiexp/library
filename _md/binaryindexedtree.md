## 説明
可換群(逆元が存在する群)について、区間和を$O(\log N)$で求め、更新を$O(\log N)$で行う。<br>
可換でなくても$[0, x)$について演算した結果だけを求めたいのであれば、使うことができる。(例: LIS)

## 操作
- $\mathrm{add}(k, x)$ : $k$番目の要素に$x$を加算する。
- $\mathrm{sum}(k)$ : 閉区間$[0, k]$の和を求める。
- $\mathrm{lower\_bound}(x)$ : $\mathrm{sum}(k)$が$x$以上になる最小の$k$を求める。