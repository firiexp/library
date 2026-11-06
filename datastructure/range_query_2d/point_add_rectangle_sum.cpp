using namespace std;

#include "fenwick_tree_2d.cpp"

template<class T>
struct PointAddRectangleSum {
    struct Operation {
        int type;
        int x, y, z, u;
        T w;
    };

    vector<Operation> ops;

    void add_point(int x, int y, T w) {
        ops.push_back({0, x, y, 0, 0, w});
    }

    void add_query(int l, int d, int r, int u) {
        ops.push_back({1, l, d, r, u, T(0)});
    }

    vector<T> solve() const {
        FenwickTree2D<T> bit;
        for (const auto &op : ops) {
            if (op.type == 0) bit.add_point(op.x, op.y);
        }
        bit.build();

        vector<T> ans;
        for (const auto &op : ops) {
            if (op.type == 0) {
                bit.add(op.x, op.y, op.w);
            } else {
                ans.push_back(bit.sum(op.x, op.y, op.z, op.u));
            }
        }
        return ans;
    }
};

/**
 * @brief 点加算長方形和(Point Add Rectangle Sum)
 */
