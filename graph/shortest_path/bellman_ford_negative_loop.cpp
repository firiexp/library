template <typename T>
struct edge {
    int from, to;
    T cost;
 
    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
 
    explicit operator int() const {return to;}
};
 
template <typename T>
vector<T> bellman_ford(int s, int N,vector<edge<T> > &G){
    vector<T> dist(N, INF<T>);
    dist[s] = 0;
    for (int i = 0; i < N - 1; ++ i) {
        bool updated = false;
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from]+ e.cost){
                dist[e.to] = dist[e.from]+ e.cost;
                updated = true;
            }
        }
        if (!updated) return dist;
    }
 
    vector<char> negative(N);
    vector<int> q;
    for (auto &&e : G) {
        if (dist[e.from] == INF<T> || negative[e.to]) continue;
        if (dist[e.to] > dist[e.from] + e.cost) {
            negative[e.to] = true;
            q.push_back(e.to);
        }
    }
    if (q.empty()) return dist;
    vector<vector<int>> next(N);
    for (auto &&e : G) next[e.from].push_back(e.to);
    for (size_t i = 0; i < q.size(); ++i) {
        for (int to : next[q[i]]) {
            if (negative[to]) continue;
            negative[to] = true;
            q.push_back(to);
        }
    }
    for (int i = 0; i < N; ++i) {
        if(negative[i]) dist[i] = -INF<T>;
    }
    return dist;
}

/**
 * @brief Bellman-Ford法(負閉路伝播)
 */
