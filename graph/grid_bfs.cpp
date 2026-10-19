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

struct GridBFSTargetResult {
    int distance;
    vector<pair<int, int>> path;
};

namespace grid_bfs_detail {
    template<bool TargetOnly, class Passable>
    auto search(int h, int w, const vector<pair<int, int>> &sources, int tr, int tc, Passable passable) {
        assert(h >= 0 && w >= 0 && 1LL * h * w <= numeric_limits<int>::max());
        if constexpr (TargetOnly) assert(0 <= tr && tr < h && 0 <= tc && tc < w);
        vector<int> ids;
        for (auto [r, c] : sources) {
            assert(0 <= r && r < h && 0 <= c && c < w);
            if (passable(r, c)) ids.push_back(r * w + c);
        }
        auto result = generated_shortest_path_detail::bfs<TargetOnly>(h * w, ids, TargetOnly ? tr * w + tc : -1, [&](int v, auto emit) {
            int r = v / w, c = v % w;
            for (auto [dr, dc] : {pair<int, int>{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                int nr = r + dr, nc = c + dc;
                if (0 <= nr && nr < h && 0 <= nc && nc < w && passable(nr, nc)) emit(nr * w + nc);
            }
        });
        if constexpr (TargetOnly) {
            vector<pair<int, int>> path;
            path.reserve(result.path.size());
            for (int v : result.path) path.emplace_back(v / w, v % w);
            return GridBFSTargetResult{result.distance, std::move(path)};
        } else return GridBFSResult{h, w, std::move(result)};
    }

}

template<class Passable>
GridBFSResult grid_bfs(int h, int w, const vector<pair<int, int>> &sources, Passable passable) {
    return grid_bfs_detail::search<false>(h, w, sources, -1, -1, std::move(passable));
}

template<class Passable>
GridBFSResult grid_bfs(int h, int w, int sr, int sc, Passable passable) {
    return grid_bfs(h, w, vector<pair<int, int>>{{sr, sc}}, std::move(passable));
}

template<class Passable>
GridBFSTargetResult grid_bfs_to(int h, int w, const vector<pair<int, int>> &sources, int tr, int tc, Passable passable) {
    return grid_bfs_detail::search<true>(h, w, sources, tr, tc, std::move(passable));
}

template<class Passable>
GridBFSTargetResult grid_bfs_to(int h, int w, int sr, int sc, int tr, int tc, Passable passable) {
    return grid_bfs_to(h, w, vector<pair<int, int>>{{sr, sc}}, tr, tc, std::move(passable));
}

#endif

/**
 * @brief グリッドの4近傍最短路
 */
