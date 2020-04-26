class UndoableUnionFind {
    stack<pair<int, int>> hist;
    int forest_size;
public:
    vector<int> uni;
    explicit UndoableUnionFind(int sz) : uni(sz, -1), forest_size(sz) {}

    int root(int a){
        if(uni[a] < 0) return a;
        return root(uni[a]);
    }

    bool unite(int a, int b){
        a = root(a), b = root(b);
        hist.emplace(a, uni[a]);
        hist.emplace(b, uni[b]);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }

    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }

    void undo(){
        uni[hist.top().first] = hist.top().second;
        hist.pop();
        uni[hist.top().first] = hist.top().second;
        hist.pop();
    }

    void snapshot(){ while(!hist.empty()) hist.pop(); }
    void rollback(){ while(!hist.empty()) undo(); }
};