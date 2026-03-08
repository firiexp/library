#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <bits/stdc++.h>

using namespace std;

#include "../util/fastio.cpp"
#include "../tree/diameter.cpp"

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 1; n <= 40; ++n) {
            for (int trial = 0; trial < 200; ++trial) {
                vector<vector<int>> g(n);
                for (int v = 1; v < n; ++v) {
                    int p = uniform_int_distribution<int>(0, v - 1)(rng);
                    g[v].push_back(p);
                    g[p].push_back(v);
                }

                int brute = 0;
                for (int s = 0; s < n; ++s) {
                    vector<int> dist(n, -1);
                    queue<int> q;
                    dist[s] = 0;
                    q.push(s);
                    while (!q.empty()) {
                        int v = q.front();
                        q.pop();
                        for (auto &&to : g[v]) {
                            if (dist[to] != -1) continue;
                            dist[to] = dist[v] + 1;
                            q.push(to);
                        }
                    }
                    for (auto &&d : dist) brute = max(brute, d);
                }

                auto [diam, ends] = tree_diameter(g);
                if (diam != brute) return 1;
                int s = ends.first;
                int t = ends.second;
                vector<int> dist(n, -1);
                queue<int> q;
                dist[s] = 0;
                q.push(s);
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    for (auto &&to : g[v]) {
                        if (dist[to] != -1) continue;
                        dist[to] = dist[v] + 1;
                        q.push(to);
                    }
                }
                if (dist[t] != diam) return 1;
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
