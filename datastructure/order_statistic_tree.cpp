template<class T, class Compare = less<T>>
class OrderStatisticTree {
private:
    struct Node {
        T key;
        int cnt;
        int sz;
        uint32_t pri;
        int l;
        int r;

        Node(const T& key_, uint32_t pri_)
            : key(key_), cnt(1), sz(1), pri(pri_), l(-1), r(-1) {}
    };

    int root_ = -1;
    uint32_t rng_ = 2463534242u;
    vector<Node> nodes_;
    vector<int> free_nodes_;
    Compare comp_;

    int size(int t) const {
        return t == -1 ? 0 : nodes_[t].sz;
    }

    bool equal_key(const T& a, const T& b) const {
        return !comp_(a, b) && !comp_(b, a);
    }

    void pull(int t) {
        if (t == -1) return;
        Node& node = nodes_[t];
        node.sz = node.cnt + size(node.l) + size(node.r);
    }

    uint32_t next_rand() {
        uint32_t x = rng_;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        rng_ = x;
        return x;
    }

    int make_node(const T& x) {
        uint32_t pri = next_rand();
        if (!free_nodes_.empty()) {
            int idx = free_nodes_.back();
            free_nodes_.pop_back();
            nodes_[idx] = Node(x, pri);
            return idx;
        }
        nodes_.emplace_back(x, pri);
        return (int)nodes_.size() - 1;
    }

    void recycle_node(int t) {
        if (t != -1) free_nodes_.push_back(t);
    }

    void rotate_left(int& t) {
        int r = nodes_[t].r;
        nodes_[t].r = nodes_[r].l;
        nodes_[r].l = t;
        pull(t);
        pull(r);
        t = r;
    }

    void rotate_right(int& t) {
        int l = nodes_[t].l;
        nodes_[t].l = nodes_[l].r;
        nodes_[l].r = t;
        pull(t);
        pull(l);
        t = l;
    }

    void insert(int& t, const T& x) {
        if (t == -1) {
            t = make_node(x);
            return;
        }

        if (equal_key(x, nodes_[t].key)) {
            ++nodes_[t].cnt;
            pull(t);
            return;
        }

        if (comp_(x, nodes_[t].key)) {
            int child = nodes_[t].l;
            insert(child, x);
            nodes_[t].l = child;
            if (nodes_[nodes_[t].l].pri > nodes_[t].pri) rotate_right(t);
        } else {
            int child = nodes_[t].r;
            insert(child, x);
            nodes_[t].r = child;
            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);
        }
        pull(t);
    }

    bool erase_one(int& t, const T& x) {
        if (t == -1) return false;

        bool ok = false;
        if (comp_(x, nodes_[t].key)) {
            int child = nodes_[t].l;
            ok = erase_one(child, x);
            nodes_[t].l = child;
        } else if (comp_(nodes_[t].key, x)) {
            int child = nodes_[t].r;
            ok = erase_one(child, x);
            nodes_[t].r = child;
        } else {
            ok = true;
            if (nodes_[t].cnt > 1) {
                --nodes_[t].cnt;
                pull(t);
                return true;
            }
            if (nodes_[t].l == -1 || nodes_[t].r == -1) {
                int old = t;
                t = nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r;
                recycle_node(old);
                return true;
            }
            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {
                rotate_right(t);
                int child = nodes_[t].r;
                ok = erase_one(child, x);
                nodes_[t].r = child;
            } else {
                rotate_left(t);
                int child = nodes_[t].l;
                ok = erase_one(child, x);
                nodes_[t].l = child;
            }
        }

        if (t != -1) pull(t);
        return ok;
    }

public:
    explicit OrderStatisticTree(uint32_t seed = 2463534242u, Compare comp = Compare())
        : root_(-1), rng_(seed), comp_(comp) {
        if (rng_ == 0) rng_ = 2463534242u;
    }

    void reserve(int capacity) {
        assert(capacity >= 0);
        nodes_.reserve(capacity);
        free_nodes_.reserve(capacity);
    }

    int size() const {
        return size(root_);
    }

    bool empty() const {
        return root_ == -1;
    }

    void insert(const T& x) {
        insert(root_, x);
    }

    bool erase_one(const T& x) {
        return erase_one(root_, x);
    }

    int count(const T& x) const {
        int t = root_;
        while (t != -1) {
            const Node& node = nodes_[t];
            if (equal_key(x, node.key)) return node.cnt;
            t = comp_(x, node.key) ? node.l : node.r;
        }
        return 0;
    }

    bool contains(const T& x) const {
        return count(x) > 0;
    }

    T find_by_order(int k) const {
        assert(0 <= k && k < size());

        int t = root_;
        while (true) {
            const Node& node = nodes_[t];
            int left_sz = size(node.l);
            if (k < left_sz) {
                t = node.l;
            } else if (k < left_sz + node.cnt) {
                return node.key;
            } else {
                k -= left_sz + node.cnt;
                t = node.r;
            }
        }
    }

    int order_of_key(const T& x) const {
        int res = 0;
        int t = root_;
        while (t != -1) {
            const Node& node = nodes_[t];
            if (comp_(node.key, x)) {
                res += size(node.l) + node.cnt;
                t = node.r;
            } else {
                t = node.l;
            }
        }
        return res;
    }
};

/**
 * @brief 順序統計木(Order Statistic Tree)
 */
