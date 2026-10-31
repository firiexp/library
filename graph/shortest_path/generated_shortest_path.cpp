#ifndef FIRIEXP_LIBRARY_GRAPH_GENERATED_SHORTEST_PATH_CPP
#define FIRIEXP_LIBRARY_GRAPH_GENERATED_SHORTEST_PATH_CPP

template<class T>
struct ShortestPaths {
    vector<T> dist;
    vector<int> parent;

    vector<int> path_to(int t) const {
        if (t < 0 || t >= (int)dist.size() || dist[t] == INF<T>) return {};
        vector<int> path;
        for (; t != -1; t = parent[t]) path.push_back(t);
        reverse(path.begin(), path.end());
        return path;
    }
};

template<class T>
struct ShortestPath {
    T dist;
    vector<int> path;
};

namespace gen_sp_detail {
    template<class T, class S, class Push>
    ShortestPaths<T> init(int n, const S &src, Push push) {
        assert(n >= 0);
        ShortestPaths<T> res{vector<T>(n, INF<T>), vector<int>(n, -1)};
        auto add = [&](int s) {
            assert(0 <= s && s < n);
            if (res.dist[s] == T(0)) return;
            res.dist[s] = T(0);
            push(s);
        };
        if constexpr (is_integral_v<S>) add(src);
        else for (int s : src) add(s);
        return res;
    }

    template<bool To, class T>
    auto finish(ShortestPaths<T> res, int t) {
        if constexpr (To) return ShortestPath<T>{res.dist[t], res.path_to(t)};
        else return res;
    }

    template<bool To, class T, class S, class F>
    auto dijkstra(int n, const S &src, int t, F adj) {
        if constexpr (To) assert(0 <= t && t < n);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        auto res = init<T>(n, src, [&](int s) { q.emplace(T(0), s); });
        while (!q.empty()) {
            auto [d, v] = q.top();
            q.pop();
            if (d != res.dist[v]) continue;
            if constexpr (To) if (v == t) break;
            adj(v, [&](int to, T cost) {
                assert(0 <= to && to < n && cost >= T(0));
                if (cost >= INF<T> - d) return;
                T nd = d + cost;
                if (res.dist[to] <= nd) return;
                res.dist[to] = nd;
                res.parent[to] = v;
                q.emplace(nd, to);
            });
        }
        return finish<To>(std::move(res), t);
    }

    template<bool To, class S, class F>
    auto bfs(int n, const S &src, int t, F adj) {
        if constexpr (To) assert(0 <= t && t < n);
        vector<int> q;
        q.reserve(n);
        auto res = init<int>(n, src, [&](int s) { q.push_back(s); });
        for (size_t i = 0; i < q.size(); ++i) {
            int v = q[i];
            if constexpr (To) if (v == t) break;
            adj(v, [&](int to) {
                assert(0 <= to && to < n);
                if (res.dist[to] != INF<int>) return;
                res.dist[to] = res.dist[v] + 1;
                res.parent[to] = v;
                q.push_back(to);
            });
        }
        return finish<To>(std::move(res), t);
    }

    template<bool To, class T, class S, class F>
    auto bfs01(int n, const S &src, int t, F adj) {
        if constexpr (To) assert(0 <= t && t < n);
        deque<int> q;
        auto res = init<T>(n, src, [&](int s) { q.push_back(s); });
        vector<char> done(n);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            if (done[v]) continue;
            done[v] = true;
            if constexpr (To) if (v == t) break;
            adj(v, [&](int to, T cost) {
                assert(0 <= to && to < n && (cost == T(0) || cost == T(1)));
                T nd = res.dist[v] + cost;
                if (res.dist[to] <= nd) return;
                res.dist[to] = nd;
                res.parent[to] = v;
                if (cost == T(0)) q.push_front(to);
                else q.push_back(to);
            });
        }
        return finish<To>(std::move(res), t);
    }
}

template<class T, class S = vector<int>, class F>
ShortestPaths<T> dijkstra_generated(int n, const S &src, F adj) {
    return gen_sp_detail::dijkstra<false, T>(n, src, -1, std::move(adj));
}

template<class T, class S = vector<int>, class F>
ShortestPath<T> dijkstra_generated_to(int n, const S &src, int t, F adj) {
    return gen_sp_detail::dijkstra<true, T>(n, src, t, std::move(adj));
}

template<class S = vector<int>, class F>
ShortestPaths<int> bfs_generated(int n, const S &src, F adj) {
    return gen_sp_detail::bfs<false>(n, src, -1, std::move(adj));
}

template<class S = vector<int>, class F>
ShortestPath<int> bfs_generated_to(int n, const S &src, int t, F adj) {
    return gen_sp_detail::bfs<true>(n, src, t, std::move(adj));
}

template<class T = int, class S = vector<int>, class F>
ShortestPaths<T> bfs01_generated(int n, const S &src, F adj) {
    return gen_sp_detail::bfs01<false, T>(n, src, -1, std::move(adj));
}

template<class T = int, class S = vector<int>, class F>
ShortestPath<T> bfs01_generated_to(int n, const S &src, int t, F adj) {
    return gen_sp_detail::bfs01<true, T>(n, src, t, std::move(adj));
}

#endif

/**
 * @brief 陽に辺を持たないグラフの最短路
 */
