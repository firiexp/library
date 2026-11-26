namespace count_c4_detail {

template<class F>
void for_each_root(int n, const vector<pair<int, int>> &edges, F process) {
    assert(n >= 0);
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < (int)edges.size(); ++i) {
        auto [u, v] = edges[i];
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    auto lower = [&](int u, int v) {
        if (adj[u].size() != adj[v].size()) return adj[u].size() < adj[v].size();
        return u < v;
    };
    for (auto &neighbors : adj) {
        sort(neighbors.begin(), neighbors.end(), [&](auto a, auto b) {
            return lower(a.first, b.first);
        });
    }
    for (int root = 0; root < n; ++root) {
        process(root, [&](auto visit) {
            for (auto [v, first] : adj[root]) {
                if (!lower(v, root)) break;
                for (auto [w, second] : adj[v]) {
                    if (w == root) break;
                    visit(w, first, second);
                }
            }
        });
    }
}

}

long long count_c4(int n, const vector<pair<int, int>> &edges) {
    vector<int> paths(n), last_root(n, -1);
    long long total = 0;
    count_c4_detail::for_each_root(n, edges, [&](int root, auto visit_paths) {
        visit_paths([&](int w, int, int) {
            if (last_root[w] != root) {
                last_root[w] = root;
                paths[w] = 0;
            }
            total += paths[w];
            ++paths[w];
        });
    });
    return total;
}

/**
 * @brief 無向グラフの長さ4の閉路数
 */
