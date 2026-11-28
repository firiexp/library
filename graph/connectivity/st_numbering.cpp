#ifndef FIRIEXP_LIBRARY_GRAPH_CONNECTIVITY_ST_NUMBERING_CPP
#define FIRIEXP_LIBRARY_GRAPH_CONNECTIVITY_ST_NUMBERING_CPP

inline vector<int> st_numbering(const vector<vector<int>> &g, int s, int t) {
    int n = g.size();
    if (s < 0 || s >= n || t < 0 || t >= n || s == t) return {};

    vector<int> preorder{s, t}, index(n, -1), low(n), parent(n), cursor(n);
    index[s] = low[s] = 0;
    index[t] = low[t] = 1;
    parent[t] = s;
    for (int v = t; v != s; ) {
        if (cursor[v] == int(g[v].size())) {
            int p = parent[v];
            if (v != t && low[v] >= index[p]) return {};
            low[p] = min(low[p], low[v]);
            v = p;
            continue;
        }
        int u = g[v][cursor[v]++];
        if (index[u] != -1) {
            low[v] = min(low[v], index[u]);
        } else {
            parent[u] = v;
            index[u] = low[u] = preorder.size();
            preorder.push_back(u);
            v = u;
        }
    }
    if (int(preorder.size()) != n || low[t] != index[s]) return {};

    vector<int> prev(n), next(n), sign(n, -1);
    prev[t] = s;
    next[s] = t;
    for (int i = 2; i < n; ++i) {
        int v = preorder[i], p = parent[v];
        int side = sign[preorder[low[v]]];
        int left = side < 0 ? prev[p] : p;
        int right = next[left];
        prev[v] = left;
        next[v] = right;
        next[left] = prev[right] = v;
        sign[p] = -side;
    }
    vector<int> order(n);
    order[0] = s;
    for (int i = 1; i < n; ++i) order[i] = next[order[i - 1]];
    return order;
}

#endif

/**
 * @brief 無向グラフの st-numbering
 */
