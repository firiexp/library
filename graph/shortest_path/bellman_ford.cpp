#include "../edge.cpp"

template <typename T>
vector<T> bellman_ford(int s, int V,vector<edge<T> > &G){
    const T INF = numeric_limits<T>::max();
    vector<T> d(V, INF);
    d[s] = 0;
    for (int i = 0; i < V - 1; ++i) {
        bool updated = false;
        for (auto &&e : G) {
            if (d[e.from] == INF) continue;
            if (d[e.from] + e.cost < d[e.to]) {
                d[e.to] = d[e.from] + e.cost;
                updated = true;
            }
        }
        if (!updated) return d;
    }
    for (auto &&e : G) {
        if(d[e.from] == INF) continue;
        if(d[e.from] + e.cost < d[e.to]) return vector<T> ();
    }
    return d;
}

template <typename T>
vector<int> bellman_ford_negative_cycle(int s, int n, const vector<edge<T>> &edges) {
    vector<T> dist(n, T(0));
    vector<unsigned char> reached(n, false);
    vector<int> parent_edge(n, -1);
    reached[s] = true;
    int last = -1;
    for (int step = 0; step < n; ++step) {
        last = -1;
        for (int id = 0; id < (int)edges.size(); ++id) {
            const auto &e = edges[id];
            if (!reached[e.from]) continue;
            T next = dist[e.from] + e.cost;
            if (reached[e.to] && !(next < dist[e.to])) continue;
            dist[e.to] = next;
            reached[e.to] = true;
            parent_edge[e.to] = id;
            last = e.to;
        }
        if (last == -1) return {};
    }
    for (int i = 0; i < n; ++i) last = edges[parent_edge[last]].from;
    vector<int> cycle;
    int v = last;
    do {
        int id = parent_edge[v];
        cycle.push_back(id);
        v = edges[id].from;
    } while (v != last);
    return {cycle.rbegin(), cycle.rend()};
}

/**
 * @brief Bellman-Ford法
 */
