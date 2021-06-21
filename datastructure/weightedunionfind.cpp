template <class T>
class WeightedUnionFind {
    vector<int> uni;
    vector<T> weights;
    int n;
public:
    explicit WeightedUnionFind(int n, T SUM_UNITY = 0) :
    uni(static_cast<uint>(n), -1) , n(n), weights(n,  SUM_UNITY){};

    int root(int a) {
        if (uni[a] < 0) return a;
        else {
            int r = root(uni[a]);
            weights[a] += weights[uni[a]];
            return (uni[a] = r);
        }
    }

    bool unite(int a, int b, T w) {
        w += weight(a); w -= weight(b);
        a = root(a);
        b = root(b);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b), w = -w;
        uni[a] += uni[b];
        uni[b] = a;
        weights[b] = w;
        return true;
    }

    int size(int a){
        return -uni[root(a)];
    }

    T weight(T a){
        root(a);
        return weights[a];
    }
    int diff(int x, int y){
        return weight(y) - weight(x);
    }
};