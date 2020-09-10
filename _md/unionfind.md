## 説明
頂点の併合、代表元の取得が$O(\alpha (n))$でできるデータ構造。

## 操作
- $\mathrm{root}(a)$ : 頂点$a$の代表元を取得。　
- $\mathrm{unite}(a, b)$ : 頂点$a$と$b$の属する集合を併合する。　
- $\mathrm{size}()$ : 集合の数を取得する。
- $\mathrm{size}(i)$ : $i$の属する集合の大きさを取得する。
- $\mathrm{same}(a, b)$ : $a$と$b$が同じ集合に属するかどうかを判定する。