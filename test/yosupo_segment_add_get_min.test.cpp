#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <algorithm>
#include <deque>
#include <limits>
#include <vector>

using ll = long long;
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/li_chao_tree.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, q;
    in.read(n, q);
    struct Segment {
        ll l, r, a, b;
    };
    vector<Segment> init(n);
    for (int i = 0; i < n; ++i) {
        in.read(init[i].l, init[i].r, init[i].a, init[i].b);
    }

    struct Query {
        int t;
        ll l, r, a, b, p;
    };
    vector<Query> qs;
    qs.reserve(q);
    vector<ll> xs;
    xs.reserve(q);

    for (int i = 0; i < q; ++i) {
        int t;
        in.read(t);
        if (!t) {
            ll l, r, a, b;
            in.read(l, r, a, b);
            qs.push_back({0, l, r, a, b, 0});
        } else {
            ll p;
            in.read(p);
            qs.push_back({1, 0, 0, 0, 0, p});
            xs.push_back(p);
        }
    }

    LiChaoTree<ll> li(xs);
    for (auto s : init) li.add_segment(s.a, s.b, s.l, s.r);

    const ll INF = numeric_limits<ll>::max() / 4;
    for (auto qu : qs) {
        if (qu.t == 0) {
            li.add_segment(qu.a, qu.b, qu.l, qu.r);
        } else {
            ll ans = li.query(qu.p);
            if (ans == INF) out.writeln("INFINITY");
            else out.writeln(ans);
        }
    }
    return 0;
}
