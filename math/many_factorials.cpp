#include "../math/ntt.cpp"

namespace {

vector<mint> convolve(const vector<mint> &a, const vector<mint> &b) {
    if (a.empty() || b.empty()) return {};
    return (poly(a) * poly(b)).v;
}

struct ManyFactorialsFactorial {
    static inline vector<mint> fact = {mint(1)};
    static inline vector<mint> ifact = {mint(1)};

    static void ensure(int size) {
        if ((int)fact.size() >= size) return;
        int cur = fact.size();
        int next = max(cur * 2, size);
        fact.resize(next);
        ifact.resize(next);
        for (int i = cur; i < next; ++i) fact[i] = fact[i - 1] * mint::raw(i);
        ifact.back() = fact.back().inv();
        for (int i = next - 1; i > cur; --i) ifact[i - 1] = ifact[i] * mint::raw(i);
    }
};

vector<mint> shift_of_sampling_points(const vector<mint> &ys, mint t, int m) {
    int n = ys.size();
    ManyFactorialsFactorial::ensure(max(n, m));

    vector<mint> b(n);
    {
        vector<mint> f(n), g(n);
        for (int i = 0; i < n; ++i) {
            f[i] = ys[i] * ManyFactorialsFactorial::ifact[i];
            g[i] = ((i & 1) ? -mint(1) : mint(1)) * ManyFactorialsFactorial::ifact[i];
        }
        b = convolve(f, g);
        b.resize(n);
    }

    vector<mint> e(n);
    {
        vector<mint> c(n);
        mint prod = mint(1);
        reverse(b.begin(), b.end());
        for (int i = 0; i < n; ++i) {
            b[i] *= ManyFactorialsFactorial::fact[n - i - 1];
            c[i] = prod * ManyFactorialsFactorial::ifact[i];
            prod *= t - mint(i);
        }
        e = convolve(b, c);
        e.resize(n);
    }

    reverse(e.begin(), e.end());
    for (int i = 0; i < n; ++i) e[i] *= ManyFactorialsFactorial::ifact[i];

    vector<mint> f(m);
    for (int i = 0; i < m; ++i) f[i] = ManyFactorialsFactorial::ifact[i];
    vector<mint> res = convolve(e, f);
    res.resize(m);
    for (int i = 0; i < m; ++i) res[i] *= ManyFactorialsFactorial::fact[i];
    return res;
}

vector<mint> many_factorials_short_block(const vector<int> &uniq_ns) {
    constexpr int log_block_size = 9;
    constexpr int block_size = 1 << log_block_size;
    constexpr int block_num = ntt_mod >> log_block_size;

    static vector<mint> block_fact = []() {
        vector<mint> f{mint(1)};
        f.reserve(block_size);
        for (int i = 0; i < log_block_size; ++i) {
            vector<mint> g = shift_of_sampling_points(f, mint(1 << i), 3 << i);
            auto get = [&](int j) -> mint {
                return j < (1 << i) ? f[j] : g[j - (1 << i)];
            };
            f.resize(2 << i);
            for (int j = 0; j < (2 << i); ++j) {
                f[j] = get(2 * j) * get(2 * j + 1) * mint::raw((2 * j + 1) << i);
            }
        }
        if (block_num > block_size) {
            vector<mint> g = shift_of_sampling_points(f, mint(block_size), block_num - block_size);
            f.insert(f.end(), g.begin(), g.end());
        } else {
            f.resize(block_num);
        }
        for (int i = 0; i < block_num; ++i) f[i] *= mint::raw(i + 1) * mint::raw(block_size);
        f.insert(f.begin(), mint(1));
        for (int i = 1; i <= block_num; ++i) f[i] *= f[i - 1];
        return f;
    }();

    int m = uniq_ns.size();
    vector<mint> uniq_ans(m);
    for (int i = 0; i < m; ++i) {
        int n = uniq_ns[i];
        int quo = n >> log_block_size;
        int rem = n & (block_size - 1);
        if ((rem << 1) <= block_size) {
            uniq_ans[i] = block_fact[quo];
            for (int x = n - rem + 1; x <= n; ++x) uniq_ans[i] *= mint::raw(x);
        } else {
            uniq_ans[i] = block_fact[quo + 1];
            mint den = mint(1);
            for (int x = n + 1; x <= (quo + 1) * block_size; ++x) den *= mint::raw(x);
            uniq_ans[i] /= den;
        }
    }
    return uniq_ans;
}

}  // namespace

vector<mint> many_factorials(const vector<long long> &ns) {
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

    vector<mint> uniq_ans = many_factorials_short_block(uniq_ns);
    for (int i = 0; i < (int)uniq_ns.size(); ++i) {
        for (int j = group_begin[i]; j < group_begin[i + 1]; ++j) ans[order[j].second] = uniq_ans[i];
    }
    return ans;
}

/**
 * @brief Many Factorials
 */
