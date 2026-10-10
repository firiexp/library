#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/enumerate_triangles.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    vector<long long> values(n);
    for (auto &x : values) in.read(x);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) in.read(u, v);
    long long answer = 0;
    const int mod = 998244353;
    enumerate_triangles(n, edges, [&](int a, int b, int c) {
        answer = (answer + values[a] * values[b] % mod * values[c]) % mod;
    });
    out.println(answer);
}
