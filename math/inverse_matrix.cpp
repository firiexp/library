#include "../util/modint.cpp"

vector<vector<mint>> inverse_matrix(const vector<vector<mint>> &A) {
    int n = A.size();
    vector<vector<mint>> B(n, vector<mint>(2 * n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) B[i][j] = A[i][j];
        B[i][n + i] = 1;
    }
    int rank = 0;
    for (int col = 0; col < n; ++col) {
        int pivot = -1;
        for (int row = rank; row < n; ++row) {
            if (B[row][col].val) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) return {};
        swap(B[pivot], B[rank]);
        mint inv = B[rank][col].inv();
        for (int j = 0; j < 2 * n; ++j) B[rank][j] *= inv;
        for (int row = 0; row < n; ++row) {
            if (row != rank && B[row][col].val) {
                mint coeff = B[row][col];
                for (int j = 0; j < 2 * n; ++j) {
                    B[row][j] -= B[rank][j] * coeff;
                }
            }
        }
        ++rank;
    }
    vector<vector<mint>> res(n, vector<mint>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) res[i][j] = B[i][n + j];
    }
    return res;
}

/**
 * @brief 逆行列(Inverse Matrix)
 */
