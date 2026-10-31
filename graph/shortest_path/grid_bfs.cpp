#ifndef FIRIEXP_LIBRARY_GRAPH_GRID_BFS_CPP
#define FIRIEXP_LIBRARY_GRAPH_GRID_BFS_CPP

#include "generated_shortest_path.cpp"

struct GridPaths {
    int h, w;
    ShortestPaths<int> paths;

    int dist(int r, int c) const {
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

struct GridPath {
    int dist;
    vector<pair<int, int>> path;
};

namespace grid_bfs_detail {
    template<bool To, class Passable>
    auto search(int h, int w, const vector<pair<int, int>> &src, int tr, int tc, Passable passable) {
        assert(h >= 0 && w >= 0 && 1LL * h * w <= numeric_limits<int>::max());
        if constexpr (To) assert(0 <= tr && tr < h && 0 <= tc && tc < w);
        vector<int> ids;
        for (auto [r, c] : src) {
            assert(0 <= r && r < h && 0 <= c && c < w);
            if (passable(r, c)) ids.push_back(r * w + c);
        }
        auto res = gen_sp_detail::bfs<To>(h * w, ids, To ? tr * w + tc : -1, [&](int v, auto emit) {
            int r = v / w, c = v % w;
            for (auto [dr, dc] : {pair<int, int>{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                int nr = r + dr, nc = c + dc;
                if (0 <= nr && nr < h && 0 <= nc && nc < w && passable(nr, nc)) emit(nr * w + nc);
            }
        });
        if constexpr (To) {
            vector<pair<int, int>> path;
            path.reserve(res.path.size());
            for (int v : res.path) path.emplace_back(v / w, v % w);
            return GridPath{res.dist, std::move(path)};
        } else return GridPaths{h, w, std::move(res)};
    }
}

template<class Passable>
GridPaths grid_bfs(int h, int w, const vector<pair<int, int>> &src, Passable passable) {
    return grid_bfs_detail::search<false>(h, w, src, -1, -1, std::move(passable));
}

template<class Passable>
GridPaths grid_bfs(int h, int w, int sr, int sc, Passable passable) {
    return grid_bfs(h, w, vector<pair<int, int>>{{sr, sc}}, std::move(passable));
}

template<class Passable>
GridPath grid_bfs_to(int h, int w, const vector<pair<int, int>> &src, int tr, int tc, Passable passable) {
    return grid_bfs_detail::search<true>(h, w, src, tr, tc, std::move(passable));
}

template<class Passable>
GridPath grid_bfs_to(int h, int w, int sr, int sc, int tr, int tc, Passable passable) {
    return grid_bfs_to(h, w, vector<pair<int, int>>{{sr, sc}}, tr, tc, std::move(passable));
}

#endif

/**
 * @brief グリッドの4近傍最短路
 */
