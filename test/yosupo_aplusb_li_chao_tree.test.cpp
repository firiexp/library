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
        assert(!offline.query_with_id(0) && !online.query_with_id(0));
        assert(offline.add_segment(0, value, 0, 1) == 0);
        assert(online.add_segment(0, value, 0, 1) == 0);
        assert(offline.query(0) == value && online.query(0) == value);
        assert(offline.query_with_id(0) == make_pair(value, 0));
        assert(online.query_with_id(0) == make_pair(value, 0));
        for (ll x : {-2LL, 2LL}) {
            assert(offline.query(x) == empty && online.query(x) == empty);
            assert(!offline.query_with_id(x) && !online.query_with_id(x));
        }
        assert(offline.add_line(0, value) == 1);
        assert(online.add_line(0, value) == 1);
        for (ll x : {-2LL, 0LL, 2LL}) {
            assert(offline.query(x) == value && online.query(x) == value);
            auto expected = make_pair(value, x == 0 ? 0 : 1);
            assert(offline.query_with_id(x) == expected && online.query_with_id(x) == expected);
        }
    }
    LiChaoTree<ll, get_max> empty_tree({});
    assert(empty_tree.add_line(0, 1) == 0);
    assert(empty_tree.add_segment(1, 0, -2, 2) == 1);
    assert(empty_tree.query(0) == empty);
    assert(!empty_tree.query_with_id(0));
    LiChaoTree<ll, get_max> single({0, 0});
    OnlineLiChaoTree<ll, get_max> single_online(0, 1);
    assert(single.add_segment(0, 0, 0, 0) == 0);
    assert(single_online.add_segment(0, 0, 0, 0) == 0);
    assert(single.query(0) == empty && single_online.query(0) == empty);
    assert(single.add_line(0, 7) == 1);
    assert(single_online.add_line(0, 7) == 1);
    assert(single.query(0) == 7 && single_online.query(0) == 7);
    assert(single.query_with_id(0) == make_pair(7LL, 1));
    assert(single_online.query_with_id(0) == make_pair(7LL, 1));
    assert(single.query(1) == empty);
    assert(!single.query_with_id(1));
    if constexpr (!get_max) {
        single.add_line(0, LLONG_MIN);
        single_online.add_line(0, LLONG_MIN);
        assert(single.query_with_id(0) == make_pair(LLONG_MIN, 2));
        assert(single_online.query_with_id(0) == make_pair(LLONG_MIN, 2));
    }
}

template<bool get_max>
void check_ties() {
    const vector<array<ll, 4>> lines = {
        {0, 0, -4, 5}, {1, 0, -4, 5}, {-1, 0, -4, 5},
        {0, 0, -4, 5}, {0, 0, 0, 1}, {1, -1, 1, 5}
    };
    vector<int> order = {0, 1, 2, 3, 4, 5};
    do {
        LiChaoTree<ll, get_max> offline({-4, -3, -2, -1, 0, 1, 2, 3, 4});
        OnlineLiChaoTree<ll, get_max> online(-4, 5);
        for (int id = 0; id < 6; ++id) {
            auto [a, b, l, r] = lines[order[id]];
            if (order[id] < 4) {
                assert(offline.add_line(a, b) == id);
                assert(online.add_line(a, b) == id);
            } else {
                assert(offline.add_segment(a, b, l, r) == id);
                assert(online.add_segment(a, b, l, r) == id);
            }
            for (ll x = -4; x <= 4; ++x) {
                optional<pair<ll, int>> expected;
                for (int j = 0; j <= id; ++j) {
                    auto [a, b, l, r] = lines[order[j]];
                    if (x < l || r <= x) continue;
                    ll value = a * x + b;
                    if (!expected || (get_max ? value > expected->first : value < expected->first)) {
                        expected = make_pair(value, j);
                    }
                }
                assert(offline.query_with_id(x) == expected && online.query_with_id(x) == expected);
            }
        }
    } while (next_permutation(order.begin(), order.end()));
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
                assert(offline.add_line(a, b) == op);
                assert(online.add_line(a, b) == op);
            } else {
                assert(offline.add_segment(a, b, l, r) == op);
                assert(online.add_segment(a, b, l, r) == op);
            }
            lines.push_back({a, b, l, r});
            for (ll x = -16; x <= 16; ++x) {
                optional<pair<ll, int>> expected;
                for (int id = 0; id <= op; ++id) {
                    const auto &line = lines[id];
                    if (x < line.l || line.r <= x) continue;
                    ll y = line.a * x + line.b;
                    if (!expected || (get_max ? y > expected->first : y < expected->first)) {
                        expected = make_pair(y, id);
                    }
                }
                ll value = expected ? expected->first : (get_max ? -inf : inf);
                assert(online.query(x) == value);
                assert(online.query_with_id(x) == expected);
                if (find(xs.begin(), xs.end(), x) == xs.end()) {
                    value = get_max ? -inf : inf;
                    expected = nullopt;
                }
                assert(offline.query(x) == value);
                assert(offline.query_with_id(x) == expected);
            }
        }
    }
}

int main() {
    check_limits<false>();
    check_limits<true>();
    check_ties<false>();
    check_ties<true>();
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
