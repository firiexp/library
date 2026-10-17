---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/int_point.cpp
    title: "\u6574\u6570\u5EA7\u6A19\u70B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_polygon_integral.test.cpp
    title: test/yosupo_aplusb_polygon_integral.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u89D2\u5F62\u306E\u533A\u9593\u9762\u7A4D\u3068\u91CD\u5FC3"
    links: []
  bundledCode: "#line 1 \"geometry/polygon_integral.cpp\"\n\n\n\n#line 1 \"geometry/int_point.cpp\"\
    \n\n\n\nstruct IntPoint {\n    long long x = 0, y = 0;\n\n    IntPoint() = default;\n\
    \    IntPoint(long long x, long long y) : x(x), y(y) {}\n\n    bool operator<(const\
    \ IntPoint &p) const { return x < p.x || (!(p.x < x) && y < p.y); }\n    bool\
    \ operator==(const IntPoint &p) const { return x == p.x && y == p.y; }\n    bool\
    \ operator!=(const IntPoint &p) const { return !(*this == p); }\n    IntPoint\
    \ &operator+=(const IntPoint &p) { x += p.x; y += p.y; return *this; }\n    IntPoint\
    \ &operator-=(const IntPoint &p) { x -= p.x; y -= p.y; return *this; }\n    IntPoint\
    \ operator+(const IntPoint &p) const { return IntPoint(*this) += p; }\n    IntPoint\
    \ operator-(const IntPoint &p) const { return IntPoint(*this) -= p; }\n};\n\n\n\
    \n/**\n * @brief \u6574\u6570\u5EA7\u6A19\u70B9\n */\n#line 5 \"geometry/polygon_integral.cpp\"\
    \n\nclass PolygonIntegral {\npublic:\n    struct RationalPoint {\n        __int128\
    \ x_num, y_num, den;\n    };\n\n    class Result {\n        friend class PolygonIntegral;\n\
    \n        __int128 area2_ = 0, x_sum = 0, y_sum = 0;\n\n        Result(__int128\
    \ area2, __int128 x, __int128 y) : area2_(area2), x_sum(x), y_sum(y) {}\n\n  \
    \  public:\n        Result() = default;\n\n        __int128 area2() const { return\
    \ area2_; }\n\n        optional<RationalPoint> centroid() const {\n          \
    \  if (area2_ == 0) return nullopt;\n            __int128 x = x_sum, y = y_sum,\
    \ d = area2_;\n            if (d < 0) {\n                x = -x;\n           \
    \     y = -y;\n                d = -d;\n            }\n            return RationalPoint{x,\
    \ y, 3 * d};\n        }\n    };\n\nprivate:\n    vector<IntPoint> points;\n  \
    \  vector<Result> prefix;\n\n    static Result edge(IntPoint a, IntPoint b) {\n\
    \        __int128 d = (__int128)a.x * b.y - (__int128)a.y * b.x;\n        return\
    \ {d, ((__int128)a.x + b.x) * d, ((__int128)a.y + b.y) * d};\n    }\n\n    static\
    \ Result add(Result a, const Result &b) {\n        a.area2_ += b.area2_;\n   \
    \     a.x_sum += b.x_sum;\n        a.y_sum += b.y_sum;\n        return a;\n  \
    \  }\n\npublic:\n    explicit PolygonIntegral(const vector<IntPoint> &input) :\
    \ points(input), prefix(input.size() + 1) {\n        int n = points.size();\n\
    \        for (int i = 0; i < n; ++i)\n            prefix[i + 1] = add(prefix[i],\
    \ edge(points[i], points[(i + 1) % n]));\n    }\n\n    Result whole() const {\
    \ return prefix.back(); }\n\n    Result query(int u, int v) const {\n        int\
    \ n = points.size();\n        assert(0 <= u && u < n && 0 <= v && v < n);\n  \
    \      if (u == v) return {};\n        Result result{prefix[v].area2_ - prefix[u].area2_,\n\
    \                      prefix[v].x_sum - prefix[u].x_sum,\n                  \
    \    prefix[v].y_sum - prefix[u].y_sum};\n        if (u > v) result = add(result,\
    \ prefix.back());\n        return add(result, edge(points[v], points[u]));\n \
    \   }\n};\n\n\n\n/**\n * @brief \u591A\u89D2\u5F62\u306E\u533A\u9593\u9762\u7A4D\
    \u3068\u91CD\u5FC3\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GEOMETRY_POLYGON_INTEGRAL_CPP\n#define FIRIEXP_LIBRARY_GEOMETRY_POLYGON_INTEGRAL_CPP\n\
    \n#include \"int_point.cpp\"\n\nclass PolygonIntegral {\npublic:\n    struct RationalPoint\
    \ {\n        __int128 x_num, y_num, den;\n    };\n\n    class Result {\n     \
    \   friend class PolygonIntegral;\n\n        __int128 area2_ = 0, x_sum = 0, y_sum\
    \ = 0;\n\n        Result(__int128 area2, __int128 x, __int128 y) : area2_(area2),\
    \ x_sum(x), y_sum(y) {}\n\n    public:\n        Result() = default;\n\n      \
    \  __int128 area2() const { return area2_; }\n\n        optional<RationalPoint>\
    \ centroid() const {\n            if (area2_ == 0) return nullopt;\n         \
    \   __int128 x = x_sum, y = y_sum, d = area2_;\n            if (d < 0) {\n   \
    \             x = -x;\n                y = -y;\n                d = -d;\n    \
    \        }\n            return RationalPoint{x, y, 3 * d};\n        }\n    };\n\
    \nprivate:\n    vector<IntPoint> points;\n    vector<Result> prefix;\n\n    static\
    \ Result edge(IntPoint a, IntPoint b) {\n        __int128 d = (__int128)a.x *\
    \ b.y - (__int128)a.y * b.x;\n        return {d, ((__int128)a.x + b.x) * d, ((__int128)a.y\
    \ + b.y) * d};\n    }\n\n    static Result add(Result a, const Result &b) {\n\
    \        a.area2_ += b.area2_;\n        a.x_sum += b.x_sum;\n        a.y_sum +=\
    \ b.y_sum;\n        return a;\n    }\n\npublic:\n    explicit PolygonIntegral(const\
    \ vector<IntPoint> &input) : points(input), prefix(input.size() + 1) {\n     \
    \   int n = points.size();\n        for (int i = 0; i < n; ++i)\n            prefix[i\
    \ + 1] = add(prefix[i], edge(points[i], points[(i + 1) % n]));\n    }\n\n    Result\
    \ whole() const { return prefix.back(); }\n\n    Result query(int u, int v) const\
    \ {\n        int n = points.size();\n        assert(0 <= u && u < n && 0 <= v\
    \ && v < n);\n        if (u == v) return {};\n        Result result{prefix[v].area2_\
    \ - prefix[u].area2_,\n                      prefix[v].x_sum - prefix[u].x_sum,\n\
    \                      prefix[v].y_sum - prefix[u].y_sum};\n        if (u > v)\
    \ result = add(result, prefix.back());\n        return add(result, edge(points[v],\
    \ points[u]));\n    }\n};\n\n#endif\n\n/**\n * @brief \u591A\u89D2\u5F62\u306E\
    \u533A\u9593\u9762\u7A4D\u3068\u91CD\u5FC3\n */\n"
  dependsOn:
  - geometry/int_point.cpp
  isVerificationFile: false
  path: geometry/polygon_integral.cpp
  requiredBy: []
  timestamp: '2026-10-18 01:50:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_polygon_integral.test.cpp
