template<class T, bool get_max = false>
struct LiChaoTree {
    struct Line {
        T a, b;
        Line(T a = 0, T b = inf()) : a(a), b(b) {}
        T get(T x) const { return a * x + b; }
    };

    vector<T> xs;
    vector<Line> seg;
    int n;

    explicit LiChaoTree(vector<T> xs) : xs(xs) {
        sort(this->xs.begin(), this->xs.end());
        this->xs.erase(unique(this->xs.begin(), this->xs.end()), this->xs.end());
        n = (int)this->xs.size();
        seg.assign(max(1, 4 * n), Line());
    }

    void add_line(T a, T b) {
        if (n == 0) return;
        if (get_max) a = -a, b = -b;
        add_line_node(1, 0, n, Line(a, b));
    }

    void add_segment(T a, T b, T l, T r) {
        if (n == 0 || l >= r) return;
        if (get_max) a = -a, b = -b;
        int L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        int R = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        if (L >= R) return;
        add_segment_node(1, 0, n, L, R, Line(a, b));
    }

    T query(T x) const {
        if (n == 0) return get_max ? -inf() : inf();
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        if (i == n || xs[i] != x) return get_max ? -inf() : inf();
        T ret = query_node(1, 0, n, i, x);
        return get_max ? -ret : ret;
    }

private:
    static constexpr T inf() {
        return numeric_limits<T>::max() / 4;
    }

    void add_line_node(int k, int l, int r, Line x) {
        int m = (l + r) / 2;
        bool lef = x.get(xs[l]) < seg[k].get(xs[l]);
        bool mid = x.get(xs[m]) < seg[k].get(xs[m]);
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

    T query_node(int k, int l, int r, int i, T x) const {
        T ret = seg[k].get(x);
        if (r - l == 1) return ret;
        int m = (l + r) / 2;
        if (i < m) return min(ret, query_node(k * 2, l, m, i, x));
        return min(ret, query_node(k * 2 + 1, m, r, i, x));
    }
};

template<class T, bool get_max = false>
struct OnlineLiChaoTree {
    struct Line {
        T a, b;
        Line(T a = 0, T b = inf()) : a(a), b(b) {}
        T get(T x) const { return a * x + b; }
    };

    struct Node {
        Line line;
        int l, r;
        explicit Node(const Line &line) : line(line), l(-1), r(-1) {}
    };

    T low, high;
    int root;
    deque<Node> nodes;

    explicit OnlineLiChaoTree(T low, T high) : low(low), high(high), root(-1) {}

    void add_line(T a, T b) {
        if (get_max) a = -a, b = -b;
        add_line(root, low, high, Line(a, b));
    }

    void add_segment(T a, T b, T l, T r) {
        if (l >= r) return;
        if (get_max) a = -a, b = -b;
        add_segment(root, low, high, l, r, Line(a, b));
    }

    T query(T x) const {
        T ret = query(root, low, high, x);
        return get_max ? -ret : ret;
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
        T m = l + (r - l) / 2;
        bool lef = x.get(l) < node.line.get(l);
        bool mid = x.get(m) < node.line.get(m);
        if (mid) swap(node.line, x);
        if (r - l == 1) return;
        if (lef != mid) add_line(node.l, l, m, x);
        else add_line(node.r, m, r, x);
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

    T query(int t, T l, T r, T x) const {
        T ret = inf();
        while (t != -1) {
            const Node &node = nodes[t];
            ret = min(ret, node.line.get(x));
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
