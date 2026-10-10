#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../util/biginteger.cpp"
#include "../datastructure/monotoniccht.cpp"

void check_products() {
    CHT<ll, false> cht;
    auto check = [&](const array<ll, 6> &v) {
        BigInteger lhs = (BigInteger(v[3]) - v[1]) * (BigInteger(v[2]) - v[4]);
        BigInteger rhs = (BigInteger(v[5]) - v[3]) * (BigInteger(v[0]) - v[2]);
        assert(cht.check({v[0], v[1]}, {v[2], v[3]}, {v[4], v[5]}) == (lhs >= rhs));
    };
    constexpr ll limit = 1LL << 62;
    vector<ll> values{-limit, -limit + 1, -1, 0, 1, limit - 1, limit};
    for (int mask = 0; mask < 117649; ++mask) {
        array<ll, 6> v;
        int cur = mask;
        for (ll &x : v) {
            x = values[cur % 7];
            cur /= 7;
        }
        check(v);
    }
    mt19937_64 rng(130);
    uniform_int_distribution<ll> coefficient(-limit, limit);
    for (int rep = 0; rep < 200000; ++rep) {
        array<ll, 6> v;
        for (ll &x : v) x = coefficient(rng);
        check(v);
    }
}

template<bool get_max>
void check_queries() {
    mt19937 rng(130);
    for (int rep = 0; rep < 500; ++rep) {
        vector<pair<ll, ll>> lines;
        for (int i = 0; i < 80; ++i) {
            lines.emplace_back((int)(rng() % 41) - 20, (int)(rng() % 401) - 200);
        }
        sort(lines.begin(), lines.end());
        if (rep & 1) reverse(lines.begin(), lines.end());
        CHT<ll, get_max> cht;
        vector<pair<ll, ll>> added;
        auto brute = [&](ll x) {
            ll best = get_max ? LLONG_MIN : LLONG_MAX;
            for (auto [a, b] : added) {
                best = get_max ? max(best, a * x + b) : min(best, a * x + b);
            }
            return best;
        };
        for (auto [a, b] : lines) {
            cht.add_line(a, b);
            added.emplace_back(a, b);
            ll x = (int)(rng() % 201) - 100;
            assert(cht.query(x) == brute(x));
        }
        auto inc = cht, dec = cht;
        for (ll x = -100; x <= 100; ++x) {
            assert(cht.query(x) == brute(x));
            assert(inc.query_increase(x) == brute(x));
            assert(dec.query_decrease(-x) == brute(-x));
        }
    }
}

template<bool get_max>
void check_boundaries() {
    constexpr ll limit = 1LL << 62;
    for (bool reverse_order : {false, true}) {
        vector<pair<ll, ll>> lines{{limit, limit}, {limit - 1, -limit}, {-limit, limit}};
        if (reverse_order) reverse(lines.begin(), lines.end());
        CHT<ll, get_max> cht;
        for (auto [a, b] : lines) cht.add_line(a, b);
        auto inc = cht, dec = cht;
        ll expected = get_max ? limit : -limit;
        assert(cht.query(0) == expected);
        assert(inc.query_increase(0) == expected);
        assert(dec.query_decrease(0) == expected);
    }
}

int main() {
    check_products();
    check_queries<false>();
    check_queries<true>();
    check_boundaries<false>();
    check_boundaries<true>();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
