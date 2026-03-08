#include <algorithm>
#include <vector>
using namespace std;

#include "binaryindexedtree.cpp"

template<class T>
struct PointAddRectangleSum {
    struct Operation {
        int type;
        int x, y, z;
        T w;
    };

    vector<Operation> ops;
    vector<int> xs;

    void add_point(int x, int y, T w) {
        ops.push_back({0, x, y, 0, w});
        xs.push_back(x);
    }

    void add_query(int l, int d, int r, int u) {
        ops.push_back({1, l, d, r, u});
    }

    vector<T> solve() const {
        vector<int> ord_x = xs;
        sort(ord_x.begin(), ord_x.end());
        ord_x.erase(unique(ord_x.begin(), ord_x.end()), ord_x.end());

        int m = (int)ord_x.size();
        vector<vector<int>> ys(m + 1);
        for (auto op : ops) {
            if (op.type != 0) continue;
            int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), op.x) - ord_x.begin()) + 1;
            for (int x = xi; x <= m; x += x & -x) ys[x].push_back(op.y);
        }
        for (int i = 1; i <= m; ++i) {
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
        }

        vector<BIT<T>> bit;
        bit.reserve(m + 1);
        bit.emplace_back(0);
        for (int i = 1; i <= m; ++i) bit.emplace_back((int)ys[i].size());

        auto add = [&](int x, int y, T w) {
            int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), x) - ord_x.begin()) + 1;
            for (int i = xi; i <= m; i += i & -i) {
                int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());
                bit[i].add(yi, w);
            }
        };
        auto sum = [&](int x, int y) {
            T ret = 0;
            int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), x) - ord_x.begin());
            for (int i = xi; i > 0; i -= i & -i) {
                int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());
                ret += bit[i].sum(yi);
            }
            return ret;
        };

        vector<T> ans;
        for (auto op : ops) {
            if (op.type == 0) {
                add(op.x, op.y, (T)op.w);
            } else {
                ans.push_back(sum(op.z, op.w) - sum(op.z, op.y) - sum(op.x, op.w) + sum(op.x, op.y));
            }
        }
        return ans;
    }
};

/**
 * @brief 点加算長方形和(Point Add Rectangle Sum)
 */
