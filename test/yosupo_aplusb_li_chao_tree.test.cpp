#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../datastructure/li_chao_tree.cpp"

template<bool get_max>
void check_limits() {
    const ll inf = numeric_limits<ll>::max() / 4;
    const ll empty = get_max ? -inf : inf;
    for (ll value : {0LL, inf, -inf, inf + 1, -inf - 1,
                     3000000000000000000LL, -3000000000000000000LL,
                     LLONG_MAX, -LLONG_MAX}) {
        LiChaoTree<ll, get_max> offline({-2, 0, 2});
        OnlineLiChaoTree<ll, get_max> online(-2, 3);
        assert(offline.query(0) == empty && online.query(0) == empty);
        offline.add_segment(0, value, 0, 1);
        online.add_segment(0, value, 0, 1);
        assert(offline.query(0) == value && online.query(0) == value);
        for (ll x : {-2LL, 2LL})
            assert(offline.query(x) == empty && online.query(x) == empty);
        offline.add_line(0, value);
        online.add_line(0, value);
        for (ll x : {-2LL, 0LL, 2LL})
            assert(offline.query(x) == value && online.query(x) == value);
    }
    LiChaoTree<ll, get_max> empty_tree({});
    empty_tree.add_line(0, 1);
    empty_tree.add_segment(1, 0, -2, 2);
    assert(empty_tree.query(0) == empty);
    LiChaoTree<ll, get_max> single({0, 0});
    OnlineLiChaoTree<ll, get_max> single_online(0, 1);
    single.add_segment(0, 0, 0, 0);
    single_online.add_segment(0, 0, 0, 0);
    assert(single.query(0) == empty && single_online.query(0) == empty);
    single.add_line(0, 7);
    single_online.add_line(0, 7);
    assert(single.query(0) == 7 && single_online.query(0) == 7);
    assert(single.query(1) == empty);
}

template<bool get_max>
void check_pruning() {
    const ll sign = get_max ? -1 : 1;
    OnlineLiChaoTree<ll, get_max> dominated(-1000000000LL, 1000000001LL);
    dominated.add_line(0, 0);
    for (int i = 0; i < 1000; ++i) {
        dominated.add_line(0, 0);
        dominated.add_line(sign * (i % 7), sign * (10000000000LL + i));
        dominated.add_segment(0, sign, -1000000000LL, 1000000001LL);
    }
    assert(dominated.nodes.size() == 1);
    dominated.add_line(0, -sign);
    assert(dominated.nodes.size() == 1);
    for (ll x : {-1000000000LL, 0LL, 1000000000LL}) assert(dominated.query(x) == -sign);
    OnlineLiChaoTree<ll, get_max> crossing(0, 1001);
    for (ll i = 0; i <= 1000; ++i) crossing.add_line(sign * (-2 * i), sign * i * i);
    for (ll x = 0; x <= 1000; ++x) assert(crossing.query(x) == -sign * x * x);
    OnlineLiChaoTree<ll, get_max> endpoint(0, 9);
    endpoint.add_line(0, 0);
    endpoint.add_line(-sign, 7 * sign);
    assert(endpoint.query(0) == 0 && endpoint.query(8) == -sign);
}

template<bool get_max>
void check_random() {
    struct Line {
        ll a, b, l, r;
    };
    const ll inf = numeric_limits<ll>::max() / 4;
    mt19937 rng(100 + get_max);
    for (int tc = 0; tc < 200; ++tc) {
        vector<ll> xs;
        for (ll x = -16; x <= 16; ++x)
            if (rng() % 3 != 0) xs.push_back(x);
        shuffle(xs.begin(), xs.end(), rng);
        if (!xs.empty()) xs.push_back(xs[0]);
        LiChaoTree<ll, get_max> offline(xs);
        OnlineLiChaoTree<ll, get_max> online(-16, 17);
        vector<Line> lines;
        for (int op = 0; op < 100; ++op) {
            ll a = int(rng() % 17) - 8;
            ll b = int(rng() % 101) - 50;
            if (op % 3 == 0) b += 3000000000000000000LL;
            if (op % 3 == 1) b -= 3000000000000000000LL;
            ll l = int(rng() % 41) - 20, r = int(rng() % 41) - 20;
            if (rng() % 3 == 0) {
                l = -16;
                r = 17;
                offline.add_line(a, b);
                online.add_line(a, b);
            } else {
                offline.add_segment(a, b, l, r);
                online.add_segment(a, b, l, r);
            }
            lines.push_back({a, b, l, r});
            for (ll x = -16; x <= 16; ++x) {
                optional<ll> expected;
                for (const auto &line : lines) {
                    if (x < line.l || line.r <= x) continue;
                    ll y = line.a * x + line.b;
                    if (!expected || (get_max ? y > *expected : y < *expected)) expected = y;
                }
                ll value = expected.value_or(get_max ? -inf : inf);
                assert(online.query(x) == value);
                if (find(xs.begin(), xs.end(), x) == xs.end()) value = get_max ? -inf : inf;
                assert(offline.query(x) == value);
            }
        }
    }
}

int main() {
    check_limits<false>();
    check_limits<true>();
    check_pruning<false>();
    check_pruning<true>();
    check_random<false>();
    check_random<true>();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
