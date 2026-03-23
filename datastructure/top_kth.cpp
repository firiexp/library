template<class T, class SumT = long long, bool Largest = true>
class TopKTreap {
private:
    struct Node {
        T key;
        int cnt;
        int sz;
        uint32_t pri;
        SumT sum;
        int l;
        int r;

        Node(const T& key_, uint32_t pri_)
            : key(key_), cnt(1), sz(1), pri(pri_), sum((SumT)key_), l(-1), r(-1) {}
    };

    int root_ = -1;
    int K_ = 0;
    uint32_t rng_ = 2463534242u;
    vector<Node> nodes_;
    vector<int> free_nodes_;

    static bool goes_left(const T& x, const T& key) {
        if constexpr (Largest) return x < key;
        else return x > key;
    }

    int size(int t) const {
        return t == -1 ? 0 : nodes_[t].sz;
    }

    SumT subtree_sum(int t) const {
        return t == -1 ? SumT(0) : nodes_[t].sum;
    }

    void pull(int t) {
        if (t == -1) return;
        Node& node = nodes_[t];
        node.sz = node.cnt + size(node.l) + size(node.r);
        node.sum = subtree_sum(node.l) + subtree_sum(node.r) + (SumT)node.key * node.cnt;
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

        if (x == nodes_[t].key) {
            ++nodes_[t].cnt;
            pull(t);
            return;
        }

        if (goes_left(x, nodes_[t].key)) {
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
        if (goes_left(x, nodes_[t].key)) {
            int child = nodes_[t].l;
            ok = erase_one(child, x);
            nodes_[t].l = child;
        } else if (goes_left(nodes_[t].key, x)) {
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
                t = (nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r);
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
    explicit TopKTreap(int K = 0, uint32_t seed = 2463534242u)
        : root_(-1), K_(K), rng_(seed) {
        assert(K >= 0);
        if (rng_ == 0) rng_ = 2463534242u;
    }

    TopKTreap(const TopKTreap&) = delete;
    TopKTreap& operator=(const TopKTreap&) = delete;

    void reserve(int capacity) {
        assert(capacity >= 0);
        nodes_.reserve(capacity);
        free_nodes_.reserve(capacity);
    }

    int k() const {
        return K_;
    }

    void set_k(int new_k) {
        assert(new_k >= 0);
        K_ = new_k;
    }

    int size() const {
        return size(root_);
    }

    bool empty() const {
        return root_ == -1;
    }

    SumT total_sum() const {
        return subtree_sum(root_);
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
            if (x == node.key) return node.cnt;
            t = goes_left(x, node.key) ? node.l : node.r;
        }
        return 0;
    }

    bool contains(const T& x) const {
        return count(x) > 0;
    }

    T kth(int kth) const {
        assert(1 <= kth && kth <= size());

        int t = root_;
        while (t != -1) {
            const Node& node = nodes_[t];
            int preferred_sz = size(node.r);
            if (kth <= preferred_sz) {
                t = node.r;
            } else if (kth <= preferred_sz + node.cnt) {
                return node.key;
            } else {
                kth -= preferred_sz + node.cnt;
                t = node.l;
            }
        }

        assert(false);
        return T();
    }

    bool has_kth() const {
        return 1 <= K_ && K_ <= size();
    }

    T kth() const {
        assert(has_kth());
        return kth(K_);
    }

    SumT sum_k(int k) const {
        if (k <= 0 || root_ == -1) return SumT(0);
        if (k >= size()) return total_sum();
        SumT res = 0;
        int t = root_;
        while (t != -1 && k > 0) {
            const Node& node = nodes_[t];
            int preferred = node.r;
            int other = node.l;
            int preferred_sz = size(preferred);
            if (k <= preferred_sz) {
                t = preferred;
                continue;
            }
            res += subtree_sum(preferred);
            k -= preferred_sz;
            int take = std::min(k, node.cnt);
            res += (SumT)node.key * take;
            k -= take;
            if (k == 0) break;
            t = other;
        }
        return res;
    }

    SumT sum_topk() const {
        return sum_k(K_);
    }
};

/**
 * @brief 上位K個を管理するTreap
 */
