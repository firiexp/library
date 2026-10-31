#include "../modular/modint.cpp"

int matrix_rank(vector<vector<mint>> A) {
    int h = A.size(), w = h ? A[0].size() : 0;
    int rank = 0;
    for (int col = 0; col < w && rank < h; ++col) {
        int pivot = rank;
        while (pivot < h && A[pivot][col] == mint(0)) ++pivot;
        if (pivot == h) continue;
        swap(A[pivot], A[rank]);
        mint inv = A[rank][col].inv();
        for (int row = rank + 1; row < h; ++row) {
            if (A[row][col] == mint(0)) continue;
            mint factor = A[row][col] * inv;
            for (int j = col + 1; j < w; ++j) A[row][j] -= A[rank][j] * factor;
        }
        ++rank;
    }
    return rank;
}

/**
 * @brief 行列の階数
 */
