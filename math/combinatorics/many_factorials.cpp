#include "../../fps/sample_point_shift.cpp"
#include "../modular/batch_inverse.cpp"

namespace {

constexpr int factorial_block_size = 512;
constexpr int factorial_block_count = ntt_mod / factorial_block_size;

vector<mint> many_factorials_short_block(const vector<int> &uniq_ns) {
    constexpr int block_size = factorial_block_size;
    static const vector<mint> block_fact = []() {
        vector<mint> f{mint(1)};
        f.reserve(block_size);
        for (int width = 1; width < block_size; width *= 2) {
            vector<mint> g = sample_point_shift(f, mint(width), 3 * width);
            auto get = [&](int j) -> mint {
                return j < width ? f[j] : g[j - width];
            };
            f.resize(2 * width);
            for (int j = 0; j < 2 * width; ++j) {
                f[j] = get(2 * j) * get(2 * j + 1) * mint::raw((2 * j + 1) * width);
            }
        }
        vector<mint> table{mint(1)};
        table.reserve(factorial_block_count + 1);
        auto append = [&](const vector<mint> &samples) {
            for (mint x : samples) {
                int end = (int)table.size() * block_size;
                table.push_back(table.back() * (x * mint::raw(end)));
            }
        };
        append(f);
        constexpr int shift_count = 7 * block_size;
        for (int start = block_size; start < factorial_block_count; start += shift_count) {
            int count = min(shift_count, factorial_block_count - start);
            append(sample_point_shift(f, mint(start), count));
        }
        return table;
    }();

    int m = uniq_ns.size();
    vector<mint> uniq_ans(m);
    vector<int> upper;
    vector<mint> denominators;
    for (int i = 0; i < m; ++i) {
        int n = uniq_ns[i];
        int quo = n / block_size;
        int rem = n % block_size;
        if (rem <= block_size / 2) {
            uniq_ans[i] = block_fact[quo];
            for (int x = n - rem + 1; x <= n; ++x) uniq_ans[i] *= mint::raw(x);
        } else {
            uniq_ans[i] = block_fact[quo + 1];
            mint den = mint(1);
            for (int x = n + 1; x <= (quo + 1) * block_size; ++x) den *= mint::raw(x);
            upper.push_back(i);
            denominators.push_back(den);
        }
    }
    auto inverses = batch_inverse(denominators);
    for (int j = 0; j < (int)upper.size(); ++j) uniq_ans[upper[j]] *= inverses[j];
    return uniq_ans;
}

}  // namespace

vector<mint> many_factorials(const vector<long long> &ns) {
    int q = ns.size();
    vector<mint> ans(q);
    if (q == 0) return ans;

    int maximum = -1;
    for (long long n : ns) {
        assert(n >= 0);
        if (n < ntt_mod) maximum = max(maximum, (int)n);
    }
    if (maximum == -1) return ans;
    static vector<mint> fact{mint(1)};
    if (maximum <= 2 * factorial_block_count) {
        if (maximum >= (int)fact.size()) {
            int old = fact.size();
            fact.resize(maximum + 1);
            for (int i = old; i <= maximum; ++i) fact[i] = fact[i - 1] * mint::raw(i);
        }
        for (int i = 0; i < q; ++i) {
            if (ns[i] < ntt_mod) ans[i] = fact[ns[i]];
        }
        return ans;
    }

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

    vector<mint> uniq_ans = many_factorials_short_block(uniq_ns);
    for (int i = 0; i < (int)uniq_ns.size(); ++i) {
        for (int j = group_begin[i]; j < group_begin[i + 1]; ++j) ans[order[j].second] = uniq_ans[i];
    }
    return ans;
}

/**
 * @brief Many Factorials
 */
