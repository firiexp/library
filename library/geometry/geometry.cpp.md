---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :question: 幾何ライブラリ <small>(geometry/geometry.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/geometry.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-28 23:17:17+09:00




## 説明
幾何に関するライブラリの詰め合わせ。いろいろあります

## verifyされた機能
- Point 構造体 (Point同士の加減、Pointのスカラー倍、比較(デフォルトは$x$座標)、入力)
- Polygon は vector\<Point> の別名
- $\mathrm{convex-hull}(v) $ : $v$の凸包を返す。

## Required by

* :x: <a href="dualgraph.cpp.html">geometry/dualgraph.cpp</a>


## Verified with

* :x: <a href="../../verify/test/aoj0273.test.cpp.html">test/aoj0273.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj0342.test.cpp.html">test/aoj0342.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
using real = double;
static constexpr real EPS = 1e-10;
struct Point {
    real x, y;
    Point& operator+=(const Point a) { x += a.x; y += a.y;  return *this; }
    Point& operator-=(const Point a) { x -= a.x; y -= a.y;  return *this; }
    Point& operator*=(const real k) { x *= k; y *= k;  return *this; }
    Point& operator/=(const real k) { x /= k; y /= k;  return *this; }
    Point operator+(const Point a) const {return Point(*this) += a; }
    Point operator-(const Point a) const {return Point(*this) -= a; }
    Point operator*(const real k) const {return Point(*this) *= k; }
    Point operator/(const real k) const {return Point(*this) /= k; }
    bool operator<(const Point &a) const { return (x != a.x ? x < a.x : y < a.y); }
    explicit Point(real a = 0, real b = 0) : x(a), y(b) {};
};
 
bool sorty(Point a, Point b){
    return (a.y != b.y ? a.y < b.y : a.x < b.x);
}
 
istream& operator>> (istream& s, Point& P){
    s >> P.x >> P.y;
    return s;
}
 
inline real dot(Point a, Point b){ return a.x*b.x + a.y*b.y; }
inline real cross(Point a, Point b){ return a.x*b.y - a.y*b.x; }
inline real abs(Point a){ return sqrt(dot(a, a)); }


real angle(Point A, Point B){
    return acos(dot(A, B)/abs(A)/abs(B));
}



static constexpr int COUNTER_CLOCKWISE = 1;
static constexpr int CLOCKWISE = -1;
static constexpr int ONLINE_BACK = 2;
static constexpr int ONLINE_FRONT = -2;
static constexpr int ON_SEGMENT = 0;
 
int ccw(Point a, Point b, Point c){
    b -= a; c -= a;
    if(cross(b, c) > EPS) return COUNTER_CLOCKWISE;
    if(cross(b, c) < -EPS) return CLOCKWISE;
    if(dot(b, c) < 0) return ONLINE_BACK;
    if(abs(b) < abs(c)) return ONLINE_FRONT;
    return ON_SEGMENT;
}
struct Segment {
    Point a, b;
    Segment(Point x, Point y) : a(x), b(y) {};
};
 
struct Line {
    Point a, b;
    Line(Point x, Point y) : a(x), b(y) {};
};
 
struct Circle{
    Point c; real r;
    Circle(Point c, real r): c(c), r(r) {};
};
 
using Polygon = vector<Point>;
 
bool intersect(Segment s, Segment t){
    return (ccw(s.a, s.b, t.a)*ccw(s.a, s.b, t.b) <= 0 &&
            ccw(t.a, t.b, s.a)*ccw(t.a, t.b, s.b) <= 0);
}

bool intersect(Segment s, Line t){
    int a = ccw(t.a, t.b, s.a), b = ccw(t.a, t.b, s.b);
    return (!(a&1) || !(b&1) || a != b);
}

Point polar(double r, double t){
    return Point(r*cos(t), r*sin(t));
}
 
double arg(Point p){
    return atan2(p.y, p.x);
}
 
static constexpr int CONTAIN = 0;
static constexpr int INSCRIBE = 1;
static constexpr int INTERSECT = 2;
static constexpr int CIRCUMSCRIBED = 3;
static constexpr int SEPARATE = 4;
 
int intersect(Circle c1, Circle c2){
    if(c1.r < c2.r) swap(c1, c2);
    real d = abs(c1.c-c2.c);
    real r = c1.r + c2.r;
    if(fabs(d-r) < EPS) return CIRCUMSCRIBED;
    if(d > r) return SEPARATE;
    if(fabs(d+c2.r-c1.r) < EPS) return INSCRIBE;
    if(d+c2.r < c1.r) return CONTAIN;
    return INTERSECT;
}
 
real distance(Line l, Point c){
    return abs(cross(l.b-l.a, c-l.a)/abs(l.b-l.a));
}
 
 
real distance(Segment s, Point c){
    if(dot(s.b-s.a, c-s.a) < EPS) return abs(c-s.a);
    if(dot(s.a-s.b, c-s.b) < EPS) return abs(c-s.b);
    return abs(cross(s.b-s.a, c-s.a)) / abs(s.a-s.b);
}
 
real distance(Segment s, Segment t){
    if(intersect(s, t)) return 0.0;
    return min({distance(s, t.a), distance(s, t.b),
                distance(t, s.a), distance(t, s.b)});
}
 
 
Point project(Line l, Point p){
    Point Q = l.b-l.a;
    return l.a + Q*(dot(p-l.a, Q) / dot(Q, Q));
}
 
 
Point project(Segment s, Point p){
    Point Q = s.b-s.a;
    return s.a + Q*(dot(p-s.a, Q) / dot(Q, Q));
}
 
Point refrect(Segment s, Point p){
    Point Q = project(s, p);
    return Q*2-p;
}
 
bool isOrthogonal(Segment s, Segment t){
    return fabs(dot(s.b-s.a, t.b-t.a)) < EPS;
}
 
bool isparallel(Segment s, Segment t){
    return fabs(cross(s.b-s.a, t.b-t.a)) < EPS;
}
 
 
Point crossPoint(Segment s, Segment t){
    real d1 = cross(s.b-s.a, t.b-t.a);
    real d2 = cross(s.b-s.a, s.b-t.a);
    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;
    return t.a+(t.b-t.a)*d2/d1;
}
 
Point crossPoint(Line s, Line t){
    real d1 = cross(s.b-s.a, t.b-t.a);
    real d2 = cross(s.b-s.a, s.b-t.a);
    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;
    return t.a+(t.b-t.a)*d2/d1;
}
 
Polygon crossPoint(Circle c, Line l){
    Point p = project(l, c.c), q = (l.b-l.a)/abs(l.b-l.a);
    if(abs(distance(l, c.c)-c.r) < EPS){
        return {p};
    }
    double k = sqrt(c.r*c.r-dot(p-c.c, p-c.c));
    return {p-q*k, p+q*k};
}
 
Polygon crossPoint(Circle c, Segment s){
    auto tmp = crossPoint(c, Line(s.a, s.b));
    Polygon ret;
    for (auto &&i : tmp) {
        if(distance(s, i) < EPS) ret.emplace_back(i);
    }
    return ret;
}
 
 
Polygon crossPoint(Circle c1, Circle c2){
    double d = abs(c1.c-c2.c);
    double a = acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
    double t = arg(c2.c-c1.c);
    return {c1.c+polar(c1.r, t+a), c1.c+polar(c1.r, t-a)};
}
 
Polygon tangent(Circle c1, Point p){
    Circle c2 = Circle(p, sqrt(dot(c1.c-p, c1.c-p)-c1.r*c1.r));
    return crossPoint(c1, c2);
}
vector<Line> tangent(Circle c1, Circle c2){
    vector<Line> ret;
    if(c1.r < c2.r) swap(c1, c2);
    double k = dot(c1.c-c2.c, c1.c-c2.c);
    if(abs(k) < EPS) return {};
    Point u = (c2.c-c1.c)/sqrt(k);
    Point v(-u.y, u.x);
    for (auto &&i : {-1, 1}) {
        double h = (c1.r+i*c2.r)/sqrt(k);
        if(abs(h*h-1) < EPS){
            ret.emplace_back(c1.c+u*c1.r, c1.c+(u+v)*c1.r);
        }else if(h*h < 1){
            Point u2 = u*h, v2 = v*sqrt(1-h*h);
            ret.emplace_back(c1.c+(u2+v2)*c1.r, c2.c-(u2+v2)*c2.r*i);
            ret.emplace_back(c1.c+(u2-v2)*c1.r, c2.c-(u2-v2)*c2.r*i);
        }
    }
    return ret;
}
 
real area(Polygon v){
    if(v.size() < 3) return 0.0;
    real ans = 0.0;
    for (int i = 0; i < v.size(); ++i) {
        ans += cross(v[i], v[(i+1)%v.size()]);
    }
    return ans/2;
}
 
real area(Circle c, Polygon &v){
    int n = v.size();
    real ans = 0.0;
    Polygon u;
    for (int i = 0; i < n; ++i) {
        u.emplace_back(v[i]);
        auto q = crossPoint(c, Segment(v[i], v[(i+1)%n]));
        for (auto &&j : q) {
            u.emplace_back(j);
        }
    }
    for (int i = 0; i < u.size(); ++i) {
        Point A = u[i]-c.c, B = u[(i+1)%u.size()]-c.c;
        if(abs(A) >= c.r+EPS || abs(B) >= c.r+EPS){
            Point C = polar(1, arg(B)-arg(A));
            ans += c.r*c.r*arg(C)/2;
        }else {
            ans += cross(A, B)/2;
        }
    }
    return ans;
}
 
Polygon convex_hull(Polygon v){
    int n = v.size();
    sort(v.begin(),v.end(), sorty);
    int k = 0;
    Polygon ret(n*2);
    for (int i = 0; i < n; ++i) {
        while(k > 1 && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1]) < 0) k--;
        ret[k++] = v[i];
    }
    for(int i = n-2, t=k; i >= 0; i--){
        while(k > t && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1]) < 0) k--;
        ret[k++] = v[i];
    }
    ret.resize(k-1);
    return ret;
}
 
