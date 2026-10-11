#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../fps/multipoint_evaluation_geometric.cpp"

void check(const poly& f, mint a, mint r, int m) {
    auto original = f.v;
    auto result = multipoint_evaluation_geometric(f, a, r, m);
    assert((int)result.size() == m && f.v == original);
    for (int j = 0; j < m; ++j) {
        mint expected = 0, power = 1;
        for (auto c : f.v) {
            expected += c * power;
            power *= a;
        }
        assert(result[j] == expected);
        a *= r;
    }
}

void self_check() {
    mt19937 rng(161);
    vector<int> sizes = {0, 1, 2, 31, 32, 33, 63, 64, 65, 127, 128, 129};
    vector<mint> ratios = {0, 1, -1, mint(3).pow((ntt_mod - 1) / 4), 3};
    for (int n : sizes) for (int m : sizes) {
        poly f(n);
        for (auto& c : f.v) c = rng() % ntt_mod;
        for (auto r : ratios) {
            check(f, mint(0), r, m);
            check(f, mint(7), r, m);
        }
        fill(f.v.begin(), f.v.end(), mint(0));
        check(f, mint(3), mint(5), m);
    }
    for (int tc = 0; tc < 1000; ++tc) {
        int n = rng() % 160, m = rng() % 160;
        poly f(n);
        for (auto& c : f.v) c = rng() % ntt_mod;
        check(f, mint(rng() % ntt_mod), mint(rng() % ntt_mod), m);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
