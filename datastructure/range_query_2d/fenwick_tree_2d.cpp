#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_FENWICK_TREE_2D_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_FENWICK_TREE_2D_CPP

using namespace std;

#include "../segmenttree/binaryindexedtree.cpp"

template<class T>
struct FenwickTree2D {
    vector<pair<int, int>> points;
    vector<int> xs;
    vector<vector<int>> ys;
    vector<BIT<T>> bit;
    bool built = false;

    int add_point(int x, int y) {
        assert(!built);
        points.push_back({x, y});
        xs.push_back(x);
        return (int)points.size() - 1;
    }

private:
    vector<int> update_point, update_x, update_offset, update_index;
    bool updates_prepared = false;

    struct WeightedPoint {
        int first, second;
        T weight;
    };

    template<bool Weighted, class Point>
    void build_impl(vector<Point> ord) {
        assert(!built);
        built = true;

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        if constexpr (Weighted) {
            sort(ord.begin(), ord.end(), [](const auto &a, const auto &b) {
                return pair<int, int>(a.first, a.second) < pair<int, int>(b.first, b.second);
            });
            int size = 0;
            for (const auto &point : ord) {
                if (size && ord[size - 1].first == point.first && ord[size - 1].second == point.second) {
                    ord[size - 1].weight += point.weight;
                } else {
                    ord[size++] = point;
                }
            }
            ord.resize(size);
        } else {
            sort(ord.begin(), ord.end());
            ord.erase(unique(ord.begin(), ord.end()), ord.end());
        }

        int m = (int)xs.size();
        ys.assign(m + 1, {});
        vector<vector<T>> values;
        if constexpr (Weighted) values.resize(m + 1);
        {
            vector<int> counts(m + 1);
            int xi = 1;
            for (auto &point : ord) {
                while (xs[xi - 1] < point.first) ++xi;
                point.first = xi;
                for (int i = xi; i <= m; i += i & -i) ++counts[i];
            }
            for (int i = 1; i <= m; ++i) {
                ys[i].reserve(counts[i]);
                if constexpr (Weighted) values[i].reserve(counts[i]);
            }
        }
        sort(ord.begin(), ord.end(), [](const auto &a, const auto &b) {
            return a.second < b.second;
        });
        for (const auto &point : ord) {
            for (int i = point.first; i <= m; i += i & -i) {
                if constexpr (Weighted) {
                    if (ys[i].empty() || ys[i].back() != point.second) {
                        ys[i].push_back(point.second);
                        values[i].push_back(point.weight);
                    } else {
                        values[i].back() += point.weight;
                    }
                } else {
                    ys[i].push_back(point.second);
                }
            }
        }
        bit.clear();
        bit.reserve(m + 1);
        bit.emplace_back(0);
        for (int i = 1; i <= m; ++i) {
            if constexpr (Weighted) {
                bit.emplace_back(values[i]);
            } else {
                ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
                bit.emplace_back((int)ys[i].size());
            }
        }
    }

public:
    void prepare_updates() {
        assert(built && !updates_prepared);
        int n = (int)points.size();
        int m = (int)xs.size();
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        sort(order.begin(), order.end(), [&](int a, int b) { return points[a] < points[b]; });
        vector<int> unique_points;
        unique_points.reserve(n);
        update_point.resize(n);
        for (int id : order) {
            if (unique_points.empty() || points[unique_points.back()] != points[id]) {
                unique_points.push_back(id);
            }
            update_point[id] = (int)unique_points.size() - 1;
        }
        int p = (int)unique_points.size();
        update_x.resize(p);
        update_offset.assign(p + 1, 0);
        int xi = 1;
        for (int k = 0; k < p; ++k) {
            while (xs[xi - 1] < points[unique_points[k]].first) ++xi;
            update_x[k] = xi;
            update_offset[k + 1] = update_offset[k];
            for (int i = xi; i <= m; i += i & -i) ++update_offset[k + 1];
        }
        update_index.resize(update_offset.back());
        order.resize(p);
        for (int k = 0; k < p; ++k) order[k] = k;
        sort(order.begin(), order.end(), [&](int a, int b) {
            return points[unique_points[a]].second < points[unique_points[b]].second;
        });
        vector<int> row_index(m + 1, -1);
        for (int k : order) {
            int y = points[unique_points[k]].second;
            int offset = update_offset[k];
            for (int i = update_x[k]; i <= m; i += i & -i) {
                if (row_index[i] < 0 || ys[i][row_index[i]] != y) ++row_index[i];
                assert(row_index[i] < (int)ys[i].size() && ys[i][row_index[i]] == y);
                update_index[offset++] = row_index[i];
            }
        }
        updates_prepared = true;
    }

    void add(int id, T w) {
        assert(updates_prepared && 0 <= id && id < (int)points.size());
        int k = update_point[id];
        int row = update_x[k];
        for (int j = update_offset[k]; j < update_offset[k + 1]; ++j, row += row & -row) {
            bit[row].add(update_index[j], w);
        }
    }

    void build() {
        build_impl<false>(points);
    }

    void build(const vector<T> &initial_weights) {
        assert(!built && initial_weights.size() <= points.size());
        int levels = 1;
        for (size_t n = points.size(); n > 1; n >>= 1) ++levels;
        if (initial_weights.size() * levels <= points.size() * 4) {
            build();
            for (int i = 0; i < (int)initial_weights.size(); ++i) {
                add(points[i].first, points[i].second, initial_weights[i]);
            }
            return;
        }
        vector<WeightedPoint> ord;
        ord.reserve(points.size());
        for (int i = 0; i < (int)points.size(); ++i) {
            ord.push_back({points[i].first, points[i].second,
                i < (int)initial_weights.size() ? initial_weights[i] : T(0)});
        }
        build_impl<true>(move(ord));
    }

    void add(int x, int y, T w) {
        assert(built);
        int m = (int)xs.size();
        int xi = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        assert(xi < m && xs[xi] == x);
        ++xi;
        for (int i = xi; i <= m; i += i & -i) {
            int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());
            assert(yi < (int)ys[i].size() && ys[i][yi] == y);
            bit[i].add(yi, w);
        }
    }

    T sum(int x, int y) {
        assert(built);
        T ret = 0;
        int xi = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        for (int i = xi; i > 0; i -= i & -i) {
            int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());
            ret += bit[i].sum(yi);
        }
        return ret;
    }

    T sum(int l, int d, int r, int u) {
        assert(built && l <= r && d <= u);
        if (l == r || d == u) return T(0);
        int li = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        int ri = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        auto row_sum = [&](int i) {
            int di = lower_bound(ys[i].begin(), ys[i].end(), d) - ys[i].begin();
            int ui = lower_bound(ys[i].begin(), ys[i].end(), u) - ys[i].begin();
            return bit[i].sum(di, ui);
        };
        T positive = 0, negative = 0;
        for (; ri > li; ri -= ri & -ri) positive += row_sum(ri);
        for (; li > ri; li -= li & -li) negative += row_sum(li);
        return positive - negative;
    }
};

/**
 * @brief 2次元Fenwick Tree(2D BIT)
 */

#endif