date: 2026-10-18
documentation_of: geometry/polygon_integral.cpp
layout: document
tags: "\u5E7E\u4F55"
title: "\u591A\u89D2\u5F62\u306E\u533A\u9593\u9762\u7A4D\u3068\u91CD\u5FC3"
---

## 説明
固定した整数凸多角形について、周に沿った頂点列と弦で囲む領域の面積・重心を整数演算で求める。
面積は符号付き面積の2倍、重心は分数で返すため、半整数の面積や整数でない重心も誤差なく扱える。
時計回り・反時計回りのどちらも扱う。前処理・保持領域は $O(N)$、各照会は $O(1)$。

## できること
- `PolygonIntegral index(points)`
  `vector<IntPoint>` を入力順のまま保持し、辺の寄与の累積和を作る。入力は変更しない
- `Result query(int u, int v) const`
  `u` から `v` へ入力順に進み、辺 `v -> u` で閉じた領域を返す。`u > v` は末尾を越えて周回する。`u == v` は面積 $0$ の退化領域
- `Result whole() const`
  多角形全体の集計を返す。空列・1点・2点は面積 $0$
- `__int128 result.area2() const`
  符号付き面積の2倍を返す。面積の大小比較や加算を整数のまま行える。反時計回りなら正、時計回りなら負