bool isconvex(Polygon v){
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if(ccw(v[(i+n-1)%n], v[i], v[(i+1)%n]) == CLOCKWISE) return false;
    }
    return true;
}
 
int contains(Polygon v, Point p){
    int n = v.size();
    bool x = false;
    static constexpr int IN = 2;
    static constexpr int ON = 1;
    static constexpr int OUT = 0;
    for (int i = 0; i < n; ++i) {
        Point a = v[i]-p, b = v[(i+1)%n]-p;
        if(fabs(cross(a, b)) < EPS && dot(a, b) < EPS) return ON;
        if(a.y > b.y) swap(a, b);
        if(a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
    }
    return (x?IN:OUT);
}
 
real diameter(Polygon v){
    int n = v.size();
    if(n == 2) return abs(v[0]-v[1]);
    int i = 0, j = 0;
    for (int k = 0; k < n; ++k) {
        if(v[i] < v[k]) i = k;
        if(!(v[j] < v[k])) j = k;
    }
    real ret = 0;
    int si = i, sj = j;
    while(i != sj || j != si){
        ret = max(ret, abs(v[i]-v[j]));
        if(cross(v[(i+1)%n]-v[i], v[(j+1)%n]-v[j]) < 0.0) i = (i+1)%n;
        else j = (j+1)%n;
    }
    return ret;
}
 
Polygon convexCut(Polygon v, Line l){
    Polygon q;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        Point a = v[i], b = v[(i+1)%n];
        if(ccw(l.a, l.b, a) != -1) q.push_back(a);
        if(ccw(l.a, l.b, a)*ccw(l.a, l.b, b) < 0){
            q.push_back(crossPoint(Line(a, b), l));
        }
    }
    return q;
}
 
