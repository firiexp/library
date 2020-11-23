---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/geometry.cpp
    title: "\u5E7E\u4F55\u30E9\u30A4\u30D6\u30E9\u30EA"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0273.test.cpp
    title: test/aoj0273.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/dualgraph.md
    document_title: "\u53CC\u5BFE\u30B0\u30E9\u30D5\u306E\u69CB\u7BC9"
    links: []
  bundledCode: "#line 1 \"geometry/geometry.cpp\"\nusing real = double;\nstatic constexpr\
    \ real EPS = 1e-10;\nconst real pi = acos(-1);\nstruct Point {\n    real x, y;\n\
    \    Point& operator+=(const Point a) { x += a.x; y += a.y;  return *this; }\n\
    \    Point& operator-=(const Point a) { x -= a.x; y -= a.y;  return *this; }\n\
    \    Point& operator*=(const real k) { x *= k; y *= k;  return *this; }\n    Point&\
    \ operator/=(const real k) { x /= k; y /= k;  return *this; }\n    Point operator+(const\
    \ Point a) const {return Point(*this) += a; }\n    Point operator-(const Point\
    \ a) const {return Point(*this) -= a; }\n    Point operator*(const real k) const\
    \ {return Point(*this) *= k; }\n    Point operator/(const real k) const {return\
    \ Point(*this) /= k; }\n    bool operator<(const Point &a) const { return (x !=\
    \ a.x ? x < a.x : y < a.y); }\n    explicit Point(real a = 0, real b = 0) : x(a),\
    \ y(b) {};\n};\n\nbool sorty(Point a, Point b){\n    return (a.y != b.y ? a.y\
    \ < b.y : a.x < b.x);\n}\n\nistream& operator>> (istream& s, Point& P){\n    s\
    \ >> P.x >> P.y;\n    return s;\n}\n\ninline real dot(Point a, Point b){ return\
    \ a.x*b.x + a.y*b.y; }\ninline real cross(Point a, Point b){ return a.x*b.y -\
    \ a.y*b.x; }\ninline real abs(Point a){ return sqrt(dot(a, a)); }\n\n\nreal angle(Point\
    \ A, Point B){\n    return acos(dot(A, B)/abs(A)/abs(B));\n}\n\n\n\nstatic constexpr\
    \ int COUNTER_CLOCKWISE = 1;\nstatic constexpr int CLOCKWISE = -1;\nstatic constexpr\
    \ int ONLINE_BACK = 2;\nstatic constexpr int ONLINE_FRONT = -2;\nstatic constexpr\
    \ int ON_SEGMENT = 0;\n\nint ccw(Point a, Point b, Point c){\n    b -= a; c -=\
    \ a;\n    if(cross(b, c) > EPS) return COUNTER_CLOCKWISE;\n    if(cross(b, c)\
    \ < -EPS) return CLOCKWISE;\n    if(dot(b, c) < 0) return ONLINE_BACK;\n    if(abs(b)\
    \ < abs(c)) return ONLINE_FRONT;\n    return ON_SEGMENT;\n}\nstruct Segment {\n\
    \    Point a, b;\n    Segment(Point x, Point y) : a(x), b(y) {};\n};\n\nstruct\
    \ Line {\n    Point a, b;\n    Line(Point x, Point y) : a(x), b(y) {};\n};\n\n\
    struct Circle{\n    Point c; real r;\n    Circle(Point c, real r): c(c), r(r)\
    \ {};\n};\n\nusing Polygon = vector<Point>;\n\nbool intersect(Segment s, Segment\
    \ t){\n    return (ccw(s.a, s.b, t.a)*ccw(s.a, s.b, t.b) <= 0 &&\n           \
    \ ccw(t.a, t.b, s.a)*ccw(t.a, t.b, s.b) <= 0);\n}\n\nbool intersect(Segment s,\
    \ Line t){\n    int a = ccw(t.a, t.b, s.a), b = ccw(t.a, t.b, s.b);\n    return\
    \ (!(a&1) || !(b&1) || a != b);\n}\n\nPoint polar(double r, double t){\n    return\
    \ Point(r*cos(t), r*sin(t));\n}\n\ndouble arg(Point p){\n    return atan2(p.y,\
    \ p.x);\n}\n\nstatic constexpr int CONTAIN = 0;\nstatic constexpr int INSCRIBE\
    \ = 1;\nstatic constexpr int INTERSECT = 2;\nstatic constexpr int CIRCUMSCRIBED\
    \ = 3;\nstatic constexpr int SEPARATE = 4;\n\nint intersect(Circle c1, Circle\
    \ c2){\n    if(c1.r < c2.r) swap(c1, c2);\n    real d = abs(c1.c-c2.c);\n    real\
    \ r = c1.r + c2.r;\n    if(fabs(d-r) < EPS) return CIRCUMSCRIBED;\n    if(d >\
    \ r) return SEPARATE;\n    if(fabs(d+c2.r-c1.r) < EPS) return INSCRIBE;\n    if(d+c2.r\
    \ < c1.r) return CONTAIN;\n    return INTERSECT;\n}\n\nreal distance(Line l, Point\
    \ c){\n    return abs(cross(l.b-l.a, c-l.a)/abs(l.b-l.a));\n}\n\n\nreal distance(Segment\
    \ s, Point c){\n    if(dot(s.b-s.a, c-s.a) < EPS) return abs(c-s.a);\n    if(dot(s.a-s.b,\
    \ c-s.b) < EPS) return abs(c-s.b);\n    return abs(cross(s.b-s.a, c-s.a)) / abs(s.a-s.b);\n\
    }\n\nreal distance(Segment s, Segment t){\n    if(intersect(s, t)) return 0.0;\n\
    \    return min({distance(s, t.a), distance(s, t.b),\n                distance(t,\
    \ s.a), distance(t, s.b)});\n}\n\n\nPoint project(Line l, Point p){\n    Point\
    \ Q = l.b-l.a;\n    return l.a + Q*(dot(p-l.a, Q) / dot(Q, Q));\n}\n\n\nPoint\
    \ project(Segment s, Point p){\n    Point Q = s.b-s.a;\n    return s.a + Q*(dot(p-s.a,\
    \ Q) / dot(Q, Q));\n}\n\nPoint refrect(Segment s, Point p){\n    Point Q = project(s,\
    \ p);\n    return Q*2-p;\n}\n\nbool isOrthogonal(Segment s, Segment t){\n    return\
    \ fabs(dot(s.b-s.a, t.b-t.a)) < EPS;\n}\n\nbool isparallel(Segment s, Segment\
    \ t){\n    return fabs(cross(s.b-s.a, t.b-t.a)) < EPS;\n}\n\n\nPoint crossPoint(Segment\
    \ s, Segment t){\n    real d1 = cross(s.b-s.a, t.b-t.a);\n    real d2 = cross(s.b-s.a,\
    \ s.b-t.a);\n    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;\n    return\
    \ t.a+(t.b-t.a)*d2/d1;\n}\n\nPoint crossPoint(Line s, Line t){\n    real d1 =\
    \ cross(s.b-s.a, t.b-t.a);\n    real d2 = cross(s.b-s.a, s.b-t.a);\n    if(fabs(d1)\
    \ < EPS && fabs(d2) < EPS) return t.a;\n    return t.a+(t.b-t.a)*d2/d1;\n}\n\n\
    Polygon crossPoint(Circle c, Line l){\n    Point p = project(l, c.c), q = (l.b-l.a)/abs(l.b-l.a);\n\
    \    if(abs(distance(l, c.c)-c.r) < EPS){\n        return {p};\n    }\n    double\
    \ k = sqrt(c.r*c.r-dot(p-c.c, p-c.c));\n    return {p-q*k, p+q*k};\n}\n\nPolygon\
    \ crossPoint(Circle c, Segment s){\n    auto tmp = crossPoint(c, Line(s.a, s.b));\n\
    \    Polygon ret;\n    for (auto &&i : tmp) {\n        if(distance(s, i) < EPS)\
    \ ret.emplace_back(i);\n    }\n    return ret;\n}\n\n\nPolygon crossPoint(Circle\
    \ c1, Circle c2){\n    double d = abs(c1.c-c2.c);\n    double a = acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));\n\
    \    double t = arg(c2.c-c1.c);\n    return {c1.c+polar(c1.r, t+a), c1.c+polar(c1.r,\
    \ t-a)};\n}\n\nPolygon tangent(Circle c1, Point p){\n    Circle c2 = Circle(p,\
    \ sqrt(dot(c1.c-p, c1.c-p)-c1.r*c1.r));\n    return crossPoint(c1, c2);\n}\nvector<Line>\
    \ tangent(Circle c1, Circle c2){\n    vector<Line> ret;\n    if(c1.r < c2.r) swap(c1,\
    \ c2);\n    double k = dot(c1.c-c2.c, c1.c-c2.c);\n    if(abs(k) < EPS) return\
    \ {};\n    Point u = (c2.c-c1.c)/sqrt(k);\n    Point v(-u.y, u.x);\n    for (auto\
    \ &&i : {-1, 1}) {\n        double h = (c1.r+i*c2.r)/sqrt(k);\n        if(abs(h*h-1)\
    \ < EPS){\n            ret.emplace_back(c1.c+u*c1.r, c1.c+(u+v)*c1.r);\n     \
    \   }else if(h*h < 1){\n            Point u2 = u*h, v2 = v*sqrt(1-h*h);\n    \
    \        ret.emplace_back(c1.c+(u2+v2)*c1.r, c2.c-(u2+v2)*c2.r*i);\n         \
    \   ret.emplace_back(c1.c+(u2-v2)*c1.r, c2.c-(u2-v2)*c2.r*i);\n        }\n   \
    \ }\n    return ret;\n}\n\nreal area(Polygon v){\n    if(v.size() < 3) return\
    \ 0.0;\n    real ans = 0.0;\n    for (int i = 0; i < v.size(); ++i) {\n      \
    \  ans += cross(v[i], v[(i+1)%v.size()]);\n    }\n    return ans/2;\n}\n\nreal\
    \ area(Circle c, Polygon &v){\n    int n = v.size();\n    real ans = 0.0;\n  \
    \  Polygon u;\n    for (int i = 0; i < n; ++i) {\n        u.emplace_back(v[i]);\n\
    \        auto q = crossPoint(c, Segment(v[i], v[(i+1)%n]));\n        for (auto\
    \ &&j : q) {\n            u.emplace_back(j);\n        }\n    }\n    for (int i\
    \ = 0; i < u.size(); ++i) {\n        Point A = u[i]-c.c, B = u[(i+1)%u.size()]-c.c;\n\
    \        if(abs(A) >= c.r+EPS || abs(B) >= c.r+EPS){\n            Point C = polar(1,\
    \ arg(B)-arg(A));\n            ans += c.r*c.r*arg(C)/2;\n        }else {\n   \
    \         ans += cross(A, B)/2;\n        }\n    }\n    return ans;\n}\n\nreal\
    \ area(Circle a, Circle b){\n    auto d = abs(a.c-b.c);\n    if(a.r+b.r <= d +\
    \ EPS) return 0;\n    else if(d <= abs(a.r-b.r)) return pi*min(a.r, b.r)*min(a.r,\
    \ b.r);\n    real p = 2*acos((a.r*a.r + d*d - b.r*b.r)/(2*a.r*d));\n    real q\
    \ = 2*acos((b.r*b.r + d*d - a.r*a.r)/(2*b.r*d));\n    return a.r*a.r*(p-sin(p))/2\
    \ + b.r*b.r*(q-sin(q))/2;\n}\n\nPolygon convex_hull(Polygon v){\n    int n = v.size();\n\
    \    sort(v.begin(),v.end(), sorty);\n    int k = 0;\n    Polygon ret(n*2);\n\
    \    for (int i = 0; i < n; ++i) {\n        while(k > 1 && cross(ret[k-1]-ret[k-2],\
    \ v[i]-ret[k-1]) < 0) k--;\n        ret[k++] = v[i];\n    }\n    for(int i = n-2,\
    \ t=k; i >= 0; i--){\n        while(k > t && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1])\
    \ < 0) k--;\n        ret[k++] = v[i];\n    }\n    ret.resize(k-1);\n    return\
    \ ret;\n}\n\nbool isconvex(Polygon v){\n    int n = v.size();\n    for (int i\
    \ = 0; i < n; ++i) {\n        if(ccw(v[(i+n-1)%n], v[i], v[(i+1)%n]) == CLOCKWISE)\
    \ return false;\n    }\n    return true;\n}\n\nint contains(Polygon v, Point p){\n\
    \    int n = v.size();\n    bool x = false;\n    static constexpr int IN = 2;\n\
    \    static constexpr int ON = 1;\n    static constexpr int OUT = 0;\n    for\
    \ (int i = 0; i < n; ++i) {\n        Point a = v[i]-p, b = v[(i+1)%n]-p;\n   \
    \     if(fabs(cross(a, b)) < EPS && dot(a, b) < EPS) return ON;\n        if(a.y\
    \ > b.y) swap(a, b);\n        if(a.y < EPS && EPS < b.y && cross(a, b) > EPS)\
    \ x = !x;\n    }\n    return (x?IN:OUT);\n}\n\nreal diameter(Polygon v){\n   \
    \ int n = v.size();\n    if(n == 2) return abs(v[0]-v[1]);\n    int i = 0, j =\
    \ 0;\n    for (int k = 0; k < n; ++k) {\n        if(v[i] < v[k]) i = k;\n    \
    \    if(!(v[j] < v[k])) j = k;\n    }\n    real ret = 0;\n    int si = i, sj =\
    \ j;\n    while(i != sj || j != si){\n        ret = max(ret, abs(v[i]-v[j]));\n\
    \        if(cross(v[(i+1)%n]-v[i], v[(j+1)%n]-v[j]) < 0.0) i = (i+1)%n;\n    \
    \    else j = (j+1)%n;\n    }\n    return ret;\n}\n\nPolygon convexCut(Polygon\
    \ v, Line l){\n    Polygon q;\n    int n = v.size();\n    for (int i = 0; i <\
    \ n; ++i) {\n        Point a = v[i], b = v[(i+1)%n];\n        if(ccw(l.a, l.b,\
    \ a) != -1) q.push_back(a);\n        if(ccw(l.a, l.b, a)*ccw(l.a, l.b, b) < 0){\n\
    \            q.push_back(crossPoint(Line(a, b), l));\n        }\n    }\n    return\
    \ q;\n}\n\nreal closest_pair(Polygon &v, int l = 0, int r = -1){\n    if(!(~r)){\n\
    \        r = v.size();\n        sort(v.begin(),v.end());\n    }\n    if(r - l\
    \ < 2) {\n        return abs(v.front()-v.back());\n    }\n    int mid = (l+r)/2;\n\
    \    real p = v[mid].x;\n    real d = min(closest_pair(v, l, mid), closest_pair(v,\
    \ mid, r));\n    inplace_merge(v.begin()+l, v.begin()+mid, v.begin()+r, sorty);\n\
    \    Polygon u;\n    for (int i = l; i < r; ++i) {\n        if(fabs(v[i].x-p)\
    \ >= d) continue;\n        for (int j = 0; j < u.size(); ++j) {\n            real\
    \ dy = v[i].y-next(u.rbegin(), j)->y;\n            if(dy >= d) break;\n      \
    \      d = min(d, abs(v[i]-*next(u.rbegin(), j)));\n        }\n        u.emplace_back(v[i]);\n\
    \    }\n    return d;\n}\n\n/**\n * @brief \u5E7E\u4F55\u30E9\u30A4\u30D6\u30E9\
    \u30EA\n * @docs _md/geometry.md\n */\n#line 2 \"geometry/dualgraph.cpp\"\n\n\
    class DualGraph {\n    struct P {\n        int to, nxt, id, id2, rev;\n      \
    \  P(int to = 0, int nxt = 0, int id = 0, int rev = 0) : to(to), nxt(nxt), id(id),\
    \ rev(rev), id2(0) {};\n        bool operator!=(P x){ return to != x.to || nxt\
    \ != x.nxt || id != x.id || rev != x.rev; }\n    };\npublic:\n    int n, m;\n\
    \    Polygon v;\n    vector<vector<P>> G_;\n    vector<vector<int>> G;\n    vector<vector<Point>>\
    \ A;\n    DualGraph(Polygon v) : v(v), n(v.size()), G_(n), m(0) {}\n\n    void\
    \ add_point(Point P){ v.emplace_back(P); n++; G_.emplace_back(); }\n    void add_edge(int\
    \ a, int b){\n        G_[a].emplace_back(b, 0, m, 0);\n        G_[b].emplace_back(a,\
    \ 0, m++, 0);\n    }\n\n    void build(){\n        vector<int> l(m), r(m);\n \
    \       for (int i = 0; i < n; ++i) {\n            sort(G_[i].begin(), G_[i].end(),\
    \ [&](P &a, P &b){ return arg(v[a.to]-v[i]) < arg(v[b.to]-v[i]); });\n       \
    \     for (int j = 0; j < G_[i].size(); ++j) {\n                G_[i][j].nxt =\
    \ (j + 1) % G_[i].size();\n                if(i < G_[i][j].to) l[G_[i][j].id]\
    \ = j;\n                else r[G_[i][j].id] = j;\n            }\n        }\n \
    \       for (int i = 0; i < n; ++i) {\n            for (auto &&e : G_[i]) {\n\
    \                e.rev = (i < e.to ? r[e.id] : l[e.id]);\n            }\n    \
    \    }\n        int cur = 1;\n        A = move(vector<vector<Point>>());\n   \
    \     for (int i = 0; i < n; ++i) {\n            for (auto &&x : G_[i]) {\n  \
    \              if(x.id2) continue;\n                x.id2 = cur;\n           \
    \     A.emplace_back();\n                A.back().emplace_back(v[i]);\n      \
    \          auto e = &x;\n                while(e->to != i){\n                \
    \    A.back().emplace_back(v[e->to]);\n                    e = &G_[e->to][G_[e->to][e->rev].nxt];\n\
    \                    e->id2 = cur;\n                }\n                cur++;\n\
    \            }\n        }\n        for (int i = 0; i < n; ++i) {\n           \
    \ for (auto &&e : G_[i]) {\n                (i < e.to ? l[e.id] : r[e.id]) = e.id2-1;\n\
    \            }\n        }\n        G = move(vector<vector<int>>(A.size()));\n\
    \        for (int i = 0; i < m; ++i) {\n            G[l[i]].emplace_back(r[i]);\n\
    \            G[r[i]].emplace_back(l[i]);\n        }\n    }\n};\n\n/**\n * @brief\
    \ \u53CC\u5BFE\u30B0\u30E9\u30D5\u306E\u69CB\u7BC9\n * @docs _md/dualgraph.md\n\
    \ */\n"
  code: "#include \"../geometry/geometry.cpp\"\n\nclass DualGraph {\n    struct P\
    \ {\n        int to, nxt, id, id2, rev;\n        P(int to = 0, int nxt = 0, int\
    \ id = 0, int rev = 0) : to(to), nxt(nxt), id(id), rev(rev), id2(0) {};\n    \
    \    bool operator!=(P x){ return to != x.to || nxt != x.nxt || id != x.id ||\
    \ rev != x.rev; }\n    };\npublic:\n    int n, m;\n    Polygon v;\n    vector<vector<P>>\
    \ G_;\n    vector<vector<int>> G;\n    vector<vector<Point>> A;\n    DualGraph(Polygon\
    \ v) : v(v), n(v.size()), G_(n), m(0) {}\n\n    void add_point(Point P){ v.emplace_back(P);\
    \ n++; G_.emplace_back(); }\n    void add_edge(int a, int b){\n        G_[a].emplace_back(b,\
    \ 0, m, 0);\n        G_[b].emplace_back(a, 0, m++, 0);\n    }\n\n    void build(){\n\
    \        vector<int> l(m), r(m);\n        for (int i = 0; i < n; ++i) {\n    \
    \        sort(G_[i].begin(), G_[i].end(), [&](P &a, P &b){ return arg(v[a.to]-v[i])\
    \ < arg(v[b.to]-v[i]); });\n            for (int j = 0; j < G_[i].size(); ++j)\
    \ {\n                G_[i][j].nxt = (j + 1) % G_[i].size();\n                if(i\
    \ < G_[i][j].to) l[G_[i][j].id] = j;\n                else r[G_[i][j].id] = j;\n\
    \            }\n        }\n        for (int i = 0; i < n; ++i) {\n           \
    \ for (auto &&e : G_[i]) {\n                e.rev = (i < e.to ? r[e.id] : l[e.id]);\n\
    \            }\n        }\n        int cur = 1;\n        A = move(vector<vector<Point>>());\n\
    \        for (int i = 0; i < n; ++i) {\n            for (auto &&x : G_[i]) {\n\
    \                if(x.id2) continue;\n                x.id2 = cur;\n         \
    \       A.emplace_back();\n                A.back().emplace_back(v[i]);\n    \
    \            auto e = &x;\n                while(e->to != i){\n              \
    \      A.back().emplace_back(v[e->to]);\n                    e = &G_[e->to][G_[e->to][e->rev].nxt];\n\
    \                    e->id2 = cur;\n                }\n                cur++;\n\
    \            }\n        }\n        for (int i = 0; i < n; ++i) {\n           \
    \ for (auto &&e : G_[i]) {\n                (i < e.to ? l[e.id] : r[e.id]) = e.id2-1;\n\
    \            }\n        }\n        G = move(vector<vector<int>>(A.size()));\n\
    \        for (int i = 0; i < m; ++i) {\n            G[l[i]].emplace_back(r[i]);\n\
    \            G[r[i]].emplace_back(l[i]);\n        }\n    }\n};\n\n/**\n * @brief\
    \ \u53CC\u5BFE\u30B0\u30E9\u30D5\u306E\u69CB\u7BC9\n * @docs _md/dualgraph.md\n\
    \ */"
  dependsOn:
  - geometry/geometry.cpp
  isVerificationFile: false
  path: geometry/dualgraph.cpp
  requiredBy: []
  timestamp: '2020-11-23 18:34:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0273.test.cpp
documentation_of: geometry/dualgraph.cpp
layout: document
redirect_from:
- /library/geometry/dualgraph.cpp
- /library/geometry/dualgraph.cpp.html
title: "\u53CC\u5BFE\u30B0\u30E9\u30D5\u306E\u69CB\u7BC9"
---
## 説明
与えられた連結な平面グラフ(頂点が座標で表される)の双対グラフを構築する。