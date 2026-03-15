template <class G>
class WeightedUnionFind {
    using T = typename G::T;
    vector<int> uni;
    vector<T> weights;

public:
    explicit WeightedUnionFind(int n) : uni(n, -1), weights(n, G::e()) {}

    int root(int a) {
        if (uni[a] < 0) return a;
        int p = uni[a];
        int r = root(p);
        weights[a] = G::op(weights[a], weights[p]);
        return uni[a] = r;
    }

    T weight(int a) {
        root(a);
        return weights[a];
    }

    bool same(int a, int b) {
        return root(a) == root(b);
    }

    bool unite(int a, int b, T w) {
        w = G::op(weight(a), G::op(w, G::inv(weight(b))));
        a = root(a);
        b = root(b);
        if (a == b) return false;
        if (uni[a] > uni[b]) {
            swap(a, b);
            w = G::inv(w);
        }
        uni[a] += uni[b];
        uni[b] = a;
        weights[b] = w;
        return true;
    }

    int size(int a) {
        return -uni[root(a)];
    }

    T diff(int x, int y) {
        return G::op(G::inv(weight(x)), weight(y));
    }
};

/*
struct Group {
    using T = long long;
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T e() { return 0; }
};
*/

/**
 * @brief 重み付きUnionFind(Weighted Union Find)
 */
