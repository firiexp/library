template <typename T>
struct edge {
    int from, to;
    T cost;

    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}

    explicit operator int() const {return to;}
};

template <typename T>
vector<T> bellman_ford(int s, int V,vector<edge<T> > &G){
    const T INF = numeric_limits<T>::max();
    vector<T> d(V, INF);
    d[s] = 0;
    for (int i = 0; i < V - 1; ++i) {
        for (auto &&e : G) {
            if (d[e.from] == INF) continue;
            d[e.to] = min(d[e.to], d[e.from] + e.cost);
        }
    }
    for (auto &&e : G) {
        if(d[e.from] == INF) continue;
        if(d[e.from] + e.cost < d[e.to]) return vector<T> ();
    }
    return d;
}