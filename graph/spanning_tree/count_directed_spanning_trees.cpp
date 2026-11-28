#ifndef FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_DIRECTED_SPANNING_TREES_CPP
#define FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_DIRECTED_SPANNING_TREES_CPP

#include "../../math/linear_algebra/matrix_determinant.cpp"
#include "../connectivity/SCC.cpp"

struct DirectedSpanningTreeEdge {
    int from, to;
    mint weight = 1;
};

mint count_directed_spanning_trees(int n, int root, const vector<DirectedSpanningTreeEdge> &edges) {
    assert(n >= 1 && 0 <= root && root < n);
    for ([[maybe_unused]] const auto &edge : edges)
        assert(0 <= edge.from && edge.from < n && 0 <= edge.to && edge.to < n);
    if (n == 1) return 1;
    auto reaches_all = [&](int start, bool reverse_edges) {
        int target = n - (start != root);
        vector<char> seen(n);
        vector<int> reached{start};
        seen[start] = true;
        auto visit = [&](int v) {
            reached.push_back(v);
            seen[v] = true;
        };
        auto scan = [&](auto append) {
            for (auto [from, to, weight] : edges) {
                if (reverse_edges) swap(from, to);
                if (!weight.val || from == to || seen[to] || to == root) continue;
                if (from == root && start != root) continue;
                append(from, to);
                if (int(reached.size()) == target) break;
            }
        };
        scan([&](int from, int to) { if (seen[from]) visit(to); });
        if (int(reached.size()) == target) return true;
        vector<vector<int>> outgoing(n);
        scan([&](int from, int to) { outgoing[from].push_back(to); });
        for (int i = 0; i < int(reached.size()); ++i)
            for (int to : outgoing[reached[i]])
                if (!seen[to]) visit(to);
        return int(reached.size()) == target;
    };
    if (!reaches_all(root, false)) return 0;

    int pivot = root == 0 ? 1 : 0;
    vector<int> component(n), sizes{n - 1, 1};
    component[root] = 1;
    if (!reaches_all(pivot, false) || !reaches_all(pivot, true)) {
        SCC scc(n);
        for (auto [from, to, weight] : edges)
            if (weight.val && from != to && from != root && to != root) scc.add_edge(from, to);
        scc.build(false);
        component = std::move(scc.cmp);
        sizes = std::move(scc.sz);
    }

    vector<mint> diagonal(n);
    for (auto [from, to, weight] : edges)
        if (from != to && to != root) diagonal[to] += weight;
    vector<int> index(n);
    vector<vector<vector<mint>>> blocks(sizes.size());
    mint answer = 1;
    for (int v = 0; v < n; ++v) {
        if (v == root) continue;
        int c = component[v];
        if (sizes[c] == 1) {
            answer *= diagonal[v];
        } else {
            auto &block = blocks[c];
            index[v] = block.size();
            block.emplace_back(sizes[c]);
            block.back()[index[v]] = diagonal[v];
        }
    }
    for (auto [from, to, weight] : edges) {
        int c = component[to];
        if (from != to && component[from] == c)
            blocks[c][index[to]][index[from]] -= weight;
    }
    for (auto &block : blocks)
        if (!block.empty()) answer *= matrix_determinant(std::move(block));
    return answer;
}

#endif

/**
 * @brief 有向グラフの全域木数
 */
