#include <algorithm>
#include <vector>
using namespace std;

#include "binaryindexedtree.cpp"

template<class T>
struct StaticRectangleSum {
    struct Point {
        int x, y;
        T w;
    };

    struct Event {
        int x, d, u, id, sign;

        bool operator<(const Event& other) const {
            return x < other.x;
        }
    };

    vector<Point> points;
    vector<Event> events;
    vector<int> ys;

    void add_point(int x, int y, T w) {
        points.push_back({x, y, w});
        ys.push_back(y);
    }

    void add_query(int l, int d, int r, int u) {
        int id = (int)events.size() / 2;
        events.push_back({r, d, u, id, 1});
        events.push_back({l, d, u, id, -1});
        ys.push_back(d);
        ys.push_back(u);
    }

    vector<T> solve() {
        vector<int> ord_y = ys;
        sort(ord_y.begin(), ord_y.end());
        ord_y.erase(unique(ord_y.begin(), ord_y.end()), ord_y.end());

        auto get_y = [&](int y) {
            return (int)(lower_bound(ord_y.begin(), ord_y.end(), y) - ord_y.begin());
        };

        vector<Point> ps = points;
        for (auto& p : ps) p.y = get_y(p.y);
        for (auto& e : events) {
            e.d = get_y(e.d);
            e.u = get_y(e.u);
        }

        sort(ps.begin(), ps.end(), [](const Point& a, const Point& b) {
            return a.x < b.x;
        });
        sort(events.begin(), events.end());

        int q = (int)events.size() / 2;
        vector<T> ans(q, 0);
        BIT<T> bit((int)ord_y.size());
        int i = 0;
        for (auto e : events) {
            while (i < (int)ps.size() && ps[i].x < e.x) {
                bit.add(ps[i].y, ps[i].w);
                ++i;
            }
            ans[e.id] += (bit.sum(e.u) - bit.sum(e.d)) * e.sign;
        }
        return ans;
    }
};

/**
 * @brief 静的長方形和(Static Rectangle Sum)
 * @docs _md/static_rectangle_sum.md
 */
