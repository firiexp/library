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
        int p = 0;
        nodes[p].cnt += k;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            int to = nodes[p].nxt[f];
            if (to == -1) {
                to = (int)nodes.size();
                nodes[p].nxt[f] = to;
                nodes.emplace_back();
            }
            p = to;
            nodes[p].cnt += k;
        }
    }

    bool erase(const T &x, int k = 1) {
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
    static constexpr T bit_mask() {
        if constexpr (X == sizeof(T) * 8) return T(-1);
        else return (T(1) << X) - 1;
    }
};

/**
 * @brief Binary Trie
 */
