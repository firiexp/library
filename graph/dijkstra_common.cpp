#ifndef FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_COMMON_CPP
#define FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_COMMON_CPP

template <typename T>
struct edge {
    int from, to;
    T cost;

    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
};

template <typename T>
struct DijkstraPriorityQueue {
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;

    bool empty() const { return q.empty(); }

    void push(T cost, int v) {
        q.emplace(cost, v);
    }

    pair<T, int> pop() {
        auto res = q.top();
        q.pop();
        return res;
    }
};

template <typename T, class Queue, class OnRelax>
vector<T> dijkstra_internal(int s, const vector<vector<edge<T>>> &G, Queue &Q, OnRelax on_relax) {
    int n = (int)G.size();
    vector<T> dist(n, INF<T>);
    dist[s] = 0;
    Q.push(T(0), s);
    while (!Q.empty()) {
        auto [cost, v] = Q.pop();
        if (dist[v] < cost) continue;
        for (auto &&e : G[v]) {
            T nxt = cost + e.cost;
            if (dist[e.to] <= nxt) continue;
            dist[e.to] = nxt;
            on_relax(v, e);
            Q.push(nxt, e.to);
        }
    }
    return dist;
}

template <typename T, class Queue>
vector<T> dijkstra_internal(int s, const vector<vector<edge<T>>> &G, Queue &Q) {
    return dijkstra_internal(s, G, Q, [](int, const edge<T> &) {});
}

#endif
