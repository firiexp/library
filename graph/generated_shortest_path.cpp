#ifndef FIRIEXP_LIBRARY_GRAPH_GENERATED_SHORTEST_PATH_CPP
#define FIRIEXP_LIBRARY_GRAPH_GENERATED_SHORTEST_PATH_CPP

template<class T>
struct GeneratedShortestPathResult {
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

namespace generated_shortest_path_detail {
    template<class T, class Push>
    GeneratedShortestPathResult<T> initialize(int n, const vector<int> &sources, Push push) {
        assert(n >= 0);
        GeneratedShortestPathResult<T> result{vector<T>(n, INF<T>), vector<int>(n, -1)};
        for (int s : sources) {
            assert(0 <= s && s < n);
            if (result.dist[s] == T(0)) continue;
            result.dist[s] = T(0);
            push(s);
        }
        return result;
    }
}

template<class T, class ForEachEdge>
GeneratedShortestPathResult<T> dijkstra_generated(int n, const vector<int> &sources, ForEachEdge for_each_edge) {
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> queue;
    auto result = generated_shortest_path_detail::initialize<T>(n, sources, [&](int s) { queue.emplace(T(0), s); });
    while (!queue.empty()) {
        auto [distance, v] = queue.top();
        queue.pop();
        if (distance != result.dist[v]) continue;
        for_each_edge(v, [&](int to, T cost) {
            assert(0 <= to && to < n && cost >= T(0));
            if (cost >= INF<T> - distance) return;
            T next = distance + cost;
            if (result.dist[to] <= next) return;
            result.dist[to] = next;
            result.parent[to] = v;
            queue.emplace(next, to);
        });
    }
    return result;
}

template<class T, class ForEachEdge>
GeneratedShortestPathResult<T> dijkstra_generated(int n, int source, ForEachEdge for_each_edge) {
    return dijkstra_generated<T>(n, vector<int>{source}, std::move(for_each_edge));
}

template<class ForEachEdge>
GeneratedShortestPathResult<int> bfs_generated(int n, const vector<int> &sources, ForEachEdge for_each_edge) {
    vector<int> queue;
    queue.reserve(n);
    auto result = generated_shortest_path_detail::initialize<int>(n, sources, [&](int s) { queue.push_back(s); });
    for (size_t i = 0; i < queue.size(); ++i) {
        int v = queue[i];
        for_each_edge(v, [&](int to) {
            assert(0 <= to && to < n);
            if (result.dist[to] != INF<int>) return;
            result.dist[to] = result.dist[v] + 1;
            result.parent[to] = v;
            queue.push_back(to);
        });
    }
    return result;
}

template<class ForEachEdge>
GeneratedShortestPathResult<int> bfs_generated(int n, int source, ForEachEdge for_each_edge) {
    return bfs_generated(n, vector<int>{source}, std::move(for_each_edge));
}

template<class T = int, class ForEachEdge>
GeneratedShortestPathResult<T> bfs01_generated(int n, const vector<int> &sources, ForEachEdge for_each_edge) {
    deque<int> queue;
    auto result = generated_shortest_path_detail::initialize<T>(n, sources, [&](int s) { queue.push_back(s); });
    vector<char> settled(n);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop_front();
        if (settled[v]) continue;
        settled[v] = true;
        for_each_edge(v, [&](int to, T cost) {
            assert(0 <= to && to < n && (cost == T(0) || cost == T(1)));
            T next = result.dist[v] + cost;
            if (result.dist[to] <= next) return;
            result.dist[to] = next;
            result.parent[to] = v;
            if (cost == T(0)) queue.push_front(to);
            else queue.push_back(to);
        });
    }
    return result;
}

template<class T = int, class ForEachEdge>
GeneratedShortestPathResult<T> bfs01_generated(int n, int source, ForEachEdge for_each_edge) {
    return bfs01_generated<T>(n, vector<int>{source}, std::move(for_each_edge));
}

#endif

/**
 * @brief 辺を都度生成する最短路
 */
