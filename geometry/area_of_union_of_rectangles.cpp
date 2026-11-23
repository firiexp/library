using namespace std;

template<class Coord = long long, class Area = long long>
struct AreaOfUnionOfRectangles {
    struct Rectangle {
        Coord l, d, r, u;
    };

    struct Event {
        Coord x;
        int from, to;

        bool operator<(const Event &other) const {
            return x < other.x;
        }
    };

    struct SegmentTree {
        vector<Coord> ys;
        int sz = 1;
        vector<int> cover;
        vector<Area> length;

        explicit SegmentTree(vector<Coord> coordinates) : ys(std::move(coordinates)) {
            while (sz < (int)ys.size() - 1) sz <<= 1;
            cover.resize(2 * sz);
            length.assign(2 * sz, Area(0));
        }

        Area child_length(int k) const {
            return k < sz ? length[2 * k] + length[2 * k + 1] : Area(0);
        }

        bool apply(int k, int width, int delta) {
            cover[k] += delta;
            if (cover[k] == 0) {
                length[k] = child_length(k);
            } else if (cover[k] == 1 && delta > 0) {
                int start = k * width - sz;
                length[k] = Area(ys[start + width]) - Area(ys[start]);
            } else {
                return false;
            }
            return true;
        }

        bool pull(int k) {
            if (cover[k]) return false;
            length[k] = child_length(k);
            return true;
        }

        void update(int l, int r, int delta) {
            l += sz;
            r += sz;
            bool pull_left = false, pull_right = false;
            for (int width = 1; l < r; l >>= 1, r >>= 1, width <<= 1) {
                if (pull_left) pull_left = pull(l - 1);
                if (pull_right) pull_right = pull(r);
                if (l & 1) pull_left |= apply(l++, width, delta);
                if (r & 1) pull_right |= apply(--r, width, delta);
            }
            int left = pull_left ? l - 1 : 0;
            int right = pull_right ? r : 0;
            while (left != right) {
                if (left) left = pull(left) ? left / 2 : 0;
                if (right) right = pull(right) ? right / 2 : 0;
            }
            while (left && pull(left)) left /= 2;
        }

        Area covered_length() const {
            return length[1];
        }
    };

    vector<Rectangle> rects;

    void add_rectangle(Coord l, Coord d, Coord r, Coord u) {
        if (l >= r || d >= u) return;
        rects.push_back({l, d, r, u});
    }

private:
    vector<Event> make_events(vector<Coord> &ys) const {
        int n = (int)rects.size();
        vector<int> rank(2 * n);
        {
            struct Endpoint {
                Coord y;
                int id;
            };
            vector<Endpoint> endpoints;
            endpoints.reserve(2 * n);
            for (int i = 0; i < n; ++i) {
                endpoints.push_back({rects[i].d, 2 * i});
                endpoints.push_back({rects[i].u, 2 * i + 1});
            }
            sort(endpoints.begin(), endpoints.end(), [](const Endpoint &a, const Endpoint &b) {
                return a.y < b.y;
            });
            ys.reserve(2 * n);
            for (const auto &end : endpoints) {
                if (ys.empty() || ys.back() < end.y) ys.push_back(end.y);
                rank[end.id] = (int)ys.size() - 1;
            }
        }
        vector<Event> events;
        events.reserve(2 * n);
        for (int i = 0; i < n; ++i) {
            int d = rank[2 * i], u = rank[2 * i + 1];
            events.push_back({rects[i].l, d, u});
            events.push_back({rects[i].r, u, d});
        }
        return events;
    }

public:
    Area solve() const {
        if (rects.empty()) return 0;
        vector<Coord> ys;
        auto events = make_events(ys);
        sort(events.begin(), events.end());

        SegmentTree seg(std::move(ys));
        Area ans = 0;
        Coord prev_x = events[0].x;
        int i = 0;
        while (i < (int)events.size()) {
            Coord x = events[i].x;
            ans += seg.covered_length() * (Area(x) - Area(prev_x));
            while (i < (int)events.size() && events[i].x == x) {
                const auto &e = events[i++];
                if (e.from < e.to) seg.update(e.from, e.to, 1);
                else seg.update(e.to, e.from, -1);
            }
            prev_x = x;
        }
        return ans;
    }
};

/**
 * @brief 長方形和集合面積(Area of Union of Rectangles)
 */