- `optional<RationalPoint> result.centroid() const`
  重心を正確な分数で返す。面積が $0$ なら `nullopt`
- `point.x_num`, `point.y_num`, `point.den`
  `RationalPoint` の `__int128` の分子と共通分母。座標は $(\mathrm{x\_num}/\mathrm{den},\mathrm{y\_num}/\mathrm{den})$ で、`den > 0`。約分はしない

## 使い方
頂点は周上の順に並べ、末尾に先頭を重複させない。凸性の検査は行わない。
`query` の添字は `0 <= u, v < N` とする。
反時計回りでは面積が正、時計回りでは負となる。

```cpp
vector<IntPoint> points{ {0, 0}, {4, 0}, {4, 2}, {0, 2} };
PolygonIntegral index(points);
auto lower = index.query(0, 2);
auto upper = index.query(2, 0);
auto full = index.whole();
assert(lower.area2() == 8);
assert(full.area2() == 16);
auto center = full.centroid();
if (center) {
    __int128 k = 2;
    bool x_equals_k = center->x_num == k * center->den;
    bool x_is_integer = center->x_num % center->den == 0;
}
```

`lower` は頂点列 `0, 1, 2` の三角形で、面積 $4$、重心 $(8/3, 2/3)$。
重心の返却値は `x_num = 64, y_num = 16, den = 24` となる。
`upper` は頂点列 `2, 3, 0` の三角形で、面積 $4$、重心 $(4/3, 4/3)$。
`full` は面積 $8$、重心 $(2,1)$ となり、例の2つの判定はいずれも `true`。`query(0, 0)` とは異なる。
隣接頂点の `query(u, u+1)` は退化するが、逆向きの照会は残りの周回路を使う。

小数が必要な場合だけ、`(long double)result.area2() / 2` や `(long double)center->x_num / center->den` へ変換する。
整数除算では小数部分が失われる。分数の比較で交差積を使う場合は、その積も整数型に収まる必要がある。

同じ境界を逆順に走査すると `area2()` の符号が反転し、重心の分子・分母は変わらない。
固定した入力で `query(u,v)` を `query(v,u)` に交換すると補領域を選ぶため、重心も一般には異なる。

## 実装上の補足
辺 $a \to b$ の寄与は次のとおり。

$$
d = a_x b_y - a_y b_x, \qquad
(D,X,Y) = (d, (a_x+b_x)d, (a_y+b_y)d)
$$

内部では $D$ を面積の2倍、$X,Y$ を重心の分子として累積する。これらの集計値は外部へ公開しない。
周回区間の累積和の差に閉じる弦の寄与を加え、重心を $(X/(3D),Y/(3D))$ で求める。
`centroid()` は $D>0$ なら $(X,Y,3D)$、$D<0$ なら $(-X,-Y,-3D)$ を返し、分母を正にする。
浮動小数点演算や最大公約数の計算は行わず、`area2()` と `centroid()` はともに $O(1)$。

座標の積・和は計算前に `__int128` へ変換する。
各辺・弦の寄与、累積和、区間差、周回補正と弦の加算を含め、すべての中間値が符号付き `__int128` に収まることを前提とする。
`centroid()` を呼ぶ場合は、分母 $3|D|$ と符号を整えた分子も符号付き `__int128` に収まることを追加の前提とする。
例えば $N \le 2\times10^5$, $|x|,|y| \le 10^9$ はこの範囲に収まる。
`long long` 座標全域を無条件には保証しない。
