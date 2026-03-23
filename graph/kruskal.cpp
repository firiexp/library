template <class T>
struct edge {
    int from, to, idx;
    T cost;

    edge(int from, int to, T cost, int idx = -1) : from(from), to(to), idx(idx), cost(cost) {}
};

class KruskalUnionFind {
    vector<int> p;

public:
    explicit KruskalUnionFind(int n) : p(n, -1) {}

    int root(int x) {
        if (p[x] < 0) return x;
        return p[x] = root(p[x]);
    }

    bool unite(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

template <class T>
struct KruskalResult {
    bool exists;
    T cost;
    vector<int> edge_id;
};

template <class T>
KruskalResult<T> kruskal(vector<edge<T>> edges, int n) {
    for (int i = 0; i < (int)edges.size(); ++i) {
        if (edges[i].idx == -1) edges[i].idx = i;
    }
    sort(edges.begin(), edges.end(), [](const edge<T> &a, const edge<T> &b) {
        if (a.cost != b.cost) return a.cost < b.cost;
        return a.idx < b.idx;
    });

    KruskalUnionFind uf(n);
    T cost = T(0);
    vector<int> edge_id;
    edge_id.reserve(max(0, n - 1));
    for (auto &&e : edges) {
        if (!uf.unite(e.from, e.to)) continue;
        cost += e.cost;
        edge_id.push_back(e.idx);
    }
    if ((int)edge_id.size() != max(0, n - 1)) return {false, T(0), {}};
    return {true, cost, edge_id};
}

/**
 * @brief 最小全域木(Kruskal法)
 */
