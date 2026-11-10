#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_UNIONFIND_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_UNIONFIND_CPP

class UnionFind {
    int n;
    vector<int> uni;
    int forest_size;
public:
    struct MergeResult {
        int keep;
        int absorbed;
        explicit operator bool() const { return absorbed != -1; }
    };

    explicit UnionFind(int n) : n(n), uni(n, -1), forest_size(n) {};

    int root(int a){
        if (uni[a] < 0) return a;
        else return (uni[a] = root(uni[a]));
    }

    MergeResult unite(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return {a, -1};
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return {a, b};
    }
    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }
    bool same(int a, int b) { return root(a) == root(b); }
};

#endif

/**
 * @brief UnionFind(素集合データ構造)
 */
