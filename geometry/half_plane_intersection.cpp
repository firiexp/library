#include "../geometry/geometry.cpp"

namespace internal_half_plane_intersection {

struct HalfPlane {
    Point p, pq;
    real angle;

    HalfPlane() = default;

    explicit HalfPlane(const Line &l)
        : p(l.a), pq(l.b - l.a), angle(atan2(pq.y, pq.x)) {}

    bool operator<(const HalfPlane &other) const {
        if (fabs(angle - other.angle) > EPS) return angle < other.angle;
        return cross(pq, other.p - p) < 0;
    }

    bool outside(Point r) const {
        return cross(pq, r - p) < -EPS;
    }
};

Point intersection(const HalfPlane &s, const HalfPlane &t) {
    real a = cross(t.p - s.p, t.pq) / cross(s.pq, t.pq);
    return s.p + s.pq * a;
}

bool same_point(Point a, Point b) {
    return abs(a - b) < EPS;
}

}  // namespace internal_half_plane_intersection

Polygon half_plane_intersection(vector<Line> ls) {
    using namespace internal_half_plane_intersection;

    static constexpr real INF = 1e9;
    vector<HalfPlane> hs;
    hs.reserve(ls.size() + 4);
    for (const Line &l : ls) hs.emplace_back(l);

    Polygon box = {
        Point(-INF, -INF),
        Point(INF, -INF),
        Point(INF, INF),
        Point(-INF, INF),
    };
    for (int i = 0; i < 4; ++i) {
        hs.emplace_back(Line(box[i], box[(i + 1) % 4]));
    }

    sort(hs.begin(), hs.end());

    deque<HalfPlane> deq;
    for (const HalfPlane &h : hs) {
        while (deq.size() > 1 &&
               h.outside(intersection(deq.back(), deq[deq.size() - 2]))) {
            deq.pop_back();
        }
        while (deq.size() > 1 &&
               h.outside(intersection(deq[0], deq[1]))) {
            deq.pop_front();
        }
        if (!deq.empty() && fabs(cross(deq.back().pq, h.pq)) < EPS) {
            if (dot(deq.back().pq, h.pq) < 0) return {};
            if (h.outside(deq.back().p)) deq.pop_back();
            else continue;
        }
        deq.push_back(h);
    }

    while (deq.size() > 2 &&
           deq.front().outside(intersection(deq.back(), deq[deq.size() - 2]))) {
        deq.pop_back();
    }
    while (deq.size() > 2 &&
           deq.back().outside(intersection(deq[0], deq[1]))) {
        deq.pop_front();
    }
    if (deq.size() < 3) return {};

    Polygon res;
    res.reserve(deq.size());
    for (int i = 0; i < (int)deq.size(); ++i) {
        Point p = intersection(deq[i], deq[(i + 1) % deq.size()]);
        if (res.empty() || !same_point(res.back(), p)) res.push_back(p);
    }
    if (res.size() >= 2 && same_point(res.front(), res.back())) res.pop_back();
    if (res.size() < 3 || fabs(area(res)) < EPS) return {};
    return res;
}

/**
 * @brief 半平面共通部分(Half-Plane Intersection)
 */
