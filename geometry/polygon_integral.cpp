#ifndef FIRIEXP_LIBRARY_GEOMETRY_POLYGON_INTEGRAL_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_POLYGON_INTEGRAL_CPP

#include "int_point.cpp"

class PolygonIntegral {
public:
    struct RationalPoint {
        __int128 x_num, y_num, den;
    };

    class Result {
        friend class PolygonIntegral;

        __int128 area2_ = 0, x_sum = 0, y_sum = 0;

        Result(__int128 area2, __int128 x, __int128 y) : area2_(area2), x_sum(x), y_sum(y) {}

    public:
        Result() = default;

        __int128 area2() const { return area2_; }

        optional<RationalPoint> centroid() const {
            if (area2_ == 0) return nullopt;
            __int128 x = x_sum, y = y_sum, d = area2_;
            if (d < 0) {
                x = -x;
                y = -y;
                d = -d;
            }
            return RationalPoint{x, y, 3 * d};
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
        a.area2_ += b.area2_;
        a.x_sum += b.x_sum;
        a.y_sum += b.y_sum;
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
        Result result{prefix[v].area2_ - prefix[u].area2_,
                      prefix[v].x_sum - prefix[u].x_sum,
                      prefix[v].y_sum - prefix[u].y_sum};
        if (u > v) result = add(result, prefix.back());
        return add(result, edge(points[v], points[u]));
    }
};

#endif

/**
 * @brief 多角形の区間面積と重心
 */
