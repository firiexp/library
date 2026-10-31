#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../math/linear_algebra/solve_linear_system_mod2.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<DynamicBitset> a(n, DynamicBitset(m));
    string s;
    for (auto& row : a) {
        sc.read(s);
        for (int j = 0; j < m; ++j) row.assign(j, s[j] == '1');
    }
    sc.read(s);
    DynamicBitset b(n);
    for (int i = 0; i < n; ++i) b.assign(i, s[i] == '1');
    auto solution = solve_linear_system_mod2(std::move(a), std::move(b), m);
    if (!solution) {
        pr.println(-1);
        return 0;
    }
    pr.println((int)solution->basis.size());
    auto output = [&](const DynamicBitset& x) {
        for (int j = 0; j < m; ++j) pr.print(x.test(j) ? '1' : '0');
        pr.println();
    };
    output(solution->particular);
    for (const auto& v : solution->basis) output(v);
}
