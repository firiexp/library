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
        ord_x.reserve(ord_x.size() + ops.size());
        for (auto &&op : ops) {
            if (op.type == 1) ord_x.push_back(op.l);
        }
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
        vector<int> cnt(m + 1);
        auto count_point = [&](int xi) {
            for (int i = xi; i <= m; i += i & -i) ++cnt[i];
        };
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            if (ops[idx].type == 1) continue;
            count_point(x_index_lower[idx]);
            count_point(x_index_lower[idx]);
            count_point(x_index_upper[idx]);
            count_point(x_index_upper[idx]);
        }
        vector<vector<int>> ys(m + 1);
        for (int i = 1; i <= m; ++i) ys[i].reserve(cnt[i]);
        auto reserve_point = [&](int xi, int y) {
            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);
        };
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            auto &&op = ops[idx];
            if (op.type == 0) {
                reserve_point(x_index_lower[idx], op.d);
                reserve_point(x_index_lower[idx], op.u);
                reserve_point(x_index_upper[idx], op.d);
                reserve_point(x_index_upper[idx], op.u);
            }
        }
        for (int i = 1; i <= m; ++i) {
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
        }

        vector<int> offset(m + 2, 0);
        for (int i = 1; i <= m; ++i) offset[i + 1] = offset[i] + (int)ys[i].size();
        vector<T> bit(offset[m + 1], 0);
        auto path_len_add = [&](int xi) {
            int len = 0;
            for (int i = xi; i <= m; i += i & -i) ++len;
            return len;
        };
        auto path_len_sum = [&](int xi) {
            int len = 0;
            for (int i = xi; i > 0; i -= i & -i) ++len;
            return len;
        };
        vector<RectInfo> rect_info(ops.size());
        vector<int> query_start(ops.size(), -1);
        int total_add_visits = 0, total_sum_visits = 0;
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            if (ops[idx].type == 0) {
                total_add_visits += path_len_add(x_index_lower[idx]) * 2;
                total_add_visits += path_len_add(x_index_upper[idx]) * 2;
            } else {
                total_sum_visits += path_len_sum(x_index_upper[idx]);
            }
        }
        vector<int> add_yi(total_add_visits);
        vector<int> sum_yi(total_sum_visits);
        int add_ptr = 0, sum_ptr = 0;
        auto encode_add = [&](int xi, int y) {
            int start = add_ptr;
            for (int i = xi; i <= m; i += i & -i) {
                add_yi[add_ptr++] = (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin()) + 1;
            }
            return start;
        };
        auto encode_sum = [&](int xi, int y) {
            int start = sum_ptr;
            for (int i = xi; i > 0; i -= i & -i) {
                sum_yi[sum_ptr++] = (int)(upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());
            }
            return start;
        };
        for (int idx = 0; idx < (int)ops.size(); ++idx) {
            auto &&op = ops[idx];
            if (op.type == 0) {
                rect_info[idx].start[0] = encode_add(x_index_lower[idx], op.d);
                rect_info[idx].start[1] = encode_add(x_index_lower[idx], op.u);
                rect_info[idx].start[2] = encode_add(x_index_upper[idx], op.d);
                rect_info[idx].start[3] = encode_add(x_index_upper[idx], op.u);
            } else {
                query_start[idx] = encode_sum(x_index_upper[idx], op.d);
            }
        }

        auto add_point = [&](int xi, int start, T w) {
            int ptr = start;
            for (int i = xi; i <= m; i += i & -i) {
                int yi = add_yi[ptr++];
                int sz = (int)ys[i].size();
                int base = offset[i];
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
