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
    vector<bool> negative(N);
    dist[s] = 0;
    for (int i = 0; i < N - 1; ++ i) {
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from]+ e.cost){
                dist[e.to] = dist[e.from]+ e.cost;
            }
        }
    }
 
    ll ans = dist[N - 1];
 
    for (int i = 0; i < N ; ++i) {
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from] + e.cost){
                dist[e.to] = dist[e.from] + e.cost;
                negative[e.to] = true;
            }
            if(negative[e.from]) negative[e.to] = true;
        }
    }
    for (int i = 0; i < N; ++i) {
        if(negative[i]) dist[i] = -INF<T>;
    }
    return dist;
}