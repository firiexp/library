#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../tree/dynamic_tree/link_cut_tree.cpp"

struct Sum {
    using T = long long;
    static T e() { return 0; }
    static T f(T a, T b) { return a + b; }
};

struct Concat {
    using T = string;
    static T e() { return ""; }
    static T f(const T &a, const T &b) { return a + b; }
};

vector<int> path(const vector<vector<bool>> &g, int u, int v) {
    int n = g.size();
    vector<int> par(n, -1), queue{u};
    par[u] = u;
    for (int i = 0; i < int(queue.size()); ++i) {
        int x = queue[i];
        for (int y = 0; y < n; ++y) if (g[x][y] && par[y] == -1) {
            par[y] = x;
            queue.push_back(y);
        }
    }
    if (par[v] == -1) return {};
    vector<int> result{v};
    while (result.back() != u) result.push_back(par[result.back()]);
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    mt19937 rng(340);
    for (int rep = 0; rep < 40; ++rep) {
        int n = 1 + rng() % 20;
        LinkCutTree<Sum> sums(n);
        LinkCutTree<Concat> words(n);
        vector<vector<bool>> g(n, vector<bool>(n));
        vector<long long> values(n);
        vector<string> letters(n, "a");
        for (int v = 0; v < n; ++v) words.set(v, letters[v]);
        for (int step = 0; step < 1500; ++step) {
            int u = rng() % n, v = rng() % n, type = rng() % 5;
            auto p = path(g, u, v);
            if (type == 0) {
                bool expected = p.empty();
                assert(sums.link(u, v) == expected);
                assert(words.link(u, v) == expected);
                if (expected) g[u][v] = g[v][u] = true;
            } else if (type == 1) {
                bool expected = g[u][v];
                assert(sums.cut(u, v) == expected);
                assert(words.cut(u, v) == expected);
                g[u][v] = g[v][u] = false;
            } else if (type == 2) {
                values[u] = rng() % 10;
                letters[u] = string(1, 'a' + rng() % 4);
                sums.set(u, values[u]);
                words.set(u, letters[u]);
            } else if (type == 3) {
                sums.evert(u);
                words.evert(u);
            }
            p = path(g, u, v);
            if (p.empty()) continue;
            long long total = 0;
            string target;
            for (int x : p) { total += values[x]; target += letters[x]; }
            for (long long limit : {0LL, max(0LL, total - 1), total, (long long)(rng() % 30)}) {
                long long prefix = 0;
                int expected = -1;
                for (int x : p) {
                    prefix += values[x];
                    if (prefix > limit) { expected = x; break; }
                }
                assert(sums.find_first_false(u, v, [&](long long sum) { return sum <= limit; }) == expected);
                assert(sums.get_root(v) == u);
                assert(sums.fold(u, v) == total);
            }
            for (int k : {0, int(p.size()) - 1, int(p.size()), int(rng() % (p.size() + 1))}) {
                string pattern = target;
                if (k < int(p.size())) pattern[k] = pattern[k] == 'a' ? 'b' : 'a';
                auto pred = [&](const string &s) { return s.size() <= pattern.size() && pattern.compare(0, s.size(), s) == 0; };
                int expected = k < int(p.size()) ? p[k] : -1;
                assert(words.find_first_false(u, v, pred) == expected);
                assert(words.get_root(v) == u);
                assert(words.fold(u, v) == target);
            }
        }
    }
}
