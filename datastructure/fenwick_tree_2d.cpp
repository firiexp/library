#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_FENWICK_TREE_2D_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_FENWICK_TREE_2D_CPP

using namespace std;

#include "binaryindexedtree.cpp"

template<class T>
struct FenwickTree2D {
    vector<pair<int, int>> points;
    vector<int> xs;
    vector<vector<int>> ys;
    vector<BIT<T>> bit;
    bool built = false;

    void add_point(int x, int y) {
        assert(!built);
        points.push_back({x, y});
        xs.push_back(x);
    }

    void build() {
        assert(!built);
        built = true;

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        vector<pair<int, int>> ord = points;
        sort(ord.begin(), ord.end());
        ord.erase(unique(ord.begin(), ord.end()), ord.end());

        int m = (int)xs.size();
        ys.assign(m + 1, {});
        {
            vector<int> counts(m + 1);
            int xi = 1;
            for (auto &[x, y] : ord) {
                while (xs[xi - 1] < x) ++xi;
                x = xi;
                for (int i = xi; i <= m; i += i & -i) ++counts[i];
            }
            for (int i = 1; i <= m; ++i) ys[i].reserve(counts[i]);
        }
        sort(ord.begin(), ord.end(), [](const auto &a, const auto &b) {
            return a.second < b.second;
        });
        for (auto [xi, y] : ord) {
            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);
        }
        bit.clear();
        bit.reserve(m + 1);
        bit.emplace_back(0);
        for (int i = 1; i <= m; ++i) {
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
            bit.emplace_back((int)ys[i].size());
        }
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
