template<class F>
void enumerate_triangles(int n, const vector<pair<int, int>> &edges, F &&callback) {
    vector<int> degree(n), start(n + 1);
    for (auto [u, v] : edges) {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        ++degree[u];
        ++degree[v];
    }
    auto reversed = [&](int u, int v) {
        return degree[u] > degree[v] || (degree[u] == degree[v] && u > v);
    };
    for (auto [u, v] : edges) {
        if (reversed(u, v)) swap(u, v);
        ++start[u + 1];
    }
    for (int v = 0; v < n; ++v) start[v + 1] += start[v];
    vector<int> to(edges.size()), cursor = start;
    for (auto [u, v] : edges) {
        if (reversed(u, v)) swap(u, v);
        to[cursor[u]++] = v;
    }
    fill(cursor.begin(), cursor.end(), -1);
    for (int u = 0; u < n; ++u) {
        for (int i = start[u]; i < start[u + 1]; ++i) cursor[to[i]] = u;
        for (int i = start[u]; i < start[u + 1]; ++i) {
            int v = to[i];
            for (int j = start[v]; j < start[v + 1]; ++j) {
                int w = to[j];
                if (cursor[w] != u) continue;
                int a = u, b = v, c = w;
                if (a > b) swap(a, b);
                if (b > c) swap(b, c);
                if (a > b) swap(a, b);
                callback(a, b, c);
            }
        }
    }
}

/**
 * @brief 無向グラフの三角形列挙
 */
