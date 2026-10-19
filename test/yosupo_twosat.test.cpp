#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/twosat.cpp"

int main() {
    Scanner in;
    Printer out;
    string p, cnf;
    int n, m;
    in >> p >> cnf >> n >> m;
    TwoSAT sat(n);
    for (int i = 0; i < m; ++i) {
        int a, b, zero;
        in >> a >> b >> zero;
        sat.add_clause(abs(a) - 1, a > 0, abs(b) - 1, b > 0);
    }
    auto answer = sat.build();
    if (answer.empty()) {
        out << "s UNSATISFIABLE\n";
    } else {
        out << "s SATISFIABLE\nv ";
        for (int i = 0; i < n; ++i) out << (answer[i] ? i + 1 : -(i + 1)) << ' ';
        out << "0\n";
    }
}
