template<class T, bool Minimize = true>
tuple<T, vector<int>, vector<T>, vector<T>> hungarian(const vector<vector<T>> &cost) {
    int n = cost.size();
    if (n == 0) return {T(0), {}, {}, {}};
    int m = cost[0].size();
    assert(n <= m);
    for (int i = 0; i < n; ++i) assert((int)cost[i].size() == m);

    vector<vector<T>> a(n + 1, vector<T>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i + 1][j + 1] = Minimize ? cost[i][j] : -cost[i][j];
        }
    }

    vector<int> p(m + 1), way(m + 1);
    vector<T> u(n + 1), v(m + 1), minv(m + 1);
    vector<char> used(m + 1);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        fill(minv.begin(), minv.end(), numeric_limits<T>::max());
        fill(used.begin(), used.end(), 0);
        int j0 = 0;
        while (p[j0] != 0) {
            used[j0] = 1;
            int i0 = p[j0], j1 = 0;
            T delta = numeric_limits<T>::max();
            for (int j = 1; j <= m; ++j) {
                if (used[j]) continue;
                T cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
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
    for (int i = 0; i < n; ++i) row[i] = u[i + 1];
    for (int j = 0; j < m; ++j) col[j] = v[j + 1];
    T ans = -v[0];
    if (!Minimize) {
        ans = -ans;
        for (int i = 0; i < n; ++i) row[i] = -row[i];
        for (int j = 0; j < m; ++j) col[j] = -col[j];
    }
    return {ans, match, row, col};
}

/**
 * @brief Hungarian algorithm
 * @docs _md/hungarian.md
 */
