#include "../util/modint.cpp"

vector<vector<mint>> inverse_matrix(const vector<vector<mint>> &A) {
    int n = A.size();
    auto B = A;
    vector<int> pivots(n);
    for (int col = 0; col < n; ++col) {
        int pivot = col;
        while (pivot < n && B[pivot][col].val == 0) ++pivot;
        if (pivot == n) return {};
        pivots[col] = pivot;
        swap(B[pivot], B[col]);
        mint inv = B[col][col].inv();
        B[col][col] = 1;
        for (int j = 0; j < n; ++j) B[col][j] *= inv;
        for (int row = 0; row < n; ++row) {
            if (row != col && B[row][col].val) {
                mint coeff = B[row][col];
                B[row][col] = 0;
                for (int j = 0; j < n; ++j) {
                    B[row][j] -= B[col][j] * coeff;
                }
            }
        }
    }
    for (int col = n - 1; col >= 0; --col)
        if (pivots[col] != col)
            for (auto& row : B) swap(row[col], row[pivots[col]]);
    return B;
}

/**
 * @brief 逆行列(Inverse Matrix)
 */
