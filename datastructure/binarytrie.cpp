template<class T, size_t X>
struct Binarytrie {
    struct Node {
        int cnt;
        int nxt[2];
        Node() : cnt(0), nxt{-1, -1} {}
    };

    vector<Node> nodes;

    Binarytrie() : nodes(1) {}

    explicit Binarytrie(const vector<T> &v) : Binarytrie() {
        reserve((int)v.size());
        for (const T &x : v) add(x);
    }

    void reserve(int n) {
        if (n <= 0) return;
        nodes.reserve(nodes.size() + (size_t)n * X);
    }

    int size() const {
        return nodes[0].cnt;
    }

    bool empty() const {
        return nodes[0].cnt == 0;
    }

    int count(const T &x) const {
        int p = 0;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            p = nodes[p].nxt[f];
            if (p == -1) return 0;
        }
        return nodes[p].cnt;
    }

    bool contains(const T &x) const {
        return count(x) > 0;
    }

    void add(const T &x, int k = 1) {
        assert(k >= 0);
        if (k == 0) return;
        int p = 0;
        nodes[p].cnt += k;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            int to = nodes[p].nxt[f];
            if (to == -1) {
                to = make_node();
                nodes[p].nxt[f] = to;
            }
            p = to;
            nodes[p].cnt += k;
        }
    }

    bool erase(const T &x, int k = 1) {
        assert(k >= 0);
        if (k == 0) return true;
        array<int, X + 1> path;
        int p = 0;
        path[0] = p;
        for (int i = int(X) - 1, d = 1; i >= 0; --i, ++d) {
            int f = (x >> i) & 1;
            p = nodes[p].nxt[f];
            if (p == -1) return false;
            path[d] = p;
        }
        if (nodes[p].cnt < k) return false;
        for (int v : path) nodes[v].cnt -= k;
        for (size_t d = X; d > 0; --d) {
            int v = path[d];
            if (nodes[v].cnt != 0) break;
            int f = (x >> (X - d)) & 1;
            nodes[path[d - 1]].nxt[f] = -1;
            nodes[v].nxt[0] = free_head;
            free_head = v;
        }
        return true;
    }

    T xor_min(const T &x) const {
        int p = 0;
        T ret = 0;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            int to = nodes[p].nxt[f];
            if (to == -1 || nodes[to].cnt == 0) {
                f ^= 1;
                ret |= T(1) << i;
            }
            p = nodes[p].nxt[f];
        }
        return ret;
    }

    T min_element(T x = 0) const {
        return xor_min(x) ^ x;
    }

    T max_element(T x = 0) const {
        T y = x ^ bit_mask();
        return xor_min(y) ^ y;
    }

private:
    int free_head = -1;

    int make_node() {
        if (free_head == -1) {
            nodes.emplace_back();
            return (int)nodes.size() - 1;
        }
        int v = free_head;
        free_head = nodes[v].nxt[0];
        nodes[v] = Node();
        return v;
    }

    static constexpr T bit_mask() {
        if constexpr (X == sizeof(T) * 8) return T(-1);
        else return (T(1) << X) - 1;
    }
};

/**
 * @brief Binary Trie
 */
