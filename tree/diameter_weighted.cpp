#ifndef FIRIEXP_LIBRARY_TREE_DIAMETER_WEIGHTED_CPP
#define FIRIEXP_LIBRARY_TREE_DIAMETER_WEIGHTED_CPP

namespace tree_diameter_weighted_detail {
template<class T>
pair<T, pair<int, int>> endpoints(const vector<vector<pair<int, T>>> &g, vector<int> *parent) {
    if (g.empty()) return {T(), {-1, -1}};
    struct State {
        int v, prev;
        T dist;
    };
    vector<State> stack;
    auto farthest = [&](int start, vector<int> *parents) {
        pair<T, int> best{T(), start};
        stack.push_back({start, -1, T()});
        while (!stack.empty()) {
            auto [v, prev, dist] = stack.back();
            stack.pop_back();
            if (parents) (*parents)[v] = prev;
            if (best.first < dist) best = {dist, v};
            for (const auto &[to, cost] : g[v]) {
                if (to != prev) stack.push_back({to, v, T(dist + cost)});
            }
        }
        return best;
    };
    int s = farthest(0, nullptr).second;
    auto [length, t] = farthest(s, parent);
    return {length, {s, t}};
}
}

template<class T>
pair<T, pair<int, int>> tree_diameter_weighted(const vector<vector<pair<int, T>>> &g) {
    return tree_diameter_weighted_detail::endpoints(g, nullptr);
}

template<class T>
pair<T, vector<int>> tree_diameter_weighted_path(const vector<vector<pair<int, T>>> &g) {
    vector<int> parent(g.size());
    auto [length, ends] = tree_diameter_weighted_detail::endpoints(g, &parent);
    vector<int> path;
    for (int v = ends.second; v != -1; v = parent[v]) path.push_back(v);
    return {length, std::move(path)};
}

#endif

/**
 * @brief 木の直径(重み付き)
 */
