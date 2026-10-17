#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../fps/linear_recurrence.cpp"

void self_check() {
    mt19937 random(214);
    for (int size : {1, 2, 3, 16, 63, 128}) {
        vector<mint> a(size);
        for (int n = 0; n < size; ++n) assert(linear_recurrence(a, n) == mint(0));
        for (auto &x : a) x = random() % ntt_mod;
        const auto original = a;
        for (int n = 0; n < size; ++n) assert(linear_recurrence(a, n) == a[n]);
        auto c = berlekamp_massey(a);
        for (ll n : {(ll)size, (ll)size + 1, LLONG_MAX}) {
            assert(linear_recurrence(a, n) == linear_recurrence(a, c, n));
        }
        assert(a == original);
    }
    for (ll n : {0LL, 1LL, LLONG_MAX}) {
        assert(linear_recurrence(vector<mint>{}, n) == mint(0));
        assert(linear_recurrence(vector<mint>(8), n) == mint(0));
    }
    for (int k : {1, 2, 7, 16}) {
        vector<mint> c(k), sequence(128);
        for (auto &x : c) x = random() % ntt_mod;
        for (int i = 0; i < k; ++i) sequence[i] = random() % ntt_mod;
        for (int i = k; i < (int)sequence.size(); ++i) {
            for (int j = 0; j < k; ++j) sequence[i] += c[j] * sequence[i - j - 1];
        }
        vector<mint> initial(sequence.begin(), sequence.begin() + 2 * k);
        for (int n = 0; n < (int)sequence.size(); ++n) {
            assert(linear_recurrence(initial, n) == sequence[n]);
        }
    }
    vector<mint> geometric(32);
    geometric[0] = 7;
    for (int i = 1; i < (int)geometric.size(); ++i) geometric[i] = 3 * geometric[i - 1];
    assert(linear_recurrence(geometric, LLONG_MAX) == 7 * mint(3).pow(LLONG_MAX));
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
