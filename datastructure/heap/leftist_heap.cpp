template<class T>
class LeftistHeap {
    struct Node {
        T value, lazy;
        int left, right, rank;
    };

    vector<Node> nodes;
    vector<int> roots, counts;
    int free_head = -1;

    int rank(int v) const { return v == -1 ? 0 : nodes[v].rank; }

    void apply(int v, const T &delta) {
        if (v == -1) return;
        nodes[v].value += delta;
        nodes[v].lazy += delta;
    }

    void push_lazy(int v) {
        apply(nodes[v].left, nodes[v].lazy);
        apply(nodes[v].right, nodes[v].lazy);
        nodes[v].lazy = T{};
    }

    int merge(int a, int b) {
        if (a == -1) return b;
        if (b == -1) return a;
        if (nodes[b].value < nodes[a].value) swap(a, b);
        push_lazy(a);
        nodes[a].right = merge(nodes[a].right, b);
        if (rank(nodes[a].left) < rank(nodes[a].right)) swap(nodes[a].left, nodes[a].right);
        nodes[a].rank = rank(nodes[a].right) + 1;
        return a;
    }

public:
    explicit LeftistHeap(int m) : roots(m, -1), counts(m, 0) {}

    bool empty(int i) const { return counts[i] == 0; }
    int size(int i) const { return counts[i]; }

    T top(int i) const {
        assert(!empty(i));
        return nodes[roots[i]].value;
    }

    void push(int i, const T &value) {
        int v;
        if (free_head == -1) {
            v = (int)nodes.size();
            nodes.push_back({value, T{}, -1, -1, 1});
        } else {
            v = free_head;
            free_head = nodes[v].left;
            nodes[v] = {value, T{}, -1, -1, 1};
        }
        roots[i] = merge(roots[i], v);
        ++counts[i];
    }

    void pop(int i) {
        assert(!empty(i));
        int v = roots[i];
        push_lazy(v);
        roots[i] = merge(nodes[v].left, nodes[v].right);
        nodes[v].left = free_head;
        free_head = v;
        --counts[i];
    }

    void meld(int i, int j) {
        if (i == j) return;
        roots[i] = merge(roots[i], roots[j]);
        counts[i] += counts[j];
        roots[j] = -1;
        counts[j] = 0;
    }

    void add_all(int i, const T &delta) { apply(roots[i], delta); }
};

/**
 * @brief 併合・一括加算付きヒープ(Leftist Heap)
 */
