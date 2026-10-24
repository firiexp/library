#ifndef FIRIEXP_LIBRARY_GRAPH_CHORDAL_GRAPH_CPP
#define FIRIEXP_LIBRARY_GRAPH_CHORDAL_GRAPH_CPP

struct ChordalResult {
    bool chordal;
    vector<int> peo;
    vector<int> induced_cycle;
};

namespace chordal_graph_detail {
struct Graph {
    vector<int> offset, adjacent;

    Graph(int n, const vector<pair<int, int>> &edges) {
        assert(n >= 0);
        offset.resize(n + 1);
        for (auto [u, v] : edges) {
            assert(0 <= u && u < n && 0 <= v && v < n && u != v);
            ++offset[u + 1];
            ++offset[v + 1];
        }
        for (int v = 0; v < n; ++v) offset[v + 1] += offset[v];
        adjacent.resize(offset.back());
        vector<int> cursor = offset;
        for (auto [u, v] : edges) {
            adjacent[cursor[u]++] = v;
            adjacent[cursor[v]++] = u;
        }
    }
};

ChordalResult recognize(const Graph &graph) {
    const auto &offset = graph.offset;
    const auto &adjacent = graph.adjacent;
    int n = (int)offset.size() - 1;
    vector<int> head(n + 1, -1), next(n), prev(n), weight(n), index(n, -1), order;
    order.reserve(n);
    for (int v = 0; v < n; ++v) {
        next[v] = v + 1 < n ? v + 1 : -1;
        prev[v] = v - 1;
    }
    if (n) head[0] = 0;
    int maximum = 0;
    for (int i = 0; i < n; ++i) {
        while (head[maximum] == -1) --maximum;
        int v = head[maximum];
        head[maximum] = next[v];
        if (next[v] != -1) prev[next[v]] = -1;
        index[v] = i;
        order.push_back(v);
        for (int j = offset[v]; j < offset[v + 1]; ++j) {
            int u = adjacent[j];
            if (index[u] != -1) continue;
            if (prev[u] == -1) head[weight[u]] = next[u];
            else next[prev[u]] = next[u];
            if (next[u] != -1) prev[next[u]] = prev[u];
            ++weight[u];
            prev[u] = -1;
            next[u] = head[weight[u]];
            if (next[u] != -1) prev[next[u]] = u;
            head[weight[u]] = u;
            maximum = max(maximum, weight[u]);
        }
    }

    fill(head.begin(), head.end(), -1);
    for (int v = 0; v < n; ++v) {
        int parent = -1;
        for (int j = offset[v]; j < offset[v + 1]; ++j) {
            int u = adjacent[j];
            if (index[u] < index[v] && (parent == -1 || index[parent] < index[u])) parent = u;
        }
        if (parent == -1) continue;
        next[v] = head[parent];
        head[parent] = v;
    }
    fill(prev.begin(), prev.end(), -1);
    int bad = -1, left = -1, right = -1;
    for (int p = 0; p < n; ++p) {
        if (head[p] == -1) continue;
        for (int j = offset[p]; j < offset[p + 1]; ++j) prev[adjacent[j]] = p;
        for (int v = head[p]; v != -1; v = next[v]) {
            if (bad != -1 && index[bad] < index[v]) continue;
            for (int j = offset[v]; j < offset[v + 1]; ++j) {
                int u = adjacent[j];
                if (index[u] < index[p] && prev[u] != p) {
                    bad = v;
                    left = u;
                    right = p;
                    break;
                }
            }
        }
    }
    if (bad == -1) {
        reverse(order.begin(), order.end());
        return {true, std::move(order), {}};
    }

    fill(weight.begin(), weight.end(), 0);
    weight[bad] = 1;
    for (int j = offset[bad]; j < offset[bad + 1]; ++j) weight[adjacent[j]] = 1;
    weight[left] = weight[right] = 0;
    fill(prev.begin(), prev.end(), -1);
    prev[left] = left;
    order.clear();
    order.push_back(left);
    for (size_t i = 0; i < order.size() && prev[right] == -1; ++i) {
        int v = order[i];
        for (int j = offset[v]; j < offset[v + 1]; ++j) {
            int u = adjacent[j];
            if (weight[u] || prev[u] != -1) continue;
            prev[u] = v;
            order.push_back(u);
        }
    }
    assert(prev[right] != -1);
    vector<int> cycle{bad};
    for (int v = right; v != left; v = prev[v]) cycle.push_back(v);
    cycle.push_back(left);
    return {false, {}, std::move(cycle)};
}

}

ChordalResult recognize_chordal(int n, const vector<pair<int, int>> &edges) {
    return chordal_graph_detail::recognize(chordal_graph_detail::Graph(n, edges));
}

struct ChordalColoringResult {
    bool chordal;
    int color_count;
    vector<int> color, max_clique, induced_cycle;
};

ChordalColoringResult chordal_coloring(int n, const vector<pair<int, int>> &edges) {
    chordal_graph_detail::Graph graph(n, edges);
    auto result = chordal_graph_detail::recognize(graph);
    if (!result.chordal) return {false, 0, {}, {}, std::move(result.induced_cycle)};
    vector<int> color(n, -1), marker(n, -1), position(n);
    for (int i = 0; i < n; ++i) position[result.peo[i]] = i;
    int color_count = 0, clique_size = 0, best = -1;
    for (int i = n - 1; i >= 0; --i) {
        int v = result.peo[i], degree = 1;
        for (int j = graph.offset[v]; j < graph.offset[v + 1]; ++j) {
            int u = graph.adjacent[j];
            if (color[u] == -1) continue;
            marker[color[u]] = v;
            ++degree;
        }
        int c = 0;
        while (marker[c] == v) ++c;
        color[v] = c;
        color_count = max(color_count, c + 1);
        if (degree > clique_size) {
            clique_size = degree;
            best = v;
        }
    }
    vector<int> clique;
    if (best != -1) {
        clique.reserve(clique_size);
        clique.push_back(best);
        for (int j = graph.offset[best]; j < graph.offset[best + 1]; ++j) {
            int u = graph.adjacent[j];
            if (position[u] > position[best]) clique.push_back(u);
        }
    }
    return {true, color_count, std::move(color), std::move(clique), {}};
}

#endif

/**
 * @brief 弦グラフ判定、完全除去順序・誘導閉路の復元
 */
