template <class T>
class WeightedUnionFind {
    vector<int> uni;
    vector<T> weights;

public:
    explicit WeightedUnionFind(int n, T sum_unity = 0) : uni(n, -1), weights(n, sum_unity) {}

    int root(int a) {
        if (uni[a] < 0) return a;
        int p = uni[a];
        int r = root(p);
        weights[a] += weights[p];
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
        w += weight(a);
        w -= weight(b);
        a = root(a);
        b = root(b);
        if (a == b) return false;
        if (uni[a] > uni[b]) {
            swap(a, b);
            w = -w;
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
        return weight(y) - weight(x);
    }
};

/**
 * @brief 重み付きUnionFind(Weighted Union Find)
 * @docs _md/weightedunionfind.md
 */
