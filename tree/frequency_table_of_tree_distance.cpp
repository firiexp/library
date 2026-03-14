#define FIRIEXP_LIBRARY_FFT_EXACT_ONLY
#include "../math/fft.cpp"
#undef FIRIEXP_LIBRARY_FFT_EXACT_ONLY

vector<long long> frequency_table_of_tree_distance(const vector<vector<int>> &g) {
    using ArbitraryConvolution::square_u64;

    int n = (int)g.size();
    if (n == 0) return {};

    vector<int> sz(n);
    vector<char> used(n, 0);
    vector<long long> ordered(n);

    auto dfs_size = [&](auto &&self, int v, int p) -> int {
        sz[v] = 1;
        for (auto &&to : g[v]) {
            if (to == p || used[to]) continue;
            sz[v] += self(self, to, v);
        }
        return sz[v];
    };

    auto find_centroid = [&](auto &&self, int v, int p, int half) -> int {
        for (auto &&to : g[v]) {
            if (to == p || used[to]) continue;
            if (sz[to] > half) return self(self, to, v, half);
        }
        return v;
    };

    auto collect = [&](auto &&self, int v, int p, int d, vector<unsigned int> &cnt) -> void {
        if ((int)cnt.size() <= d) cnt.resize(d + 1);
        ++cnt[d];
        for (auto &&to : g[v]) {
            if (to == p || used[to]) continue;
            self(self, to, v, d + 1, cnt);
        }
    };

    auto add_convolution = [&](const vector<unsigned long long> &conv, int sign) {
        int lim = min(n, (int)conv.size());
        for (int d = 0; d < lim; ++d) {
            ordered[d] += sign * (long long)conv[d];
        }
    };

    auto solve = [&](auto &&self, int start) -> void {
        int centroid = find_centroid(find_centroid, start, -1, dfs_size(dfs_size, start, -1) / 2);
        used[centroid] = 1;

        vector<unsigned int> total(1, 1);
        for (auto &&to : g[centroid]) {
            if (used[to]) continue;
            vector<unsigned int> cnt(1, 0);
            collect(collect, to, centroid, 1, cnt);
            add_convolution(square_u64(cnt), -1);
            if (total.size() < cnt.size()) total.resize(cnt.size());
            for (int d = 1; d < (int)cnt.size(); ++d) total[d] += cnt[d];
        }
        add_convolution(square_u64(total), 1);

        for (auto &&to : g[centroid]) {
            if (!used[to]) self(self, to);
        }
    };

    solve(solve, 0);

    vector<long long> ans(n);
    for (int d = 1; d < n; ++d) ans[d] = ordered[d] / 2;
    return ans;
}

/**
 * @brief 木距離頻度表(Frequency Table of Tree Distance)
 */
