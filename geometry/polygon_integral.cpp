#ifndef FIRIEXP_LIBRARY_GEOMETRY_POLYGON_INTEGRAL_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_POLYGON_INTEGRAL_CPP

#include "int_point.cpp"

class PolygonIntegral {
public:
    struct Result {
        __int128 area2 = 0, moment_x = 0, moment_y = 0;

        long double area() const { return (long double)area2 / 2; }

        optional<pair<long double, long double>> centroid() const {
            if (area2 == 0) return nullopt;
            long double denominator = 3 * (long double)area2;
            return pair<long double, long double>{moment_x / denominator, moment_y / denominator};
        }
    };

private:
    vector<IntPoint> points;
    vector<Result> prefix;

    static Result edge(IntPoint a, IntPoint b) {
        __int128 d = (__int128)a.x * b.y - (__int128)a.y * b.x;
        return {d, ((__int128)a.x + b.x) * d, ((__int128)a.y + b.y) * d};
    }

    static Result add(Result a, const Result &b) {
        a.area2 += b.area2;
        a.moment_x += b.moment_x;
        a.moment_y += b.moment_y;
        return a;
    }

public:
    explicit PolygonIntegral(const vector<IntPoint> &input) : points(input), prefix(input.size() + 1) {
        int n = points.size();
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = add(prefix[i], edge(points[i], points[(i + 1) % n]));
    }

    Result whole() const { return prefix.back(); }

    Result query(int u, int v) const {
        int n = points.size();
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (u == v) return {};
        Result result{prefix[v].area2 - prefix[u].area2,
                      prefix[v].moment_x - prefix[u].moment_x,
                      prefix[v].moment_y - prefix[u].moment_y};
        if (u > v) result = add(result, prefix.back());
        return add(result, edge(points[v], points[u]));
    }
};

#endif

/**
 * @brief 多角形の区間面積と重心
 */
