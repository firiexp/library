---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/geometry.cpp
    title: "\u5E7E\u4F55\u30E9\u30A4\u30D6\u30E9\u30EA(Geometry)"
  - icon: ':heavy_check_mark:'
    path: geometry/half_plane_intersection.cpp
    title: "\u534A\u5E73\u9762\u5171\u901A\u90E8\u5206(Half-Plane Intersection)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: 1e-8
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
  bundledCode: "#line 1 \"test/aoj_cgl_4_c_half_plane_intersection.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C\"\
    \n#define ERROR \"1e-8\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cmath>\n#include <deque>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\n\nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace\
    \ std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\n\
    template<class T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
    \n    constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0),\
    \ size(0), interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n\
    \        int len = size - idx;\n        memmove(buf, buf + idx, len);\n      \
    \  if (interactive) {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin))\
    \ size = len + (int)strlen(buf + len);\n            else size = len;\n       \
    \ } else {\n            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void\
    \ ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void\
    \ ensure_interactive() {\n        if (idx == size) load();\n    }\n\n    inline\
    \ char skip() {\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            return buf[idx++];\n\
    \        }\n        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n\
    \            ++idx;\n            ensure();\n        }\n        return buf[idx++];\n\
    \    }\n\n    template<class T, typename enable_if<is_integral<T>::value, int>::type\
    \ = 0>\n    void read(T &x) {\n        if (interactive) {\n            char c\
    \ = skip();\n            bool neg = false;\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    neg = true;\n      \
    \              ensure_interactive();\n                    c = buf[idx++];\n  \
    \              }\n            }\n            x = 0;\n            while (c >= '0')\
    \ {\n                x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class Next, class... Tail>\n    void read(Head &head, Next &next, Tail &...tail)\
    \ {\n        read(head);\n        read(next, tail...);\n    }\n\n    template<class\
    \ T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void write_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n \
    \       write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
    \        write_range(s.data(), s.size());\n    }\n\n    void write(char c) {\n\
    \        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void write(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type,\
    \ string>::value, int>::type = 0>\n    void write(const T &a) {\n        bool\
    \ first = true;\n        for (auto &&x : a) {\n            if (!first) pc(' ');\n\
    \            first = false;\n            write(x);\n        }\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner &in, T &x) {\n  \
    \  in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter &operator<<(Printer\
    \ &out, const T &x) {\n    out.write(x);\n    return out;\n}\n\n/**\n * @brief\
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"geometry/geometry.cpp\"\
    \n// \u51F8\u5305\u306F\u540C\u3058\u9802\u70B9\u304C\u542B\u307E\u308C\u3066\u3044\
    \u308B\u3068\u30D0\u30B0\u308B\nusing real = double;\nstatic constexpr real EPS\
    \ = 1e-10;\nconst real pi = acos(-1);\n\nstruct Point {\n    real x, y;\n    Point&\
    \ operator+=(const Point a) { x += a.x; y += a.y;  return *this; }\n    Point&\
    \ operator-=(const Point a) { x -= a.x; y -= a.y;  return *this; }\n    Point&\
    \ operator*=(const real k) { x *= k; y *= k;  return *this; }\n    Point& operator/=(const\
    \ real k) { x /= k; y /= k;  return *this; }\n    Point operator+(const Point\
    \ a) const {return Point(*this) += a; }\n    Point operator-(const Point a) const\
    \ {return Point(*this) -= a; }\n    Point operator*(const real k) const {return\
    \ Point(*this) *= k; }\n    Point operator/(const real k) const {return Point(*this)\
    \ /= k; }\n    bool operator<(const Point &a) const { return (x != a.x ? x < a.x\
    \ : y < a.y); }\n    explicit Point(real a = 0, real b = 0) : x(a), y(b) {};\n\
    };\n\nbool sorty(Point a, Point b) {\n    return (a.y != b.y ? a.y < b.y : a.x\
    \ < b.x);\n}\n\nistream &operator>>(istream &s, Point &P) {\n    s >> P.x >> P.y;\n\
    \    return s;\n}\n\ninline real dot(Point a, Point b) { return a.x * b.x + a.y\
    \ * b.y; }\n\ninline real cross(Point a, Point b) { return a.x * b.y - a.y * b.x;\
    \ }\n\ninline real abs(Point a) { return sqrt(dot(a, a)); }\n\nreal angle(Point\
    \ A, Point B) {\n    return acos(dot(A, B) / abs(A) / abs(B));\n}\n\nstatic constexpr\
    \ int COUNTER_CLOCKWISE = 1;\nstatic constexpr int CLOCKWISE = -1;\nstatic constexpr\
    \ int ONLINE_BACK = 2;\nstatic constexpr int ONLINE_FRONT = -2;\nstatic constexpr\
    \ int ON_SEGMENT = 0;\n\nint ccw(Point a, Point b, Point c) {\n    b -= a;\n \
    \   c -= a;\n    if (cross(b, c) > EPS)\n        return COUNTER_CLOCKWISE;\n \
    \   if (cross(b, c) < -EPS)\n        return CLOCKWISE;\n    if (dot(b, c) < 0)\n\
    \        return ONLINE_BACK;\n    if (abs(b) < abs(c))\n        return ONLINE_FRONT;\n\
    \    return ON_SEGMENT;\n}\n\nstruct Segment {\n    Point a, b;\n\n    Segment(Point\
    \ x, Point y) : a(x), b(y) {};\n};\n\nstruct Line {\n    Point a, b;\n\n    Line(Point\
    \ x, Point y) : a(x), b(y) {};\n};\n\nstruct Circle {\n    Point c;\n    real\
    \ r;\n\n    Circle(Point c, real r) : c(c), r(r) {};\n};\n\nusing Polygon = vector<Point>;\n\
    \nbool intersect(Segment s, Segment t) {\n    return (ccw(s.a, s.b, t.a) * ccw(s.a,\
    \ s.b, t.b) <= 0 &&\n            ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0);\n\
    }\n\nbool intersect(Segment s, Line t) {\n    int a = ccw(t.a, t.b, s.a), b =\
    \ ccw(t.a, t.b, s.b);\n    return (!(a & 1) || !(b & 1) || a != b);\n}\n\nPoint\
    \ polar(double r, double t) {\n    return Point(r * cos(t), r * sin(t));\n}\n\n\
    double arg(Point p) {\n    return atan2(p.y, p.x);\n}\n\nstatic constexpr int\
    \ CONTAIN = 0;\nstatic constexpr int INSCRIBE = 1;\nstatic constexpr int INTERSECT\
    \ = 2;\nstatic constexpr int CIRCUMSCRIBED = 3;\nstatic constexpr int SEPARATE\
    \ = 4;\n\nint intersect(Circle c1, Circle c2) {\n    if (c1.r < c2.r)\n      \
    \  swap(c1, c2);\n    real d = abs(c1.c - c2.c);\n    real r = c1.r + c2.r;\n\
    \    if (fabs(d - r) < EPS)\n        return CIRCUMSCRIBED;\n    if (d > r)\n \
    \       return SEPARATE;\n    if (fabs(d + c2.r - c1.r) < EPS)\n        return\
    \ INSCRIBE;\n    if (d + c2.r < c1.r)\n        return CONTAIN;\n    return INTERSECT;\n\
    }\n\nreal distance(Line l, Point c) {\n    return abs(cross(l.b - l.a, c - l.a)\
    \ / abs(l.b - l.a));\n}\n\nreal distance(Segment s, Point c) {\n    if (dot(s.b\
    \ - s.a, c - s.a) < EPS)\n        return abs(c - s.a);\n    if (dot(s.a - s.b,\
    \ c - s.b) < EPS)\n        return abs(c - s.b);\n    return abs(cross(s.b - s.a,\
    \ c - s.a)) / abs(s.a - s.b);\n}\n\nreal distance(Segment s, Segment t) {\n  \
    \  if (intersect(s, t))\n        return 0.0;\n    return min({distance(s, t.a),\
    \ distance(s, t.b),\n                distance(t, s.a), distance(t, s.b)});\n}\n\
    \nPoint project(Line l, Point p) {\n    Point Q = l.b - l.a;\n    return l.a +\
    \ Q * (dot(p - l.a, Q) / dot(Q, Q));\n}\n\nPoint project(Segment s, Point p) {\n\
    \    Point Q = s.b - s.a;\n    return s.a + Q * (dot(p - s.a, Q) / dot(Q, Q));\n\
    }\n\nPoint refrect(Segment s, Point p) {\n    Point Q = project(s, p);\n    return\
    \ Q * 2 - p;\n}\n\nbool isOrthogonal(Segment s, Segment t) {\n    return fabs(dot(s.b\
    \ - s.a, t.b - t.a)) < EPS;\n}\n\nbool isparallel(Segment s, Segment t) {\n  \
    \  return fabs(cross(s.b - s.a, t.b - t.a)) < EPS;\n}\n\nPoint crossPoint(Segment\
    \ s, Segment t) {\n    real d1 = cross(s.b - s.a, t.b - t.a);\n    real d2 = cross(s.b\
    \ - s.a, s.b - t.a);\n    if (fabs(d1) < EPS && fabs(d2) < EPS)\n        return\
    \ t.a;\n    return t.a + (t.b - t.a) * d2 / d1;\n}\n\nPoint crossPoint(Line s,\
    \ Line t) {\n    real d1 = cross(s.b - s.a, t.b - t.a);\n    real d2 = cross(s.b\
    \ - s.a, s.b - t.a);\n    if (fabs(d1) < EPS && fabs(d2) < EPS)\n        return\
    \ t.a;\n    return t.a + (t.b - t.a) * d2 / d1;\n}\n\nPolygon crossPoint(Circle\
    \ c, Line l) {\n    Point p = project(l, c.c), q = (l.b - l.a) / abs(l.b - l.a);\n\
    \    if (abs(distance(l, c.c) - c.r) < EPS) {\n        return {p};\n    }\n  \
    \  double k = sqrt(c.r * c.r - dot(p - c.c, p - c.c));\n    return {p - q * k,\
    \ p + q * k};\n}\n\nPolygon crossPoint(Circle c, Segment s) {\n    auto tmp =\
    \ crossPoint(c, Line(s.a, s.b));\n    Polygon ret;\n    for (auto &&i: tmp) {\n\
    \        if (distance(s, i) < EPS)\n            ret.emplace_back(i);\n    }\n\
    \    return ret;\n}\n\nPolygon crossPoint(Circle c1, Circle c2) {\n    double\
    \ d = abs(c1.c - c2.c);\n    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r)\
    \ / (2 * c1.r * d));\n    double t = arg(c2.c - c1.c);\n    return {c1.c + polar(c1.r,\
    \ t + a), c1.c + polar(c1.r, t - a)};\n}\n\nPolygon tangent(Circle c1, Point p)\
    \ {\n    Circle c2 = Circle(p, sqrt(dot(c1.c - p, c1.c - p) - c1.r * c1.r));\n\
    \    return crossPoint(c1, c2);\n}\n\nvector<Line> tangent(Circle c1, Circle c2)\
    \ {\n    vector<Line> ret;\n    if (c1.r < c2.r)\n        swap(c1, c2);\n    double\
    \ k = dot(c1.c - c2.c, c1.c - c2.c);\n    if (abs(k) < EPS)\n        return {};\n\
    \    Point u = (c2.c - c1.c) / sqrt(k);\n    Point v(-u.y, u.x);\n    for (auto\
    \ &&i: {-1, 1}) {\n        double h = (c1.r + i * c2.r) / sqrt(k);\n        if\
    \ (abs(h * h - 1) < EPS) {\n            ret.emplace_back(c1.c + u * c1.r, c1.c\
    \ + (u + v) * c1.r);\n        } else if (h * h < 1) {\n            Point u2 =\
    \ u * h, v2 = v * sqrt(1 - h * h);\n            ret.emplace_back(c1.c + (u2 +\
    \ v2) * c1.r, c2.c - (u2 + v2) * c2.r * i);\n            ret.emplace_back(c1.c\
    \ + (u2 - v2) * c1.r, c2.c - (u2 - v2) * c2.r * i);\n        }\n    }\n    return\
    \ ret;\n}\n\nreal area(Polygon v) {\n    if (v.size() < 3)\n        return 0.0;\n\
    \    real ans = 0.0;\n    for (int i = 0; i < v.size(); ++i) {\n        ans +=\
    \ cross(v[i], v[(i + 1) % v.size()]);\n    }\n    return ans / 2;\n}\n\nreal area(Circle\
    \ c, Polygon &v) {\n    int n = v.size();\n    real ans = 0.0;\n    Polygon u;\n\
    \    for (int i = 0; i < n; ++i) {\n        u.emplace_back(v[i]);\n        auto\
    \ q = crossPoint(c, Segment(v[i], v[(i + 1) % n]));\n        for (auto &&j: q)\
    \ {\n            u.emplace_back(j);\n        }\n    }\n    for (int i = 0; i <\
    \ u.size(); ++i) {\n        Point A = u[i] - c.c, B = u[(i + 1) % u.size()] -\
    \ c.c;\n        if (abs(A) >= c.r + EPS || abs(B) >= c.r + EPS) {\n          \
    \  Point C = polar(1, arg(B) - arg(A));\n            ans += c.r * c.r * arg(C)\
    \ / 2;\n        } else {\n            ans += cross(A, B) / 2;\n        }\n   \
    \ }\n    return ans;\n}\n\nreal area(Circle a, Circle b) {\n    auto d = abs(a.c\
    \ - b.c);\n    if (a.r + b.r <= d + EPS)\n        return 0;\n    else if (d <=\
    \ abs(a.r - b.r))\n        return pi * min(a.r, b.r) * min(a.r, b.r);\n    real\
    \ p = 2 * acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));\n    real q =\
    \ 2 * acos((b.r * b.r + d * d - a.r * a.r) / (2 * b.r * d));\n    return a.r *\
    \ a.r * (p - sin(p)) / 2 + b.r * b.r * (q - sin(q)) / 2;\n}\n\nPolygon convex_hull(Polygon\
    \ v) {\n    int n = v.size();\n    sort(v.begin(), v.end(), sorty);\n    int k\
    \ = 0;\n    Polygon ret(n * 2);\n    for (int i = 0; i < n; ++i) {\n        while\
    \ (k > 1 && cross(ret[k - 1] - ret[k - 2], v[i] - ret[k - 1]) < 0)\n         \
    \   k--;\n        ret[k++] = v[i];\n    }\n    for (int i = n - 2, t = k; i >=\
    \ 0; i--) {\n        while (k > t && cross(ret[k - 1] - ret[k - 2], v[i] - ret[k\
    \ - 1]) < 0)\n            k--;\n        ret[k++] = v[i];\n    }\n    ret.resize(k\
    \ - 1);\n    return ret;\n}\n\nbool isconvex(Polygon v) {\n    int n = v.size();\n\
    \    for (int i = 0; i < n; ++i) {\n        if (ccw(v[(i + n - 1) % n], v[i],\
    \ v[(i + 1) % n]) == CLOCKWISE)\n            return false;\n    }\n    return\
    \ true;\n}\n\nint contains(Polygon v, Point p) {\n    int n = v.size();\n    bool\
    \ x = false;\n    static constexpr int IN = 2, ON = 1, OUT = 0;\n    for (int\
    \ i = 0; i < n; ++i) {\n        Point a = v[i] - p, b = v[(i + 1) % n] - p;\n\
    \        if (fabs(cross(a, b)) < EPS && dot(a, b) < EPS)\n            return ON;\n\
    \        if (a.y > b.y)\n            swap(a, b);\n        if (a.y < EPS && EPS\
    \ < b.y && cross(a, b) > EPS)\n            x = !x;\n    }\n    return (x ? IN\
    \ : OUT);\n}\n\nint contains_convex(Polygon &v, Point p) {\n    int a = 1, b =\
    \ v.size() - 1;\n    static constexpr int IN = 2, ON = 1, OUT = 0;\n    if (v.size()\
    \ < 3)\n        return (ccw(v.front(), v.back(), p) & 1) == 0 ? ON : OUT;\n  \
    \  if (ccw(v[0], v[a], v[b]) > 0)\n        swap(a, b);\n    int la = ccw(v[0],\
    \ v[a], p), lb = ccw(v[0], v[b], p);\n    if ((la & 1) == 0 || (lb & 1) == 0)\n\
    \        return ON;\n    if (la > 0 || lb < 0)\n        return OUT;\n    while\
    \ (abs(a - b) > 1) {\n        int c = (a + b) / 2;\n        int val = ccw(v[0],\
    \ v[c], p);\n        (val > 0 ? b : a) = c;\n    }\n    int res = ccw(v[a], v[b],\
    \ p);\n    if ((res & 1) == 0)\n        return ON;\n    return res < 0 ? IN :\
    \ OUT;\n}\n\nreal diameter(Polygon v) {\n    int n = v.size();\n    if (n == 2)\n\
    \        return abs(v[0] - v[1]);\n    int i = 0, j = 0;\n    for (int k = 0;\
    \ k < n; ++k) {\n        if (v[i] < v[k])\n            i = k;\n        if (!(v[j]\
    \ < v[k]))\n            j = k;\n    }\n    real ret = 0;\n    int si = i, sj =\
    \ j;\n    while (i != sj || j != si) {\n        ret = max(ret, abs(v[i] - v[j]));\n\
    \        if (cross(v[(i + 1) % n] - v[i], v[(j + 1) % n] - v[j]) < 0.0)\n    \
    \        i = (i + 1) % n;\n        else\n            j = (j + 1) % n;\n    }\n\
    \    return ret;\n}\n\nPolygon convexCut(Polygon v, Line l) {\n    Polygon q;\n\
    \    int n = v.size();\n    for (int i = 0; i < n; ++i) {\n        Point a = v[i],\
    \ b = v[(i + 1) % n];\n        if (ccw(l.a, l.b, a) != -1)\n            q.push_back(a);\n\
    \        if (ccw(l.a, l.b, a) * ccw(l.a, l.b, b) < 0) {\n            q.push_back(crossPoint(Line(a,\
    \ b), l));\n        }\n    }\n    return q;\n}\n\nreal closest_pair(Polygon &v,\
    \ int l = 0, int r = -1) {\n    if (!(~r)) {\n        r = v.size();\n        sort(v.begin(),\
    \ v.end());\n    }\n    if (r - l < 2) {\n        return abs(v.front() - v.back());\n\
    \    }\n    int mid = (l + r) / 2;\n    real p = v[mid].x;\n    real d = min(closest_pair(v,\
    \ l, mid), closest_pair(v, mid, r));\n    inplace_merge(v.begin() + l, v.begin()\
    \ + mid, v.begin() + r, sorty);\n    Polygon u;\n    for (int i = l; i < r; ++i)\
    \ {\n        if (fabs(v[i].x - p) >= d)\n            continue;\n        for (int\
    \ j = 0; j < u.size(); ++j) {\n            real dy = v[i].y - next(u.rbegin(),\
    \ j)->y;\n            if (dy >= d)\n                break;\n            d = min(d,\
    \ abs(v[i] - *next(u.rbegin(), j)));\n        }\n        u.emplace_back(v[i]);\n\
    \    }\n    return d;\n}\n\n/**\n * @brief \u5E7E\u4F55\u30E9\u30A4\u30D6\u30E9\
    \u30EA(Geometry)\n */\n#line 2 \"geometry/half_plane_intersection.cpp\"\n\nnamespace\
    \ internal_half_plane_intersection {\n\nstruct HalfPlane {\n    Point p, pq;\n\
    \    real angle;\n\n    HalfPlane() = default;\n\n    explicit HalfPlane(const\
    \ Line &l)\n        : p(l.a), pq(l.b - l.a), angle(atan2(pq.y, pq.x)) {}\n\n \
    \   bool operator<(const HalfPlane &other) const {\n        if (fabs(angle - other.angle)\
    \ > EPS) return angle < other.angle;\n        return cross(pq, other.p - p) <\
    \ 0;\n    }\n\n    bool outside(Point r) const {\n        return cross(pq, r -\
    \ p) < -EPS;\n    }\n};\n\nPoint intersection(const HalfPlane &s, const HalfPlane\
    \ &t) {\n    real a = cross(t.p - s.p, t.pq) / cross(s.pq, t.pq);\n    return\
    \ s.p + s.pq * a;\n}\n\nbool same_point(Point a, Point b) {\n    return abs(a\
    \ - b) < EPS;\n}\n\n}  // namespace internal_half_plane_intersection\n\nPolygon\
    \ half_plane_intersection(vector<Line> ls) {\n    using namespace internal_half_plane_intersection;\n\
    \n    static constexpr real INF = 1e9;\n    vector<HalfPlane> hs;\n    hs.reserve(ls.size()\
    \ + 4);\n    for (const Line &l : ls) hs.emplace_back(l);\n\n    Polygon box =\
    \ {\n        Point(-INF, -INF),\n        Point(INF, -INF),\n        Point(INF,\
    \ INF),\n        Point(-INF, INF),\n    };\n    for (int i = 0; i < 4; ++i) {\n\
    \        hs.emplace_back(Line(box[i], box[(i + 1) % 4]));\n    }\n\n    sort(hs.begin(),\
    \ hs.end());\n\n    deque<HalfPlane> deq;\n    for (const HalfPlane &h : hs) {\n\
    \        while (deq.size() > 1 &&\n               h.outside(intersection(deq.back(),\
    \ deq[deq.size() - 2]))) {\n            deq.pop_back();\n        }\n        while\
    \ (deq.size() > 1 &&\n               h.outside(intersection(deq[0], deq[1])))\
    \ {\n            deq.pop_front();\n        }\n        if (!deq.empty() && fabs(cross(deq.back().pq,\
    \ h.pq)) < EPS) {\n            if (dot(deq.back().pq, h.pq) < 0) return {};\n\
    \            if (h.outside(deq.back().p)) deq.pop_back();\n            else continue;\n\
    \        }\n        deq.push_back(h);\n    }\n\n    while (deq.size() > 2 &&\n\
    \           deq.front().outside(intersection(deq.back(), deq[deq.size() - 2])))\
    \ {\n        deq.pop_back();\n    }\n    while (deq.size() > 2 &&\n          \
    \ deq.back().outside(intersection(deq[0], deq[1]))) {\n        deq.pop_front();\n\
    \    }\n    if (deq.size() < 3) return {};\n\n    Polygon res;\n    res.reserve(deq.size());\n\
    \    for (int i = 0; i < (int)deq.size(); ++i) {\n        Point p = intersection(deq[i],\
    \ deq[(i + 1) % deq.size()]);\n        if (res.empty() || !same_point(res.back(),\
    \ p)) res.push_back(p);\n    }\n    if (res.size() >= 2 && same_point(res.front(),\
    \ res.back())) res.pop_back();\n    if (res.size() < 3 || fabs(area(res)) < EPS)\
    \ return {};\n    return res;\n}\n\n/**\n * @brief \u534A\u5E73\u9762\u5171\u901A\
    \u90E8\u5206(Half-Plane Intersection)\n */\n#line 21 \"test/aoj_cgl_4_c_half_plane_intersection.test.cpp\"\
    \n\nvector<Line> polygon_half_planes(const Polygon &poly) {\n    vector<Line>\
    \ ls;\n    int n = poly.size();\n    ls.reserve(n);\n    for (int i = 0; i < n;\
    \ ++i) {\n        ls.emplace_back(poly[i], poly[(i + 1) % n]);\n    }\n    return\
    \ ls;\n}\n\nvoid self_check() {\n    {\n        Polygon poly = {\n           \
    \ Point(1, 1),\n            Point(4, 1),\n            Point(4, 3),\n         \
    \   Point(1, 3),\n        };\n        auto ls = polygon_half_planes(poly);\n \
    \       ls.emplace_back(Point(2, 0), Point(2, 4));\n        Polygon got = half_plane_intersection(ls);\n\
    \        assert(fabs(fabs(area(got)) - 2.0) < 1e-9);\n    }\n    {\n        Polygon\
    \ poly = {\n            Point(1, 1),\n            Point(4, 1),\n            Point(4,\
    \ 3),\n            Point(1, 3),\n        };\n        auto ls = polygon_half_planes(poly);\n\
    \        ls.emplace_back(Point(2, 4), Point(2, 0));\n        Polygon got = half_plane_intersection(ls);\n\
    \        assert(fabs(fabs(area(got)) - 4.0) < 1e-9);\n    }\n    {\n        Polygon\
    \ poly = {\n            Point(0, 0),\n            Point(4, 0),\n            Point(4,\
    \ 2),\n            Point(2, 4),\n            Point(0, 4),\n        };\n      \
    \  auto ls = polygon_half_planes(poly);\n        ls.emplace_back(Point(5, 5),\
    \ Point(5, 3));\n        Polygon got = half_plane_intersection(ls);\n        assert(got.empty());\n\
    \    }\n}\n\nint main() {\n    self_check();\n\n    Scanner sc;\n    int n;\n\
    \    sc.read(n);\n    Polygon poly(n);\n    for (int i = 0; i < n; ++i) {\n  \
    \      ll x, y;\n        sc.read(x, y);\n        poly[i] = Point(x, y);\n    }\n\
    \n    vector<Line> base = polygon_half_planes(poly);\n    int q;\n    sc.read(q);\n\
    \    while (q--) {\n        ll x1, y1, x2, y2;\n        sc.read(x1, y1, x2, y2);\n\
    \        vector<Line> ls = base;\n        ls.emplace_back(Point(x1, y1), Point(x2,\
    \ y2));\n        Polygon ans = half_plane_intersection(ls);\n        printf(\"\
    %.8f\\n\", fabs(area(ans)));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C\"\
    \n#define ERROR \"1e-8\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cmath>\n#include <deque>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\n\nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../geometry/half_plane_intersection.cpp\"\n\nvector<Line> polygon_half_planes(const\
    \ Polygon &poly) {\n    vector<Line> ls;\n    int n = poly.size();\n    ls.reserve(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        ls.emplace_back(poly[i], poly[(i +\
    \ 1) % n]);\n    }\n    return ls;\n}\n\nvoid self_check() {\n    {\n        Polygon\
    \ poly = {\n            Point(1, 1),\n            Point(4, 1),\n            Point(4,\
    \ 3),\n            Point(1, 3),\n        };\n        auto ls = polygon_half_planes(poly);\n\
    \        ls.emplace_back(Point(2, 0), Point(2, 4));\n        Polygon got = half_plane_intersection(ls);\n\
    \        assert(fabs(fabs(area(got)) - 2.0) < 1e-9);\n    }\n    {\n        Polygon\
    \ poly = {\n            Point(1, 1),\n            Point(4, 1),\n            Point(4,\
    \ 3),\n            Point(1, 3),\n        };\n        auto ls = polygon_half_planes(poly);\n\
    \        ls.emplace_back(Point(2, 4), Point(2, 0));\n        Polygon got = half_plane_intersection(ls);\n\
    \        assert(fabs(fabs(area(got)) - 4.0) < 1e-9);\n    }\n    {\n        Polygon\
    \ poly = {\n            Point(0, 0),\n            Point(4, 0),\n            Point(4,\
    \ 2),\n            Point(2, 4),\n            Point(0, 4),\n        };\n      \
    \  auto ls = polygon_half_planes(poly);\n        ls.emplace_back(Point(5, 5),\
    \ Point(5, 3));\n        Polygon got = half_plane_intersection(ls);\n        assert(got.empty());\n\
    \    }\n}\n\nint main() {\n    self_check();\n\n    Scanner sc;\n    int n;\n\
    \    sc.read(n);\n    Polygon poly(n);\n    for (int i = 0; i < n; ++i) {\n  \
    \      ll x, y;\n        sc.read(x, y);\n        poly[i] = Point(x, y);\n    }\n\
    \n    vector<Line> base = polygon_half_planes(poly);\n    int q;\n    sc.read(q);\n\
    \    while (q--) {\n        ll x1, y1, x2, y2;\n        sc.read(x1, y1, x2, y2);\n\
    \        vector<Line> ls = base;\n        ls.emplace_back(Point(x1, y1), Point(x2,\
    \ y2));\n        Polygon ans = half_plane_intersection(ls);\n        printf(\"\
    %.8f\\n\", fabs(area(ans)));\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - geometry/half_plane_intersection.cpp
  - geometry/geometry.cpp
  isVerificationFile: true
  path: test/aoj_cgl_4_c_half_plane_intersection.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_cgl_4_c_half_plane_intersection.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_cgl_4_c_half_plane_intersection.test.cpp
- /verify/test/aoj_cgl_4_c_half_plane_intersection.test.cpp.html
title: test/aoj_cgl_4_c_half_plane_intersection.test.cpp
---
