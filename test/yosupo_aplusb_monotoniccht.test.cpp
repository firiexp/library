#define STANDALONE

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
        CHT<ll, get_max, true> cht;
        CHT<ll, get_max> values_only;
        vector<pair<ll, ll>> added;
        auto brute = [&](ll x) {
            ll best = get_max ? LLONG_MIN : LLONG_MAX;
            for (auto [a, b] : added) {
                best = get_max ? max(best, a * x + b) : min(best, a * x + b);
            }
            return best;
        };
        for (auto [a, b] : lines) {
            cht.add_line(a, b, added.size());
            values_only.add_line(a, b);
            added.emplace_back(a, b);
            ll x = (int)(rng() % 201) - 100;
            assert(cht.query(x) == brute(x));
            assert(values_only.query(x) == brute(x));
            auto [value, id] = cht.query_with_id(x);
            assert(0 <= id && id < int(added.size()));
            assert(value == brute(x) && added[id].first * x + added[id].second == value);
        }
        auto inc = cht, dec = cht;
        auto inc_values = values_only, dec_values = values_only;
        auto check_id = [&](pair<ll, int> result, ll x) {
            auto [value, id] = result;
            assert(0 <= id && id < int(added.size()));
            assert(value == brute(x) && added[id].first * x + added[id].second == value);
        };
        for (ll x = -100; x <= 100; ++x) {
            assert(cht.query(x) == brute(x));
            assert(inc.query_increase(x) == brute(x));
            assert(dec.query_decrease(-x) == brute(-x));
            assert(inc_values.query_increase(x) == brute(x));
            assert(dec_values.query_decrease(-x) == brute(-x));
            check_id(cht.query_with_id(x), x);
            check_id(inc.query_increase_with_id(x), x);
            check_id(dec.query_decrease_with_id(-x), -x);
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

template<bool get_max>
void check_ties_and_interleaved() {
    for (bool reverse_order : {false, true}) {
        vector<pair<ll, ll>> lines{{-2, 0}, {-2, -1}, {-2, 1}, {-1, 0}, {0, 0}, {0, 0}, {1, 0}, {2, 0}};
        if (reverse_order) reverse(lines.begin(), lines.end());
        for (int direction : {-1, 0, 1}) {
            CHT<ll, get_max, true> cht;
            for (int i = 0; i < int(lines.size()); ++i) {
                auto [a, b] = lines[i];
                cht.add_line(a, b, 7 * i + 11);
                ll x = direction * (i - 4);
                auto [value, id] = direction == 0 ? cht.query_with_id(x) : direction == 1 ? cht.query_increase_with_id(x) : cht.query_decrease_with_id(x);
                assert(id % 7 == 4);
                id = (id - 11) / 7;
                assert(0 <= id && id <= i);
                assert(lines[id].first * x + lines[id].second == value);
                for (int j = 0; j <= i; ++j) {
                    ll candidate = lines[j].first * x + lines[j].second;
                    assert(get_max ? candidate <= value : candidate >= value);
                }
            }
        }
    }
}

int main() {
    check_products();
    check_queries<false>();
    check_queries<true>();
    check_boundaries<false>();
    check_boundaries<true>();
    check_ties_and_interleaved<false>();
    check_ties_and_interleaved<true>();
    CHT<double, false, true> floating;
    floating.add_line(0.5, 1.25, 42);
    floating.add_line(1.5, 0.25, -100);
    auto [value, id] = floating.query_with_id(2.0);
    assert(value == 2.25 && id == 42);
    CHT<ll, true, true> default_id;
    default_id.add_line(1, 0);
    assert((default_id.query_with_id(2) == pair<ll, int>{2, -1}));
}
