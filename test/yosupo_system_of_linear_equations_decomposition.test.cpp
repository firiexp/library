#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/linear_algebra/linear_system_decomposition.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int h, w;
    sc.read(h, w);
    vector<vector<mint>> a(h, vector<mint>(w));
    vector<mint> b(h);
    for (auto &row : a) for (auto &value : row) {
        int x;
        sc.read(x);
        value = x;
    }
    for (auto &value : b) {
        int x;
        sc.read(x);
        value = x;
    }
    LinearSystemDecomposition system(move(a), w);
    auto x = system.solve(move(b));
    if (!x) {
        pr.println(-1);
        return 0;
    }
    pr.println((int)system.basis().size());
    for (int i = 0; i < w; ++i) {
        pr.print((*x)[i].val);
        pr.print(i + 1 == w ? '\n' : ' ');
    }
    for (const auto &v : system.basis()) for (int i = 0; i < w; ++i) {
        pr.print(v[i].val);
        pr.print(i + 1 == w ? '\n' : ' ');
    }
}
