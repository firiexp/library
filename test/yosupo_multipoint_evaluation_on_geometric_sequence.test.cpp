#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../fps/multipoint_evaluation_geometric.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m, a, r;
    in.read(n, m, a, r);
    poly f(n);
    for (auto& c : f.v) {
        int x;
        in.read(x);
        c = x;
    }
    auto result = multipoint_evaluation_geometric(f, mint(a), mint(r), m);
    for (int i = 0; i < m; ++i) {
        if (i) out.print(' ');
        out.print(result[i].val);
    }
    out.println();
}
