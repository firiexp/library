struct QuickFind {
    int n;
    vector<int> roots;
    vector<vector<int>> v;
    explicit QuickFind(int n) : n(n) {
        v.resize(n);
        for (int i = 0; i < n; ++i) v[i].emplace_back(i);
        roots.resize(n);
        iota(roots.begin(),roots.end(), 0);
    }
 
    int root(int a){ return roots[a]; }
    size_t size(int a){ return v[a].size(); }
    bool unite(int a, int b){
        if(same(a, b)) return false;
        a = roots[a], b = roots[b];
        if(size(a) < size(b)) swap(a, b);
        for (auto &&i : v[b]) {
            v[a].emplace_back(i);
            roots[i] = a;
        }
        v[b].clear();
        v[b].shrink_to_fit();
        return true;
    }
    bool same(int a, int b){ return roots[a] == roots[b]; }
    const vector<int>& components(int x){ return v[roots[x]];}
};