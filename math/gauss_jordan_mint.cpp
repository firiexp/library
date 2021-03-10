#include "../util/modint.cpp"

int gauss_jordan(vector<vector<mint>> &A, bool is_extended = false) {
    int m = A.size(), n = A[0].size();
    int rank = 0;
    for (int col = 0; col < n; ++col) {
        if (is_extended && col == n-1) break;
        int pivot = -1;
        for (int row = rank; row < m; ++row) {
            if (A[row][col].val) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        swap(A[pivot], A[rank]);
        auto d = A[rank][col].inv();
        for (int col2 = 0; col2 < n; ++col2) A[rank][col2] *= d;
        for (int row = 0; row < m; ++row) {
            if (row != rank && A[row][col].val) {
                auto fac = A[row][col];
                for (int col2 = 0; col2 < n; ++col2) {
                    A[row][col2] -= A[rank][col2] * fac;
                }
            }
        }
        ++rank;
    }
    return rank;
}