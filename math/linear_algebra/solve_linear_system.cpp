#include "./gauss_jordan_mint.cpp"

struct LinearSystemSolution {
    int rank;
    vector<mint> particular;
    vector<vector<mint>> basis;
};

optional<LinearSystemSolution> solve_linear_system(vector<vector<mint>> A, const vector<mint>& b, int variables = -1) {
    int n = A.size();
    assert(variables >= -1 && (int)b.size() == n);
    int m = variables < 0 ? (n ? (int)A[0].size() : 0) : variables;
    for (int row = 0; row < n; ++row) {
        assert((int)A[row].size() == m);
        A[row].push_back(b[row]);
    }
    int rank = n ? gauss_jordan(A, true) : 0;
    for (int row = rank; row < n; ++row) {
        if (A[row][m].val) return nullopt;
    }

    vector<int> pivot(rank), is_pivot(m);
    for (int row = 0; row < rank; ++row) {
        for (int col = 0; col < m; ++col) {
            if (A[row][col].val) {
                pivot[row] = col;
                is_pivot[col] = 1;
                break;
            }
        }
    }

    LinearSystemSolution result{rank, vector<mint>(m), {}};
    for (int row = 0; row < rank; ++row) {
        result.particular[pivot[row]] = A[row][m];
    }
    for (int col = 0; col < m; ++col) {
        if (is_pivot[col]) continue;
        vector<mint> v(m);
        v[col] = 1;
        for (int row = 0; row < rank; ++row) v[pivot[row]] = -A[row][col];
        result.basis.push_back(move(v));
    }
    return result;
}

/**
 * @brief 連立一次方程式の解空間
 */
