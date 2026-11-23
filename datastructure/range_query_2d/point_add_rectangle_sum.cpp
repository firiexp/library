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
        auto first_query = find_if(ops.begin(), ops.end(), [](const Operation &op) {
            return op.type == 1;
        });
        if (first_query == ops.end()) return {};

        FenwickTree2D<T> bit;
        for (const auto &op : ops) {
            if (op.type == 0) bit.add_point(op.x, op.y);
        }
        vector<T> initial_weights;
        initial_weights.reserve(first_query - ops.begin());
        for (auto it = ops.begin(); it != first_query; ++it) initial_weights.push_back(it->w);
        bit.build(initial_weights);

        vector<T> ans;
        for (auto it = first_query; it != ops.end(); ++it) {
            const auto &op = *it;
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
