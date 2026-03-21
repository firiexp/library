template<class T, class SumT = long long>
class TopKLargestTreap {
private:
    struct Node {
        T key;
        int cnt;        // この key の個数
        int sz;         // 部分木全体の個数
        uint32_t pri;   // Treap priority
        SumT sum;       // 部分木全体の和
        Node* l;
        Node* r;
        Node(const T& key_, uint32_t pri_) : key(key_), cnt(1), sz(1), pri(pri_), sum((SumT)key_), l(nullptr), r(nullptr) {}
    };

    Node* root_ = nullptr;
    int K_ = 0;
    uint32_t rng_ = 2463534242u; // xorshift 用の非 0 seed

    static int size(Node* t) {
        return t ? t->sz : 0;
    }

    static SumT subtree_sum(Node* t) {
        return t ? t->sum : SumT(0);
    }

    static void pull(Node* t) {
        if (!t) return;
        t->sz = t->cnt + size(t->l) + size(t->r);
        t->sum = subtree_sum(t->l) + subtree_sum(t->r) + (SumT)t->key * t->cnt;
    }

    uint32_t next_rand() {
        uint32_t x = rng_;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        rng_ = x;
        return x;
    }

    Node* make_node(const T& x) {
        return new Node(x, next_rand());
    }

    static void rotate_left(Node*& t) {
        Node* r = t->r;
        t->r = r->l;
        r->l = t;
        pull(t);
        pull(r);
        t = r;
    }

    static void rotate_right(Node*& t) {
        Node* l = t->l;
        t->l = l->r;
        l->r = t;
        pull(t);
        pull(l);
        t = l;
    }

    void insert(Node*& t, const T& x) {
        if (!t) {
            t = make_node(x);
            return;
        }

        if (x == t->key) {
            ++t->cnt;
            pull(t);
            return;
        }

        if (x < t->key) {
            insert(t->l, x);
            if (t->l->pri > t->pri) rotate_right(t);
        } else {
            insert(t->r, x);
            if (t->r->pri > t->pri) rotate_left(t);
        }
        pull(t);
    }

    bool erase_one(Node*& t, const T& x) {
        if (!t) return false;
        bool ok = false;
        if (x < t->key) {
            ok = erase_one(t->l, x);
        } else if (x > t->key) {
            ok = erase_one(t->r, x);
        } else {
            ok = true;
            if (t->cnt > 1) {
                --t->cnt;
                pull(t);
                return true;
            }
            if (!t->l || !t->r) {
                Node* old = t;
                t = (t->l ? t->l : t->r);
                delete old;
                return true;
            }
            if (t->l->pri > t->r->pri) {
                rotate_right(t);
                ok = erase_one(t->r, x);
            } else {
                rotate_left(t);
                ok = erase_one(t->l, x); 
            }
        }

        if (t) pull(t);
        return ok;
    }

    static void destroy(Node* t) {
        if (!t) return;
        destroy(t->l);
        destroy(t->r);
        delete t;
    }

public:
    explicit TopKLargestTreap(int K = 0, uint32_t seed = 2463534242u)
        : root_(nullptr), K_(K), rng_(seed) {
        assert(K >= 0);
        if (rng_ == 0) rng_ = 2463534242u;
    }

    TopKLargestTreap(const TopKLargestTreap&) = delete;
    TopKLargestTreap& operator=(const TopKLargestTreap&) = delete;

    ~TopKLargestTreap() {
        destroy(root_);
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
        return root_ == nullptr;
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
        Node* t = root_;
        while (t) {
            if (x == t->key) return t->cnt;
            t = (x < t->key ? t->l : t->r);
        }
        return 0;
    }

    bool contains(const T& x) const {
        return count(x) > 0;
    }

    T kth_largest(int kth) const {
        assert(1 <= kth && kth <= size());

        Node* t = root_;
        while (t) {
            int rsz = size(t->r);
            if (kth <= rsz) {
                t = t->r;
            } else if (kth <= rsz + t->cnt) {
                return t->key;
            } else {
                kth -= rsz + t->cnt;
                t = t->l;
            }
        }

        assert(false);
        return T();
    }

    bool has_kth() const {
        return 1 <= K_ && K_ <= size();
    }

    T kth_largest() const {
        assert(has_kth());
        return kth_largest(K_);
    }
    
    SumT sum_largest_k(int k) const {
        if (k <= 0 || !root_) return SumT(0);
        if (k >= size()) return total_sum();
        SumT res = 0;
        Node* t = root_;
        while (t && k > 0) {
            int rsz = size(t->r);
            if (k <= rsz) {
                t = t->r;
                continue;
            }
            res += subtree_sum(t->r);
            k -= rsz;
            int take = std::min(k, t->cnt);
            res += (SumT)t->key * take;
            k -= take;
            if (k == 0) break;
            t = t->l;
        }
        return res;
    }

    SumT sum_topk() const {
        return sum_largest_k(K_);
    }
};

/**
 * @brief 上位K管理Treap
 */
