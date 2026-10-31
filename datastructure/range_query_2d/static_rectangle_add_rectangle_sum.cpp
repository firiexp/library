#include "../binaryindexedtree.cpp"

template<class T>
class StaticRectangleAddRectangleSum {
    struct Point {
        int x, y;
        T w;
    };
    struct Event {
        int x, y, id, sign;
    };
    struct Coefficients {
        T w, xw, yw, xyw;
        Coefficients(int value = 0) : w(value), xw(value), yw(value), xyw(value) {}
        Coefficients& operator+=(const Coefficients& other) {
            w += other.w;
            xw += other.xw;
            yw += other.yw;
            xyw += other.xyw;
            return *this;
        }
    };

    vector<Point> points;
    vector<Event> events;
    int query_count = 0;

public:
    void add_rectangle(int l, int d, int r, int u, T w) {
        if (l == r || d == u) return;
        points.push_back({l, d, w});
        points.push_back({l, u, -w});
        points.push_back({r, d, -w});
        points.push_back({r, u, w});
    }

    void add_query(int l, int d, int r, int u) {
        int id = query_count++;
        if (l == r || d == u) return;
        events.push_back({r, u, id, 1});
        events.push_back({l, u, id, -1});
        events.push_back({r, d, id, -1});
        events.push_back({l, d, id, 1});
    }

    vector<T> solve() const {
        vector<T> ans(query_count, T(0));
        if (points.empty() || events.empty()) return ans;
        auto ps = points;
        auto es = events;
        vector<int> ys;
        ys.reserve(ps.size());
        for (const auto& p : ps) ys.push_back(p.y);
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        auto get_y = [&](int y) {
            return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin());
        };
        sort(ps.begin(), ps.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
        sort(es.begin(), es.end(), [](const Event& a, const Event& b) { return a.x < b.x; });
        BIT<Coefficients> bit((int)ys.size());
        int i = 0;
        for (const auto& e : es) {
            while (i < (int)ps.size() && ps[i].x < e.x) {
                const auto& p = ps[i++];
                Coefficients c;
                c.w = p.w;
                c.xw = T(p.x) * p.w;
                c.yw = T(p.y) * p.w;
                c.xyw = T(p.x) * c.yw;
                bit.add(get_y(p.y), c);
            }
            auto c = bit.sum(get_y(e.y));
            T x = T(e.x), y = T(e.y);
            T value = x * y * c.w - y * c.xw - x * c.yw + c.xyw;
            if (e.sign == 1) ans[e.id] += value;
            else ans[e.id] -= value;
        }
        return ans;
    }
};

/**
 * @brief 静的な長方形加算・長方形和
 */
