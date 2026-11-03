template<class Coord = long long, class Length = long long>
struct PerimeterOfUnionOfRectangles {
    struct Rectangle {
        Coord l, d, r, u;
    };

    struct Event {
        Coord x;
        int yl, yr, delta;

        bool operator<(const Event &other) const {
            if (x != other.x) return x < other.x;
            return delta > other.delta;
        }
    };

    struct SegmentTree {
        struct Node {
            int cover = 0, parts = 0;
            Length length = 0, total = 0;
            bool left = false, right = false;
        };

        int sz = 1;
        vector<Node> nodes;

        explicit SegmentTree(const vector<Coord> &ys) {
            int n = int(ys.size()) - 1;
            while (sz < n) sz <<= 1;
            nodes.resize(sz << 1);
            for (int i = 0; i < n; ++i) nodes[sz + i].total = Length(ys[i + 1]) - Length(ys[i]);
            for (int k = sz - 1; k > 0; --k) nodes[k].total = nodes[k << 1].total + nodes[k << 1 | 1].total;
        }

        void pull(int k) {
            auto &node = nodes[k];
            if (node.cover > 0) {
                node.length = node.total;
                node.parts = 1;
                node.left = node.right = true;
            } else if (k < sz) {
                const auto &a = nodes[k << 1], &b = nodes[k << 1 | 1];
                node.length = a.length + b.length;
                node.parts = a.parts + b.parts - (a.right && b.left);
                node.left = a.left;
                node.right = b.right;
            } else {
                node.length = 0;
                node.parts = 0;
                node.left = node.right = false;
            }
        }

        void apply(int k, int delta) {
            nodes[k].cover += delta;
            pull(k);
        }

        void update(int l, int r, int delta) {
            l += sz;
            r += sz;
            int left = l, right = r - 1;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) apply(l++, delta);
                if (r & 1) apply(--r, delta);
            }
            while (left >>= 1) pull(left);
            while (right >>= 1) pull(right);
        }
    };

    vector<Rectangle> rects;

    void add_rectangle(Coord l, Coord d, Coord r, Coord u) {
        if (l < r && d < u) rects.push_back({l, d, r, u});
    }

    Length solve() const {
        if (rects.empty()) return 0;
        vector<Coord> ys;
        ys.reserve(rects.size() * 2);
        for (const auto &rect : rects) {
            ys.push_back(rect.d);
            ys.push_back(rect.u);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        vector<Event> events;
        events.reserve(rects.size() * 2);
        for (const auto &rect : rects) {
            int d = lower_bound(ys.begin(), ys.end(), rect.d) - ys.begin();
            int u = lower_bound(ys.begin(), ys.end(), rect.u) - ys.begin();
            events.push_back({rect.l, d, u, 1});
            events.push_back({rect.r, d, u, -1});
        }
        sort(events.begin(), events.end());
        SegmentTree seg(ys);
        Length answer = 0;
        Coord previous_x = events.front().x;
        for (const auto &event : events) {
            answer += Length(2) * seg.nodes[1].parts * (Length(event.x) - Length(previous_x));
            Length before = seg.nodes[1].length;
            seg.update(event.yl, event.yr, event.delta);
            Length after = seg.nodes[1].length;
            answer += after < before ? before - after : after - before;
            previous_x = event.x;
        }
        return answer;
    }
};

/**
 * @brief 長方形和集合の周長
 */
