using namespace std;

template<class Coord = long long, class Area = long long>
struct AreaOfUnionOfRectangles {
    struct Rectangle {
        Coord l, d, r, u;
    };

    struct Event {
        Coord x;
        int yl, yr;
        int delta;

        bool operator<(const Event &other) const {
            return x < other.x;
        }
    };

    struct SegmentTree {
        int n, sz;
        vector<int> cnt;
        vector<Area> len;
        vector<Area> total;

        explicit SegmentTree(const vector<Coord> &ys) : n((int)ys.size() - 1), sz(1) {
            while (sz < n) sz <<= 1;
            cnt.assign(sz << 1, 0);
            len.assign(sz << 1, 0);
            total.assign(sz << 1, 0);
            for (int i = 0; i < n; ++i) {
                total[sz + i] = Area(ys[i + 1]) - Area(ys[i]);
            }
            for (int k = sz - 1; k > 0; --k) total[k] = total[k << 1] + total[k << 1 | 1];
        }

        void apply(int k, int x) {
            cnt[k] += x;
            pull(k);
        }

        void pull(int k) {
            if (cnt[k] > 0) {
                len[k] = total[k];
            } else if (k < sz) {
                len[k] = len[k << 1] + len[k << 1 | 1];
            } else {
                len[k] = 0;
            }
        }

        void update(int a, int b, int x) {
            if (a >= b) return;
            a += sz;
            b += sz;
            int left = a;
            int right = b - 1;
            for (; a < b; a >>= 1, b >>= 1) {
                if (a & 1) apply(a++, x);
                if (b & 1) apply(--b, x);
            }
            while (left >>= 1) pull(left);
            while (right >>= 1) pull(right);
        }

        Area covered_length() const {
            return len[1];
        }
    };

    vector<Rectangle> rects;
    vector<Coord> ys;

    void add_rectangle(Coord l, Coord d, Coord r, Coord u) {
        if (l >= r || d >= u) return;
        rects.push_back({l, d, r, u});
        ys.push_back(d);
        ys.push_back(u);
    }

    Area solve() const {
        if (rects.empty()) return 0;

        vector<Coord> ord_y = ys;
        sort(ord_y.begin(), ord_y.end());
        ord_y.erase(unique(ord_y.begin(), ord_y.end()), ord_y.end());
        if ((int)ord_y.size() <= 1) return 0;

        vector<Event> events;
        events.reserve(rects.size() * 2);
        for (auto &&rect : rects) {
            int d = (int)(lower_bound(ord_y.begin(), ord_y.end(), rect.d) - ord_y.begin());
            int u = (int)(lower_bound(ord_y.begin(), ord_y.end(), rect.u) - ord_y.begin());
            events.push_back({rect.l, d, u, 1});
            events.push_back({rect.r, d, u, -1});
        }
        sort(events.begin(), events.end());

        SegmentTree seg(ord_y);
        Area ans = 0;
        Coord prev_x = events[0].x;
        int i = 0;
        while (i < (int)events.size()) {
            Coord x = events[i].x;
            ans += seg.covered_length() * Area(x - prev_x);
            while (i < (int)events.size() && events[i].x == x) {
                seg.update(events[i].yl, events[i].yr, events[i].delta);
                ++i;
            }
            prev_x = x;
        }
        return ans;
    }
};

/**
 * @brief 長方形和集合面積(Area of Union of Rectangles)
 */
