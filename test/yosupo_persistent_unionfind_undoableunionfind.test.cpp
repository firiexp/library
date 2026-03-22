#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/undoableunionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    using A = array<int, 4>;
    vector<vector<A>> g(q + 1);
    vector<int> ans(q + 1, -1);
    for (int i = 1; i <= q; ++i) {
        int t, k, u, v;
        sc.read(t, k, u, v);
        ++k;
        g[k].push_back({t, i, u, v});
    }

    UndoableUnionFind uf(n);
    struct Frame {
        A cur;
        int child_idx;
        bool entered;
        bool united;
    };
    vector<Frame> st = {{A{-1, 0, -1, -1}, 0, false, false}};
    while (!st.empty()) {
        auto &cur = st.back();
        int t = cur.cur[0], idx = cur.cur[1], u = cur.cur[2], v = cur.cur[3];
        if (!cur.entered) {
            cur.entered = true;
            if (t == 1) {
                ans[idx] = uf.same(u, v);
                st.pop_back();
                continue;
            }
            if (t == 0) {
                uf.unite(u, v);
                cur.united = true;
            }
        }
        if (cur.child_idx < (int)g[idx].size()) {
            st.push_back({g[idx][cur.child_idx++], 0, false, false});
            continue;
        }
        if (cur.united) uf.undo();
        st.pop_back();
    }

    for (int i = 1; i <= q; ++i) {
        if (ans[i] != -1) pr.println(ans[i]);
    }
    return 0;
}
