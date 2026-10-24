template<class T, bool Minimize = true>
tuple<T, vector<int>, vector<T>, vector<T>> hungarian(const vector<vector<T>> &cost) {
    int n = cost.size();
    if (n == 0) return {T(0), {}, {}, {}};
    int m = cost[0].size();
    assert(n <= m);
    for (int i = 0; i < n; ++i) assert((int)cost[i].size() == m);

    auto solve = [&](auto zero) -> tuple<T, vector<int>, vector<T>, vector<T>> {
        using Wide = decltype(zero);
        vector<int> p(m + 1), way(m + 1), visited;
        vector<Wide> u(n + 1), v(m + 1), minv(m + 1);
        vector<char> used(m + 1);
        visited.reserve(n);

        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            fill(minv.begin(), minv.end(), numeric_limits<Wide>::max());
            fill(used.begin(), used.end(), 0);
            visited.clear();
            minv[0] = 0;
            int j0 = 0;
            while (p[j0] != 0) {
                used[j0] = 1;
                visited.push_back(j0);
                int i0 = p[j0], j1 = 0;
                Wide offset = minv[j0] - u[i0];
                Wide distance = numeric_limits<Wide>::max();
                for (int j = 1; j <= m; ++j) {
                    if (used[j]) continue;
                    Wide value = cost[i0 - 1][j - 1];
                    Wide cur = (Minimize ? value : -value) + offset - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < distance) {
                        distance = minv[j];
                        j1 = j;
                    }
                }
                j0 = j1;
            }
            for (int j : visited) {
                Wide delta = minv[j0] - minv[j];
                u[p[j]] += delta;
                v[j] -= delta;
            }
            while (j0 != 0) {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            }
        }

        vector<int> match(n, -1);
        for (int j = 1; j <= m; ++j) {
            if (p[j] != 0) match[p[j] - 1] = j - 1;
        }

        vector<T> row(n), col(m);
        for (int i = 0; i < n; ++i) row[i] = T(Minimize ? u[i + 1] : -u[i + 1]);
        for (int j = 0; j < m; ++j) col[j] = T(Minimize ? v[j + 1] : -v[j + 1]);
        T ans = T(Minimize ? -v[0] : v[0]);
        return {ans, std::move(match), std::move(row), std::move(col)};
    };
    if constexpr (is_integral<T>::value) {
        long long limit = numeric_limits<long long>::max() / (8LL * (n + 1LL));
        unsigned long long magnitude = 0;
        for (const auto &row : cost) for (T value : row) {
            long long x = value;
            magnitude |= (unsigned long long)(x < 0 ? ~x : x);
        }
        if (magnitude < (unsigned long long)limit) return solve(0LL);
        return solve(__int128(0));
    } else {
        return solve(T(0));
    }
}

/**
 * @brief ハンガリアン法(Hungarian Algorithm)
 */
