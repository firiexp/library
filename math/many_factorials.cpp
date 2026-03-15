#include "../fps/sample_point_shift.cpp"
#include "../fps/multipoint_evaluation.cpp"
#include "../fps/taylor_shift.cpp"

vector<mint> many_factorials(const vector<long long> &ns) {
    struct EvalPoint {
        int x, query_id;
    };

    int q = ns.size();
    vector<mint> ans(q);
    if (q == 0) return ans;

    vector<pair<int, int>> order;
    order.reserve(q);
    for (int i = 0; i < q; ++i) {
        if (ns[i] >= ntt_mod) {
            ans[i] = mint(0);
            continue;
        }
        order.push_back({(int)ns[i], i});
    }
    if (order.empty()) return ans;
    sort(order.begin(), order.end());

    vector<int> uniq_ns, group_begin;
    uniq_ns.reserve(order.size());
    group_begin.reserve(order.size() + 1);
    for (int l = 0; l < (int)order.size();) {
        int r = l + 1;
        while (r < (int)order.size() && order[r].first == order[l].first) ++r;
        uniq_ns.push_back(order[l].first);
        group_begin.push_back(l);
        l = r;
    }
    group_begin.push_back(order.size());

    constexpr int log_block_size = 15;
    constexpr int block_size = 1 << log_block_size;
    constexpr int block_num = ntt_mod >> log_block_size;
    constexpr int manual_bits = 10;
    constexpr int manual_mask = (1 << manual_bits) - 1;

    static vector<mint> block_fact = []() {
        vector<vector<mint>> samples(log_block_size + 1);
        samples[0] = {mint(1), mint(2)};
        for (int lg = 0; lg < log_block_size; ++lg) {
            int d = 1 << lg;
            const vector<mint> &cur = samples[lg];
            vector<mint> shifted = sample_point_shift(cur, mint(d + 1), 3 * d + 1);
            vector<mint> next(2 * d + 1);
            for (int i = 0; i <= 2 * d; ++i) {
                mint left = 2 * i <= d ? cur[2 * i] : shifted[2 * i - (d + 1)];
                mint right = 2 * i + 1 <= d ? cur[2 * i + 1] : shifted[2 * i + 1 - (d + 1)];
                next[i] = left * right;
            }
            samples[lg + 1] = std::move(next);
        }
        vector<mint> blocks = sample_point_shift(samples[log_block_size], mint(0), block_num);
        blocks.insert(blocks.begin(), mint(1));
        for (int i = 1; i <= block_num; ++i) blocks[i] *= blocks[i - 1];
        return blocks;
    }();

    int m = uniq_ns.size();
    vector<mint> uniq_ans(m);
    vector<vector<EvalPoint>> eval_points(log_block_size);
    for (int i = 0; i < m; ++i) {
        int n = uniq_ns[i];
        int quo = n >> log_block_size;
        int rem = n & (block_size - 1);
        uniq_ans[i] = block_fact[quo];
        int tail = rem & manual_mask;
        for (int x = n - tail + 1; x <= n; ++x) uniq_ans[i] *= mint(x);
        int x = n - tail;
        int hi = rem - tail;
        for (int bit = manual_bits; bit < log_block_size; ++bit) {
            if ((hi >> bit) & 1) {
                eval_points[bit].push_back({x, i});
                x -= 1 << bit;
            }
        }
    }

    vector<poly> falling(log_block_size);
    falling[0] = poly(vector<mint>{mint(0), mint(1)});
    for (int bit = 1; bit < log_block_size; ++bit) {
        int d = 1 << (bit - 1);
        falling[bit] = falling[bit - 1] * taylor_shift(falling[bit - 1], mint(-d));
    }

    for (int bit = manual_bits; bit < log_block_size; ++bit) {
        auto &pts = eval_points[bit];
        if (pts.empty()) continue;
        sort(pts.begin(), pts.end(), [](const EvalPoint &a, const EvalPoint &b) {
            return a.x < b.x;
        });
        int batch = 1 << bit;
        for (int l = 0; l < (int)pts.size();) {
            vector<mint> xs;
            vector<pair<int, int>> groups;
            xs.reserve(batch);
            groups.reserve(batch);
            while (l < (int)pts.size() && (int)xs.size() < batch) {
                int r = l + 1;
                while (r < (int)pts.size() && pts[r].x == pts[l].x) ++r;
                xs.push_back(mint(pts[l].x));
                groups.push_back({l, r});
                l = r;
            }
            vector<mint> ys = falling[bit].multipoint_eval(xs);
            for (int i = 0; i < (int)groups.size(); ++i) {
                auto [gl, gr] = groups[i];
                for (int j = gl; j < gr; ++j) uniq_ans[pts[j].query_id] *= ys[i];
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = group_begin[i]; j < group_begin[i + 1]; ++j) ans[order[j].second] = uniq_ans[i];
    }
    return ans;
}

/**
 * @brief 多数階乗(Many Factorials)
 */
