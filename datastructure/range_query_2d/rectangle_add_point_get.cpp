using namespace std;

template<class T>
struct RectangleAddPointGet {
    struct Operation {
        int type;
        int l, d, r, u;
        T w;
    };

    vector<Operation> ops;
    vector<int> xs;

    void add_rectangle(int l, int d, int r, int u, T w) {
        ops.push_back({0, l, d, r, u, w});
        xs.push_back(l);
        xs.push_back(r);
    }

    void add_query(int x, int y) {
        ops.push_back({1, x, y, 0, 0, 0});
    }

    vector<T> solve() const {
        struct RectInfo {
            int start[4];
        };
        vector<int> ord_x = xs;
        sort(ord_x.begin(), ord_x.end());
        ord_x.erase(unique(ord_x.begin(), ord_x.end()), ord_x.end());

        int m = (int)ord_x.size();
        vector<int> x_index_lower(ops.size());
        vector<int> x_index_upper(ops.size());
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            x_index_lower[idx] = (int)(lower_bound(ord_x.begin(), ord_x.end(), ops[idx].l) - ord_x.begin()) + 1;
            if (ops[idx].type == 1) {
                x_index_upper[idx] = (int)(upper_bound(ord_x.begin(), ord_x.end(), ops[idx].l) - ord_x.begin());
            } else {
                x_index_upper[idx] = (int)(lower_bound(ord_x.begin(), ord_x.end(), ops[idx].r) - ord_x.begin()) + 1;
            }
        }
        vector<vector<int>> ys(m + 1);
        vector<RectInfo> rect_info(ops.size());
        vector<int> add_yi;
        {
            struct Endpoint {
                int y, xi, start;
            };
            vector<Endpoint> endpoints;
            endpoints.reserve(2 * xs.size());
            vector<int> counts(m + 1);
            int visits = 0;
            for (int idx = 0; idx < (int)ops.size(); ++idx) {
                const auto& op = ops[idx];
                if (op.type != 0) continue;
                auto register_side = [&](int xi, int side) {
                    int length = 0;
                    for (int i = xi; i <= m; i += i & -i) ++length;
                    counts[xi] += 2;
                    rect_info[idx].start[side] = visits;
                    rect_info[idx].start[side + 1] = visits + length;
                    endpoints.push_back({op.d, xi, visits});
                    endpoints.push_back({op.u, xi, visits + length});
                    visits += 2 * length;
                };
                register_side(x_index_lower[idx], 0);
                register_side(x_index_upper[idx], 2);
            }
            for (int i = 1; i <= m; ++i) {
                ys[i].reserve(counts[i]);
                int parent = i + (i & -i);
                if (parent <= m) counts[parent] += counts[i];
            }
            sort(endpoints.begin(), endpoints.end(), [](const Endpoint& a, const Endpoint& b) {
                return a.y < b.y;
            });
            add_yi.resize(visits);
            for (auto [y, xi, start] : endpoints) {
                for (int i = xi; i <= m; i += i & -i) {
                    auto& row = ys[i];
                    if (row.empty() || row.back() != y) row.push_back(y);
                    add_yi[start++] = (int)row.size();
                }
            }
        }

        vector<int> offset(m + 2, 0);
        for (int i = 1; i <= m; ++i) offset[i + 1] = offset[i] + (int)ys[i].size();
        auto path_len_sum = [&](int xi) {
            int len = 0;
            for (int i = xi; i > 0; i -= i & -i) ++len;
            return len;
        };
        vector<int> query_start(ops.size(), -1);
        int total_sum_visits = 0;
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            if (ops[idx].type == 1) total_sum_visits += path_len_sum(x_index_upper[idx]);
        }
        vector<int> sum_yi(total_sum_visits);
        int sum_ptr = 0;
        auto encode_sum = [&](int xi, int y) {
            int start = sum_ptr;
            for (int i = xi; i > 0; i -= i & -i) {
                sum_yi[sum_ptr++] = (int)(upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());
            }
            return start;
        };
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            if (ops[idx].type == 1) query_start[idx] = encode_sum(x_index_upper[idx], ops[idx].d);
        }

        ys.clear();
        vector<T> bit(offset[m + 1], 0);
        auto add_point = [&](int xi, int start, T w) {
            int ptr = start;
            for (int i = xi; i <= m; i += i & -i) {
                int yi = add_yi[ptr++];
                int base = offset[i];
                int sz = offset[i + 1] - base;
                for (; yi <= sz; yi += yi & -yi) bit[base + yi - 1] += w;
            }
        };
        auto prefix_sum = [&](int xi, int start) {
            T ret = 0;
            int ptr = start;
            for (int i = xi; i > 0; i -= i & -i) {
                int yi = sum_yi[ptr++];
                int base = offset[i];
                for (; yi > 0; yi -= yi & -yi) ret += bit[base + yi - 1];
            }
            return ret;
        };

        vector<T> ans;
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            auto &&op = ops[idx];
            if (op.type == 0) {
                add_point(x_index_lower[idx], rect_info[idx].start[0], op.w);
                add_point(x_index_lower[idx], rect_info[idx].start[1], -op.w);
                add_point(x_index_upper[idx], rect_info[idx].start[2], -op.w);
                add_point(x_index_upper[idx], rect_info[idx].start[3], op.w);
            } else {
                ans.push_back(prefix_sum(x_index_upper[idx], query_start[idx]));
            }
        }
        return ans;
    }
};

/**
 * @brief 長方形加算点取得(Rectangle Add Point Get)
 */
