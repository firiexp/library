template<class T, size_t X>
struct Binarytrie {
    struct Node {
        int cnt;
        Node *nxt[2];
        Node() : cnt(0), nxt{nullptr, nullptr} {}
    };

    Node *root;

    Binarytrie() : root(new Node) {}

    int size() const {
        return root->cnt;
    }

    bool empty() const {
        return root->cnt == 0;
    }

    int count(const T &x) const {
        Node *p = root;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            if (!p->nxt[f]) return 0;
            p = p->nxt[f];
        }
        return p->cnt;
    }

    bool contains(const T &x) const {
        return count(x) > 0;
    }

    void add(const T &x, int k = 1) {
        Node *p = root;
        p->cnt += k;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            if (!p->nxt[f]) p->nxt[f] = new Node;
            p = p->nxt[f];
            p->cnt += k;
        }
    }

    bool erase(const T &x, int k = 1) {
        if (count(x) < k) return false;
        Node *p = root;
        p->cnt -= k;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            p = p->nxt[f];
            p->cnt -= k;
        }
        return true;
    }

    T xor_min(const T &x) const {
        Node *p = root;
        T ret = 0;
        for (int i = int(X) - 1; i >= 0; --i) {
            int f = (x >> i) & 1;
            if (!p->nxt[f] || p->nxt[f]->cnt == 0) {
                f ^= 1;
                ret |= T(1) << i;
            }
            p = p->nxt[f];
        }
        return ret;
    }

    T min_element(T x = 0) const {
        return xor_min(x) ^ x;
    }

    T max_element(T x = 0) const {
        return xor_min(~x) ^ x;
    }
};

/**
 * @brief Binary Trie
 */
