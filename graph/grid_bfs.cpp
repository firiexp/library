#ifndef FIRIEXP_LIBRARY_GRAPH_GRID_BFS_CPP
#define FIRIEXP_LIBRARY_GRAPH_GRID_BFS_CPP

#include "generated_shortest_path.cpp"

struct GridBFSResult {
    int h, w;
    GeneratedShortestPathResult<int> paths;

    int distance(int r, int c) const {
        assert(0 <= r && r < h && 0 <= c && c < w);
        return paths.dist[r * w + c];
    }

    vector<pair<int, int>> path_to(int r, int c) const {
        if (r < 0 || r >= h || c < 0 || c >= w) return {};
        vector<pair<int, int>> path;
        for (int v : paths.path_to(r * w + c)) path.emplace_back(v / w, v % w);
        return path;
    }
};

template<class Passable>
GridBFSResult grid_bfs(int h, int w, const vector<pair<int, int>> &sources, Passable passable) {
    assert(h >= 0 && w >= 0 && 1LL * h * w <= numeric_limits<int>::max());
    vector<int> ids;
    for (auto [r, c] : sources) {
        assert(0 <= r && r < h && 0 <= c && c < w);
        if (passable(r, c)) ids.push_back(r * w + c);
    }
    auto result = bfs_generated(h * w, ids, [&](int v, auto emit) {
        int r = v / w, c = v % w;
        for (auto [dr, dc] : {pair<int, int>{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            int nr = r + dr, nc = c + dc;
            if (0 <= nr && nr < h && 0 <= nc && nc < w && passable(nr, nc)) emit(nr * w + nc);
        }
    });
    return {h, w, std::move(result)};
}

template<class Passable>
GridBFSResult grid_bfs(int h, int w, int sr, int sc, Passable passable) {
    return grid_bfs(h, w, vector<pair<int, int>>{{sr, sc}}, std::move(passable));
}

#endif

/**
 * @brief グリッドの4近傍最短路
 */
