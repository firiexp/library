template<class T, bool get_max = false>
struct LiChaoTree {
    struct Line {
        T a, b;
        int id;
        Line(T a = 0, T b = inf(), int id = -1) : a(a), b(b), id(id) {}
        T get(T x) const { return a * x + b; }
        bool better(const Line &other, T x) const {
            return make_pair(get(x), id) < make_pair(other.get(x), other.id);
        }
    };

    vector<T> xs;
    vector<Line> seg;
    int n;
    int next_id = 0;

    explicit LiChaoTree(vector<T> xs) : xs(xs) {
        sort(this->xs.begin(), this->xs.end());
        this->xs.erase(unique(this->xs.begin(), this->xs.end()), this->xs.end());
        n = (int)this->xs.size();
        seg.assign(max(1, 4 * n), Line());
    }

    int add_line(T a, T b) {
        int id = next_id++;
        if (n == 0) return id;
        if (get_max) a = -a, b = -b;
        add_line_node(1, 0, n, Line(a, b, id));
        return id;
    }

    int add_segment(T a, T b, T l, T r) {
        int id = next_id++;
        if (n == 0 || l >= r) return id;
        if (get_max) a = -a, b = -b;
        int L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        int R = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        if (L >= R) return id;
        add_segment_node(1, 0, n, L, R, Line(a, b, id));
        return id;
    }

    T query(T x) const {
        auto ret = query_with_id(x);
        return ret ? ret->first : (get_max ? -inf() : inf());
    }

    optional<pair<T, int>> query_with_id(T x) const {
        if (n == 0) return nullopt;
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        if (i == n || xs[i] != x) return nullopt;
        auto ret = query_node(1, 0, n, i, x);
        if (ret && get_max) ret->first = -ret->first;
        return ret;
    }

private:
    static constexpr T inf() {
        return numeric_limits<T>::max() / 4;
    }

    void add_line_node(int k, int l, int r, Line x) {
        if (seg[k].id == -1) {
            seg[k] = x;
            return;
        }
        int m = (l + r) / 2;
        bool lef = x.better(seg[k], xs[l]);
        bool mid = x.better(seg[k], xs[m]);
        if (mid) swap(seg[k], x);
        if (r - l == 1) return;
        if (lef != mid) add_line_node(k * 2, l, m, x);
        else add_line_node(k * 2 + 1, m, r, x);
    }

    void add_segment_node(int k, int l, int r, int a, int b, Line x) {
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            add_line_node(k, l, r, x);
            return;
        }
        int m = (l + r) / 2;
        add_segment_node(k * 2, l, m, a, b, x);
        add_segment_node(k * 2 + 1, m, r, a, b, x);
    }

    optional<pair<T, int>> query_node(int k, int l, int r, int i, T x) const {
        optional<pair<T, int>> ret;
        if (seg[k].id != -1) ret = make_pair(seg[k].get(x), seg[k].id);
        if (r - l == 1) return ret;
        int m = (l + r) / 2;
        auto child = i < m ? query_node(k * 2, l, m, i, x)
                          : query_node(k * 2 + 1, m, r, i, x);
        if (child && (!ret || *child < *ret)) ret = child;
        return ret;
    }
};

template<class T, bool get_max = false>
struct OnlineLiChaoTree {
    struct Line {
        T a, b;
        int id;
        Line(T a = 0, T b = inf(), int id = -1) : a(a), b(b), id(id) {}
        T get(T x) const { return a * x + b; }
        bool better(const Line &other, T x) const {
            return make_pair(get(x), id) < make_pair(other.get(x), other.id);
        }
    };

    struct Node {
        Line line;
        int l, r;
        explicit Node(const Line &line) : line(line), l(-1), r(-1) {}
    };

    T low, high;
    int root;
    int next_id = 0;
    deque<Node> nodes;

    explicit OnlineLiChaoTree(T low, T high) : low(low), high(high), root(-1) {}

    int add_line(T a, T b) {
        int id = next_id++;
        if (get_max) a = -a, b = -b;
        add_line(root, low, high, Line(a, b, id));
        return id;
    }

    int add_segment(T a, T b, T l, T r) {
        int id = next_id++;
        if (l >= r) return id;
        if (get_max) a = -a, b = -b;
        add_segment(root, low, high, l, r, Line(a, b, id));
        return id;
    }

    T query(T x) const {
        auto ret = query_with_id(x);
        return ret ? ret->first : (get_max ? -inf() : inf());
    }

    optional<pair<T, int>> query_with_id(T x) const {
        auto ret = query(root, low, high, x);
        if (ret && get_max) ret->first = -ret->first;
        return ret;
    }

private:
    static constexpr T inf() {
        return numeric_limits<T>::max() / 4;
    }

    int new_node(const Line &line) {
        nodes.emplace_back(line);
        return (int)nodes.size() - 1;
    }

    void add_line(int &t, T l, T r, Line x) {
        if (t == -1) {
            t = new_node(x);
            return;
        }
        Node &node = nodes[t];
        if (node.line.id == -1) {
            node.line = x;
            return;
        }
        T m = l + (r - l) / 2;
        bool lef = x.better(node.line, l);
        bool mid = x.better(node.line, m);
        if (mid) swap(node.line, x);
        if (r - l == 1) return;
        if (lef != mid) add_line(node.l, l, m, x);
        else if (x.better(node.line, r - 1)) add_line(node.r, m, r, x);
    }

    void add_segment(int &t, T l, T r, T a, T b, Line x) {
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            add_line(t, l, r, x);
            return;
        }
        if (t == -1) t = new_node(Line());
        Node &node = nodes[t];
        T m = l + (r - l) / 2;
        if (a < m) add_segment(node.l, l, m, a, b, x);
        if (m < b) add_segment(node.r, m, r, a, b, x);
    }

    optional<pair<T, int>> query(int t, T l, T r, T x) const {
        optional<pair<T, int>> ret;
        while (t != -1) {
            const Node &node = nodes[t];
            if (node.line.id != -1) {
                auto value = make_pair(node.line.get(x), node.line.id);
                if (!ret || value < *ret) ret = value;
            }
            if (r - l == 1) break;
            T m = l + (r - l) / 2;
            if (x < m) {
                t = node.l;
                r = m;
            } else {
                t = node.r;
                l = m;
            }
        }
        return ret;
    }
};

/**
 * @brief Li Chao Tree
 */