real closest_pair(Polygon &v, int l = 0, int r = -1){
    if(!(~r)){
        r = v.size();
        sort(v.begin(),v.end());
    }
    if(r - l < 2) {
        return abs(v.front()-v.back());
    }
    int mid = (l+r)/2;
    real p = v[mid].x;
    real d = min(closest_pair(v, l, mid), closest_pair(v, mid, r));
    inplace_merge(v.begin()+l, v.begin()+mid, v.begin()+r, sorty);
    Polygon u;
    for (int i = l; i < r; ++i) {
        if(fabs(v[i].x-p) >= d) continue;
        for (int j = 0; j < u.size(); ++j) {
            real dy = v[i].y-next(u.rbegin(), j)->y;
            if(dy >= d) break;
            d = min(d, abs(v[i]-*next(u.rbegin(), j)));
        }
        u.emplace_back(v[i]);
    }
    return d;
}

/**
 * @brief 幾何ライブラリ
 * @docs _md/geometry.md
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/geometry.cpp"
using real = double;
static constexpr real EPS = 1e-10;
struct Point {
    real x, y;
    Point& operator+=(const Point a) { x += a.x; y += a.y;  return *this; }
    Point& operator-=(const Point a) { x -= a.x; y -= a.y;  return *this; }
    Point& operator*=(const real k) { x *= k; y *= k;  return *this; }
    Point& operator/=(const real k) { x /= k; y /= k;  return *this; }
    Point operator+(const Point a) const {return Point(*this) += a; }
    Point operator-(const Point a) const {return Point(*this) -= a; }
    Point operator*(const real k) const {return Point(*this) *= k; }
    Point operator/(const real k) const {return Point(*this) /= k; }
    bool operator<(const Point &a) const { return (x != a.x ? x < a.x : y < a.y); }
    explicit Point(real a = 0, real b = 0) : x(a), y(b) {};
};
 
bool sorty(Point a, Point b){
    return (a.y != b.y ? a.y < b.y : a.x < b.x);
}
 
istream& operator>> (istream& s, Point& P){
    s >> P.x >> P.y;
    return s;
}
 
inline real dot(Point a, Point b){ return a.x*b.x + a.y*b.y; }
inline real cross(Point a, Point b){ return a.x*b.y - a.y*b.x; }
inline real abs(Point a){ return sqrt(dot(a, a)); }


real angle(Point A, Point B){
    return acos(dot(A, B)/abs(A)/abs(B));
}



static constexpr int COUNTER_CLOCKWISE = 1;
static constexpr int CLOCKWISE = -1;
static constexpr int ONLINE_BACK = 2;
static constexpr int ONLINE_FRONT = -2;
static constexpr int ON_SEGMENT = 0;
 
int ccw(Point a, Point b, Point c){
    b -= a; c -= a;
    if(cross(b, c) > EPS) return COUNTER_CLOCKWISE;
    if(cross(b, c) < -EPS) return CLOCKWISE;
    if(dot(b, c) < 0) return ONLINE_BACK;
    if(abs(b) < abs(c)) return ONLINE_FRONT;
    return ON_SEGMENT;
}
struct Segment {
    Point a, b;
    Segment(Point x, Point y) : a(x), b(y) {};
};
 
struct Line {
    Point a, b;
    Line(Point x, Point y) : a(x), b(y) {};
};
 
struct Circle{
    Point c; real r;
    Circle(Point c, real r): c(c), r(r) {};
};
 
using Polygon = vector<Point>;
 
bool intersect(Segment s, Segment t){
    return (ccw(s.a, s.b, t.a)*ccw(s.a, s.b, t.b) <= 0 &&
            ccw(t.a, t.b, s.a)*ccw(t.a, t.b, s.b) <= 0);
}

bool intersect(Segment s, Line t){
    int a = ccw(t.a, t.b, s.a), b = ccw(t.a, t.b, s.b);
    return (!(a&1) || !(b&1) || a != b);
}

Point polar(double r, double t){
    return Point(r*cos(t), r*sin(t));
}
 
double arg(Point p){
    return atan2(p.y, p.x);
}
 
static constexpr int CONTAIN = 0;
static constexpr int INSCRIBE = 1;
static constexpr int INTERSECT = 2;
static constexpr int CIRCUMSCRIBED = 3;
static constexpr int SEPARATE = 4;
 
int intersect(Circle c1, Circle c2){
    if(c1.r < c2.r) swap(c1, c2);
    real d = abs(c1.c-c2.c);
    real r = c1.r + c2.r;
    if(fabs(d-r) < EPS) return CIRCUMSCRIBED;
    if(d > r) return SEPARATE;
    if(fabs(d+c2.r-c1.r) < EPS) return INSCRIBE;
    if(d+c2.r < c1.r) return CONTAIN;
    return INTERSECT;
}
 
real distance(Line l, Point c){
    return abs(cross(l.b-l.a, c-l.a)/abs(l.b-l.a));
}
 
 
real distance(Segment s, Point c){
    if(dot(s.b-s.a, c-s.a) < EPS) return abs(c-s.a);
    if(dot(s.a-s.b, c-s.b) < EPS) return abs(c-s.b);
    return abs(cross(s.b-s.a, c-s.a)) / abs(s.a-s.b);
}
 
real distance(Segment s, Segment t){
    if(intersect(s, t)) return 0.0;
    return min({distance(s, t.a), distance(s, t.b),
                distance(t, s.a), distance(t, s.b)});
}
 
 
Point project(Line l, Point p){
    Point Q = l.b-l.a;
    return l.a + Q*(dot(p-l.a, Q) / dot(Q, Q));
}
 
 
Point project(Segment s, Point p){
    Point Q = s.b-s.a;
    return s.a + Q*(dot(p-s.a, Q) / dot(Q, Q));
}
 
Point refrect(Segment s, Point p){
    Point Q = project(s, p);
    return Q*2-p;
}
 
bool isOrthogonal(Segment s, Segment t){
    return fabs(dot(s.b-s.a, t.b-t.a)) < EPS;
}
 
bool isparallel(Segment s, Segment t){
    return fabs(cross(s.b-s.a, t.b-t.a)) < EPS;
}
 
 
Point crossPoint(Segment s, Segment t){
    real d1 = cross(s.b-s.a, t.b-t.a);
    real d2 = cross(s.b-s.a, s.b-t.a);
    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;
    return t.a+(t.b-t.a)*d2/d1;
}
 
Point crossPoint(Line s, Line t){
    real d1 = cross(s.b-s.a, t.b-t.a);
    real d2 = cross(s.b-s.a, s.b-t.a);
    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;
    return t.a+(t.b-t.a)*d2/d1;
}
 
Polygon crossPoint(Circle c, Line l){
    Point p = project(l, c.c), q = (l.b-l.a)/abs(l.b-l.a);
    if(abs(distance(l, c.c)-c.r) < EPS){
        return {p};
    }
    double k = sqrt(c.r*c.r-dot(p-c.c, p-c.c));
    return {p-q*k, p+q*k};
}
 
Polygon crossPoint(Circle c, Segment s){
    auto tmp = crossPoint(c, Line(s.a, s.b));
    Polygon ret;
    for (auto &&i : tmp) {
        if(distance(s, i) < EPS) ret.emplace_back(i);
    }
    return ret;
}
 
 
Polygon crossPoint(Circle c1, Circle c2){
    double d = abs(c1.c-c2.c);
    double a = acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
    double t = arg(c2.c-c1.c);
    return {c1.c+polar(c1.r, t+a), c1.c+polar(c1.r, t-a)};
}
 
Polygon tangent(Circle c1, Point p){
    Circle c2 = Circle(p, sqrt(dot(c1.c-p, c1.c-p)-c1.r*c1.r));
    return crossPoint(c1, c2);
}
vector<Line> tangent(Circle c1, Circle c2){
    vector<Line> ret;
    if(c1.r < c2.r) swap(c1, c2);
    double k = dot(c1.c-c2.c, c1.c-c2.c);
    if(abs(k) < EPS) return {};
    Point u = (c2.c-c1.c)/sqrt(k);
    Point v(-u.y, u.x);
    for (auto &&i : {-1, 1}) {
        double h = (c1.r+i*c2.r)/sqrt(k);
        if(abs(h*h-1) < EPS){
            ret.emplace_back(c1.c+u*c1.r, c1.c+(u+v)*c1.r);
        }else if(h*h < 1){
            Point u2 = u*h, v2 = v*sqrt(1-h*h);
            ret.emplace_back(c1.c+(u2+v2)*c1.r, c2.c-(u2+v2)*c2.r*i);
            ret.emplace_back(c1.c+(u2-v2)*c1.r, c2.c-(u2-v2)*c2.r*i);
        }
    }
    return ret;
}
 
real area(Polygon v){
    if(v.size() < 3) return 0.0;
    real ans = 0.0;
    for (int i = 0; i < v.size(); ++i) {
        ans += cross(v[i], v[(i+1)%v.size()]);
    }
    return ans/2;
}
 
real area(Circle c, Polygon &v){
    int n = v.size();
    real ans = 0.0;
    Polygon u;
    for (int i = 0; i < n; ++i) {
        u.emplace_back(v[i]);
        auto q = crossPoint(c, Segment(v[i], v[(i+1)%n]));
        for (auto &&j : q) {
            u.emplace_back(j);
        }
    }
    for (int i = 0; i < u.size(); ++i) {
        Point A = u[i]-c.c, B = u[(i+1)%u.size()]-c.c;
        if(abs(A) >= c.r+EPS || abs(B) >= c.r+EPS){
            Point C = polar(1, arg(B)-arg(A));
            ans += c.r*c.r*arg(C)/2;
        }else {
            ans += cross(A, B)/2;
        }
    }
    return ans;
}
 
Polygon convex_hull(Polygon v){
    int n = v.size();
    sort(v.begin(),v.end(), sorty);
    int k = 0;
    Polygon ret(n*2);
    for (int i = 0; i < n; ++i) {
        while(k > 1 && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1]) < 0) k--;
        ret[k++] = v[i];
    }
    for(int i = n-2, t=k; i >= 0; i--){
        while(k > t && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1]) < 0) k--;
        ret[k++] = v[i];
    }
    ret.resize(k-1);
    return ret;
}
 
bool isconvex(Polygon v){
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if(ccw(v[(i+n-1)%n], v[i], v[(i+1)%n]) == CLOCKWISE) return false;
    }
    return true;
}
 
int contains(Polygon v, Point p){
    int n = v.size();
    bool x = false;
    static constexpr int IN = 2;
    static constexpr int ON = 1;
    static constexpr int OUT = 0;
    for (int i = 0; i < n; ++i) {
        Point a = v[i]-p, b = v[(i+1)%n]-p;
        if(fabs(cross(a, b)) < EPS && dot(a, b) < EPS) return ON;
        if(a.y > b.y) swap(a, b);
        if(a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
    }
    return (x?IN:OUT);
}
 
real diameter(Polygon v){
    int n = v.size();
    if(n == 2) return abs(v[0]-v[1]);
    int i = 0, j = 0;
    for (int k = 0; k < n; ++k) {
        if(v[i] < v[k]) i = k;
        if(!(v[j] < v[k])) j = k;
    }
    real ret = 0;
    int si = i, sj = j;
    while(i != sj || j != si){
        ret = max(ret, abs(v[i]-v[j]));
        if(cross(v[(i+1)%n]-v[i], v[(j+1)%n]-v[j]) < 0.0) i = (i+1)%n;
        else j = (j+1)%n;
    }
    return ret;
}
 
Polygon convexCut(Polygon v, Line l){
    Polygon q;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        Point a = v[i], b = v[(i+1)%n];
        if(ccw(l.a, l.b, a) != -1) q.push_back(a);
        if(ccw(l.a, l.b, a)*ccw(l.a, l.b, b) < 0){
            q.push_back(crossPoint(Line(a, b), l));
        }
    }
    return q;
}
 
real closest_pair(Polygon &v, int l = 0, int r = -1){
    if(!(~r)){
        r = v.size();
        sort(v.begin(),v.end());
    }
    if(r - l < 2) {
        return abs(v.front()-v.back());
    }
    int mid = (l+r)/2;
    real p = v[mid].x;
    real d = min(closest_pair(v, l, mid), closest_pair(v, mid, r));
    inplace_merge(v.begin()+l, v.begin()+mid, v.begin()+r, sorty);
    Polygon u;
    for (int i = l; i < r; ++i) {
        if(fabs(v[i].x-p) >= d) continue;
        for (int j = 0; j < u.size(); ++j) {
            real dy = v[i].y-next(u.rbegin(), j)->y;
            if(dy >= d) break;
            d = min(d, abs(v[i]-*next(u.rbegin(), j)));
        }
        u.emplace_back(v[i]);
    }
    return d;
}

/**
 * @brief 幾何ライブラリ
 * @docs _md/geometry.md
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

