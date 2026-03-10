#include "../util/modint.cpp"

mint matrix_determinant(vector<vector<mint>> A) {
    int n = A.size();
    mint det = 1;
    for (int col = 0; col < n; ++col) {
        int pivot = col;
        while (pivot < n && !A[pivot][col].val) ++pivot;
        if (pivot == n) return 0;
        if (pivot != col) {
            swap(A[pivot], A[col]);
            det = -det;
        }
        det *= A[col][col];
        mint inv = A[col][col].inv();
        for (int row = col + 1; row < n; ++row) {
            if (!A[row][col].val) continue;
            mint coeff = A[row][col] * inv;
            for (int j = col; j < n; ++j) {
                A[row][j] -= A[col][j] * coeff;
            }
        }
    }
    return det;
}

/**
 * @brief 行列式(Matrix Determinant)
 */
