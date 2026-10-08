ll matrix_determinant_mod(vector<vector<ll>> A, int mod) {
    assert(mod >= 1);
    int n = A.size();
    for (auto& row : A) {
        assert((int)row.size() == n);
        for (auto& x : row) {
            x %= mod;
            if (x < 0) x += mod;
        }
    }
    ll det = 1 % mod;
    for (int col = 0; col < n; ++col) {
        for (int row = col + 1; row < n; ++row) {
            while (A[row][col]) {
                ll quotient = A[col][col] / A[row][col];
                for (int j = col; j < n; ++j) {
                    A[col][j] = (A[col][j] - quotient * A[row][j]) % mod;
                    if (A[col][j] < 0) A[col][j] += mod;
                }
                swap(A[col], A[row]);
                det = -det;
            }
        }
        if (A[col][col] == 0) return 0;
        det = det * A[col][col] % mod;
    }
    if (det < 0) det += mod;
    return det;
}

/**
 * @brief 任意の法の行列式
 */
