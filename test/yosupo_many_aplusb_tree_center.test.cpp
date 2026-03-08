#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <queue>
#include <random>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/tree_center.cpp"

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 0; n <= 40; ++n) {
            for (int trial = 0; trial < 200; ++trial) {
                vector<vector<int>> g(n);
                for (int v = 1; v < n; ++v) {
                    int p = uniform_int_distribution<int>(0, v - 1)(rng);
                    g[v].push_back(p);
                    g[p].push_back(v);
                }

                int brute_radius = 0;
                vector<int> brute_centers;
                if (n > 0) {
                    vector<int> ecc(n);
                    for (int s = 0; s < n; ++s) {
                        vector<int> dist(n, -1);
                        queue<int> q;
                        dist[s] = 0;
                        q.push(s);
                        while (!q.empty()) {
                            int v = q.front();
                            q.pop();
                            for (int to : g[v]) {
                                if (dist[to] != -1) continue;
                                dist[to] = dist[v] + 1;
                                q.push(to);
                            }
                        }
                        for (int d : dist) ecc[s] = max(ecc[s], d);
                    }
                    brute_radius = *min_element(ecc.begin(), ecc.end());
                    for (int v = 0; v < n; ++v) {
                        if (ecc[v] == brute_radius) brute_centers.push_back(v);
                    }
                }

                auto [radius, centers] = tree_center(g);
                sort(centers.begin(), centers.end());
                if (radius != brute_radius) return 1;
                if (centers != brute_centers) return 1;
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
