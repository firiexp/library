class UndoableUnionFind {
    stack<pair<int, int>> hist;
    int forest_size;
    int snap;

public:
    vector<int> uni;

    explicit UndoableUnionFind(int sz) : forest_size(sz), snap(0), uni(sz, -1) {}

    int root(int a) {
        if (uni[a] < 0) return a;
        return root(uni[a]);
    }

    bool same(int a, int b) {
        return root(a) == root(b);
    }

    bool unite(int a, int b) {
        a = root(a);
        b = root(b);
        hist.emplace(a, uni[a]);
        hist.emplace(b, uni[b]);
        if (a == b) return false;
        if (uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }

    int size() { return forest_size; }
    int size(int i) { return -uni[root(i)]; }

    int get_state() const {
        return int(hist.size() >> 1);
    }

    void undo() {
        int a = hist.top().first;
        int ua = hist.top().second;
        hist.pop();
        int b = hist.top().first;
        int ub = hist.top().second;
        hist.pop();
        if (a != b) forest_size++;
        uni[a] = ua;
        uni[b] = ub;
    }

    void snapshot() {
        snap = get_state();
    }

    void rollback(int state = -1) {
        if (state == -1) state = snap;
        while (get_state() > state) undo();
    }
};

/**
 * @brief Undoable Union Find
 * @docs _md/undoableunionfind.md
 */
