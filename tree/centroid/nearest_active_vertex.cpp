#include "centroid_decomposition_query_helper.cpp"

class NearestActiveVertex {
    vector<vector<int>> path, dist;
    vector<set<pair<int, int>>> candidates;
    vector<char> active;

public:
    explicit NearestActiveVertex(const vector<vector<int>> &g)
        : candidates(g.size()), active(g.size(), false) {
        CentroidDecompositionQueryHelper cd(g.size());
        cd.G = g;
        cd.build();
        path = move(cd.path);
        dist = move(cd.dist);
    }

    void set_active(int v, bool enabled) {
        if(active[v] == enabled) return;
        active[v] = enabled;
        for(int i = 0; i < int(path[v].size()); ++i) {
            int c = path[v][i];
            pair<int, int> key{dist[v][i], v};
            if(enabled) candidates[c].insert(key);
            else candidates[c].erase(key);
        }
    }

    pair<int, int> nearest(int v) const {
        pair<int, int> result{-1, -1};
        for(int i = 0; i < int(path[v].size()); ++i) {
            int c = path[v][i];
            if(candidates[c].empty()) continue;
            auto [distance, u] = *candidates[c].begin();
            pair<int, int> candidate{dist[v][i] + distance, u};
            if(result.second == -1 || candidate < result) result = candidate;
        }
        return result;
    }
};

/**
 * @brief 木の最近傍有効頂点
 */
