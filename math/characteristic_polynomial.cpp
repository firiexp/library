template<class T>
vector<T> characteristic_polynomial(vector<vector<T>> a) {
    int n = (int)a.size();
    for (int k = 0; k + 2 < n; ++k) {
        int pivot = k + 1;
        while (pivot < n && a[pivot][k] == T(0)) ++pivot;
        if (pivot == n) continue;
        if (pivot != k + 1) {
            swap(a[pivot], a[k + 1]);
            for (auto& row : a) swap(row[pivot], row[k + 1]);
        }
        T inv = T(1) / a[k + 1][k];
        for (int i = k + 2; i < n; ++i) {
            if (a[i][k] == T(0)) continue;
            T factor = a[i][k] * inv;
            a[i][k] = 0;
            for (int j = k + 1; j < n; ++j) a[i][j] -= factor * a[k + 1][j];
            for (int j = 0; j < n; ++j) a[j][k + 1] += factor * a[j][i];
        }
    }
    vector<vector<T>> p(n + 1);
    p[0] = {T(1)};
    for (int i = 0; i < n; ++i) {
        p[i + 1].resize(i + 2);
        for (int j = 0; j <= i; ++j) {
            p[i + 1][j + 1] += p[i][j];
            p[i + 1][j] -= a[i][i] * p[i][j];
        }
        T product = 1;
        for (int k = i - 1; k >= 0; --k) {
            product *= a[k + 1][k];
            T factor = product * a[k][i];
            for (int j = 0; j <= k; ++j) p[i + 1][j] -= factor * p[k][j];
        }
    }
    return p[n];
}

/**
 * @brief 特性多項式
 */
