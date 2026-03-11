#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <algorithm>
#include <deque>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/li_chao_tree.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, q;
    in.read(n, q);
    vector<pair<ll, ll>> init(n);
    for (int i = 0; i < n; ++i) {
        in.read(init[i].first, init[i].second);
    }

    struct Query {
        int t;
        ll a, b, p;
    };
    vector<Query> qs;
    qs.reserve(q);
    vector<ll> xs;
    xs.reserve(q);

    for (int i = 0; i < q; ++i) {
        int t;
        in.read(t);
        if (!t) {
            ll a, b;
            in.read(a, b);
            qs.push_back({0, a, b, 0});
        } else {
            ll p;
            in.read(p);
            qs.push_back({1, 0, 0, p});
            xs.push_back(p);
        }
    }

    LiChaoTree<ll> li(xs);
    for (auto [a, b] : init) li.add_line(a, b);

    for (auto qu : qs) {
        if (qu.t == 0) li.add_line(qu.a, qu.b);
        else out.writeln(li.query(qu.p));
    }
    return 0;
}
