#ifndef FIRIEXP_LIBRARY_TREE_EULER_TOUR_TREE_CPP
#define FIRIEXP_LIBRARY_TREE_EULER_TOUR_TREE_CPP

struct EulerTourTree {
    struct SubtreeInfo {
        int size;
        long long sum;
    };

    struct Node {
        int left = -1, right = -1, parent = -1, count = 0;
        long long value = 0, sum = 0, lazy = 0;
    };

    int n;
    vector<Node> nodes;
    vector<int> free_nodes, push_stack;
    map<pair<int, int>, pair<int, int>> edges;

    explicit EulerTourTree(const vector<long long> &values) : n(values.size()) {
        nodes.reserve(3 * (size_t)n);
        nodes.resize(n);
        push_stack.reserve(64);
        for (int v = 0; v < n; ++v) {
            nodes[v].count = 1;
            nodes[v].value = nodes[v].sum = values[v];
        }
    }

    bool connected(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (u == v) return true;
        splay(u);
        splay(v);
        return nodes[u].parent != -1;
    }

    bool link(int u, int v) {
        if (connected(u, v)) return false;
        int a = reroot(u), b = reroot(v);
        int forward = new_edge_node(), backward = new_edge_node();
        attach(forward, a, b);
        attach(backward, forward, -1);
        if (u < v) edges[{u, v}] = {forward, backward};
        else edges[{v, u}] = {backward, forward};
        return true;
    }

    bool cut(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        auto it = edges.find({min(u, v), max(u, v)});
        if (it == edges.end()) return false;
        auto [a, middle, b] = isolate(v, u);
        take_right(b);
        free_nodes.push_back(a);
        free_nodes.push_back(b);
        edges.erase(it);
        return true;
    }

    void subtree_add(int v, int p, long long delta) {
        auto [a, middle, b] = isolate(v, p);
        apply(middle, delta);
        restore(a, middle, b);
    }

    SubtreeInfo subtree_info(int v, int p) {
        auto [a, middle, b] = isolate(v, p);
        SubtreeInfo result{nodes[middle].count, nodes[middle].sum};
        restore(a, middle, b);
        return result;
    }

    long long subtree_sum(int v, int p) {
        return subtree_info(v, p).sum;
    }

    void vertex_add(int v, long long delta) {
        assert(0 <= v && v < n);
        splay(v);
        nodes[v].value += delta;
        pull(v);
    }

    long long get(int v) {
        assert(0 <= v && v < n);
        splay(v);
        return nodes[v].value;
    }

private:
    int new_edge_node() {
        if (free_nodes.empty()) {
            nodes.emplace_back();
            return nodes.size() - 1;
        }
        int v = free_nodes.back();
        free_nodes.pop_back();
        nodes[v] = Node{};
        return v;
    }

    void apply(int v, long long delta) {
        if (v == -1 || nodes[v].count == 0) return;
        if (v < n) nodes[v].value += delta;
        nodes[v].sum += delta * nodes[v].count;
        nodes[v].lazy += delta;
    }

    void push(int v) {
        if (nodes[v].lazy == 0) return;
        apply(nodes[v].left, nodes[v].lazy);
        apply(nodes[v].right, nodes[v].lazy);
        nodes[v].lazy = 0;
    }

    void pull(int v) {
        nodes[v].count = v < n;
        nodes[v].sum = nodes[v].value;
        for (int child : {nodes[v].left, nodes[v].right}) {
            if (child == -1) continue;
            nodes[v].count += nodes[child].count;
            nodes[v].sum += nodes[child].sum;
        }
    }

    void rotate(int v) {
        int p = nodes[v].parent, g = nodes[p].parent;
        if (nodes[p].left == v) {
            int child = nodes[v].right;
            nodes[v].right = p;
            nodes[p].left = child;
            if (child != -1) nodes[child].parent = p;
        } else {
            int child = nodes[v].left;
            nodes[v].left = p;
            nodes[p].right = child;
            if (child != -1) nodes[child].parent = p;
        }
        nodes[p].parent = v;
        nodes[v].parent = g;
        if (g != -1) {
            if (nodes[g].left == p) nodes[g].left = v;
            else nodes[g].right = v;
        }
        pull(p);
        pull(v);
    }

    void splay(int v) {
        push_stack.clear();
        for (int x = v; x != -1; x = nodes[x].parent) push_stack.push_back(x);
        for (int i = (int)push_stack.size() - 1; i >= 0; --i) push(push_stack[i]);
        while (nodes[v].parent != -1) {
            int p = nodes[v].parent, g = nodes[p].parent;
            if (g != -1) {
                bool zigzig = (nodes[p].left == v) == (nodes[g].left == p);
                rotate(zigzig ? p : v);
            }
            rotate(v);
        }
    }

    int take_left(int v) {
        int child = nodes[v].left;
        nodes[v].left = -1;
        if (child != -1) nodes[child].parent = -1;
        pull(v);
        return child;
    }

    int take_right(int v) {
        int child = nodes[v].right;
        nodes[v].right = -1;
        if (child != -1) nodes[child].parent = -1;
        pull(v);
        return child;
    }

    void attach(int v, int left, int right) {
        nodes[v].left = left;
        nodes[v].right = right;
        if (left != -1) nodes[left].parent = v;
        if (right != -1) nodes[right].parent = v;
        pull(v);
    }

    void restore(int a, int middle, int b) {
        if (a == -1) return;
        attach(a, -1, middle);
        attach(b, a, nodes[b].right);
    }

    int merge(int a, int b) {
        if (a == -1 || b == -1) return a == -1 ? b : a;
        int v = a;
        push(v);
        while (nodes[v].right != -1) {
            v = nodes[v].right;
            push(v);
        }
        splay(v);
        nodes[v].right = b;
        nodes[b].parent = v;
        pull(v);
        return v;
    }

    int reroot(int v) {
        splay(v);
        int before = take_left(v);
        return merge(v, before);
    }

    tuple<int, int, int> isolate(int v, int p) {
        assert(0 <= v && v < n && -1 <= p && p < n);
        if (p == -1) {
            splay(v);
            return {-1, v, -1};
        }
        auto it = edges.find({min(v, p), max(v, p)});
        assert(it != edges.end());
        auto [a, b] = it->second;
        if (p > v) swap(a, b);
        reroot(a);
        splay(b);
        take_left(b);
        splay(a);
        int middle = take_right(a);
        return {a, middle, b};
    }
};

#endif

/**
 * @brief 動的な木の部分木加算・部分木和（Euler Tour Tree）
 */
