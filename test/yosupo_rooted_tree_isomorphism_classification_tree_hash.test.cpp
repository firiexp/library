#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include <algorithm>
#include <cassert>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace std;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/tree_hash.cpp"

string canonical_dfs(int v, const vector<vector<int>> &ch) {
    vector<string> subs;
    subs.reserve(ch[v].size());
    for (int to : ch[v]) subs.push_back(canonical_dfs(to, ch));
    sort(subs.begin(), subs.end());
    string res = "(";
    for (const auto &s : subs) res += s;
    res += ")";
    return res;
}

void self_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 300; ++tc) {
        int n = rng() % 30 + 1;
        int root = rng() % n;
        vector<pair<int, int>> edges;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            int p = rng() % v;
            edges.push_back({p, v});
            g[p].push_back(v);
            g[v].push_back(p);
        }

        vector<int> parent(n, -1), order;
        order.reserve(n);
        vector<int> st(1, root);
        parent[root] = root;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            order.push_back(v);
            for (int to : g[v]) {
                if (to == parent[v]) continue;
                parent[to] = v;
                st.push_back(to);
            }
        }

        vector<vector<int>> ch(n);
        for (int v = 0; v < n; ++v) {
            if (v == root) continue;
            ch[parent[v]].push_back(v);
        }

        vector<string> canon(n);
        for (int i = n - 1; i >= 0; --i) canon[order[i]] = canonical_dfs(order[i], ch);

        TreeHash th(n);
        for (auto [u, v] : edges) th.add_edge(u, v);
        auto id = th.build(root);

        map<string, int> expect;
        for (int v = 0; v < n; ++v) {
            if (!expect.count(canon[v])) expect[canon[v]] = expect.size();
        }
        assert(th.kinds() == (int)expect.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                assert((id[i] == id[j]) == (canon[i] == canon[j]));
            }
        }
    }
}

int main() {
    self_check();

    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    TreeHash th(n);
    for (int v = 1; v < n; ++v) {
        int p;
        sc.read(p);
        th.add_edge(p, v);
    }
    auto id = th.build(0);
    pr.writeln(th.kinds());
    for (int i = 0; i < n; ++i) {
        pr.write(id[i]);
        pr.write(i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
