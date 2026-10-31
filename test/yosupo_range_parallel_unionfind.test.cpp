#define PROBLEM "https://judge.yosupo.jp/problem/range_parallel_unionfind"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../datastructure/unionfind/range_parallel_unionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<mint> sum(n);
    for (auto& x : sum) {
        int value;
        sc.read(value);
        x = value;
    }
    RangeParallelUnionFind uf(n);
    mint answer = 0;
    while (q--) {
        int k, a, b;
        sc.read(k, a, b);
        uf.unite_range(a, b, k, [&](int keep, int absorbed) {
            answer += sum[keep] * sum[absorbed];
            sum[keep] += sum[absorbed];
        });
        pr.println(answer.val);
    }
}
