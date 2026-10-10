#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/enumerate_triangles.cpp"

void check(int n, vector<pair<int, int>> edges, mt19937 &rng) {
    vector<vector<bool>> adjacent(n, vector<bool>(n));
    for (auto [u, v] : edges) adjacent[u][v] = adjacent[v][u] = true;
    vector<long long> values(n);
    for (auto &x : values) x = rng() % 998244353;
    vector<array<int, 3>> expected;
    long long sum = 0;
    for (int a = 0; a < n; ++a)
        for (int b = a + 1; b < n; ++b)
            for (int c = b + 1; c < n; ++c)
                if (adjacent[a][b] && adjacent[b][c] && adjacent[c][a]) {
                    expected.push_back({a, b, c});
                    sum = (sum + values[a] * values[b] % 998244353 * values[c]) % 998244353;
                }
    shuffle(edges.begin(), edges.end(), rng);
    for (auto &[u, v] : edges) if (rng() & 1) swap(u, v);
    auto input = edges;
    vector<array<int, 3>> actual;
    long long actual_sum = 0;
    auto callback = [&](int a, int b, int c) {
        assert(0 <= a && a < b && b < c && c < n);
        actual.push_back({a, b, c});
        actual_sum = (actual_sum + values[a] * values[b] % 998244353 * values[c]) % 998244353;
    };
    enumerate_triangles(n, edges, callback);
    sort(actual.begin(), actual.end());
    assert(actual == expected && actual_sum == sum && edges == input);
}

void self_check() {
    mt19937 rng(121);
    for (int n = 0; n <= 6; ++n) {
        vector<pair<int, int>> all;
        for (int u = 0; u < n; ++u)
            for (int v = u + 1; v < n; ++v) all.emplace_back(u, v);
        for (int mask = 0; mask < (1 << all.size()); ++mask) {
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)all.size(); ++i)
                if (mask >> i & 1) edges.push_back(all[i]);
            check(n, edges, rng);
        }
    }
    for (int trial = 0; trial < 1000; ++trial) {
        int n = rng() % 81, threshold = rng() % 101;
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u)
            for (int v = u + 1; v < n; ++v)
                if (int(rng() % 100) < threshold) edges.emplace_back(u, v);
        check(n, edges, rng);
    }
    vector<pair<int, int>> star, complete;
    for (int v = 1; v < 100000; ++v) star.emplace_back(0, v);
    long long count = 0;
    enumerate_triangles(100000, star, [&](int, int, int) { ++count; });
    assert(count == 0);
    int n = 447;
    for (int u = 0; u < n; ++u)
        for (int v = u + 1; v < n; ++v) complete.emplace_back(u, v);
    enumerate_triangles(n, complete, [&](int a, int b, int c) {
        assert(a < b && b < c);
        ++count;
    });
    assert(count == 1LL * n * (n - 1) * (n - 2) / 6);
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
