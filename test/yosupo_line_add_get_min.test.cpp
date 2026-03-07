#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <vector>

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include "../datastructure/li_chao_tree.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &init[i].first, &init[i].second);
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
        scanf("%d", &t);
        if (!t) {
            ll a, b;
            scanf("%lld %lld", &a, &b);
            qs.push_back({0, a, b, 0});
        } else {
            ll p;
            scanf("%lld", &p);
            qs.push_back({1, 0, 0, p});
            xs.push_back(p);
        }
    }

    LiChaoTree<ll> li(xs);
    for (auto [a, b] : init) li.add_line(a, b);

    for (auto qu : qs) {
        if (qu.t == 0) li.add_line(qu.a, qu.b);
        else printf("%lld\n", li.query(qu.p));
    }
    return 0;
}
