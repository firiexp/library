#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../math/stern_brocot_tree.cpp"

using Fraction = pair<ll, ll>;

bool less_fraction(Fraction a, Fraction b) {
    return (__int128)a.first * b.second < (__int128)b.first * a.second;
}

void check_cut(ll max_num, ll max_den, Fraction threshold, Fraction left, Fraction right) {
    int calls = 0;
    auto bounds = SternBrocotTree::binary_search(max_num, max_den, [&](ll p, ll q) {
        ++calls;
        assert(0 < p && p <= max_num && 0 < q && q <= max_den);
        return !less_fraction(threshold, {p, q});
    });
    assert(bounds == make_pair(left, right));
    if (!max_num || !max_den) assert(calls == 0);
    ll limit = max(max_num, max_den);
    int bits = 0;
    while (limit > 0) { ++bits; limit /= 2; }
    assert(calls <= 6 * bits);
}

int main() {
    for (ll a = 0; a <= 12; ++a) for (ll b = 0; b <= 12; ++b) {
        vector<Fraction> fractions{{0, 1}, {1, 0}};
        for (ll p = 1; p <= a; ++p) for (ll q = 1; q <= b; ++q) {
            if (gcd(p, q) == 1) fractions.emplace_back(p, q);
        }
        sort(fractions.begin(), fractions.end(), less_fraction);
        for (size_t i = 0; i + 1 < fractions.size(); ++i) {
            check_cut(a, b, fractions[i], fractions[i], fractions[i + 1]);
        }
    }
    const ll n = LLONG_MAX;
    check_cut(n, n, {0, 1}, {0, 1}, {1, n});
    check_cut(n, n, {1, 0}, {n, 1}, {1, 0});
    check_cut(n, n, {1, 1}, {1, 1}, {n, n - 1});
    ll k = (1LL << 62) + 17;
    check_cut(n, 1, {k, 1}, {k, 1}, {k + 1, 1});
    check_cut(1, n, {1, k}, {1, k}, {1, k - 1});
    ll a = 1, b = 1;
    while (a <= n - b) {
        ll next = a + b;
        a = b;
        b = next;
    }
    check_cut(b, b, {b, a}, {b, a}, {a, b - a});

    using namespace SternBrocotTree;
    auto root = ancestor_path({}, 0);
    assert(root && root->empty());
    assert(!ancestor_path({}, 1));
    auto path = encode_path(7, 3);
    vector<Fraction> expected{{1, 1}, {2, 1}, {3, 1}, {5, 2}, {7, 3}};
    for (ll d = 0; d <= depth(path); ++d) {
        auto prefix = ancestor_path(path, d);
        assert(prefix && depth(*prefix) == d);
        auto node = decode_path(*prefix);
        assert(make_pair(node.num(), node.den()) == expected[d]);
        auto direct = ancestor(7, 3, d);
        assert(direct && make_pair(direct->num(), direct->den()) == expected[d]);
    }
    for (ll d : {-1LL, depth(path) + 1, LLONG_MAX}) {
        assert(!ancestor_path(path, d));
        assert(!ancestor(7, 3, d));
    }
}
