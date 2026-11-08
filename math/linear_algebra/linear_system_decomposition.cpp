#ifndef FIRIEXP_LIBRARY_MATH_LINEAR_SYSTEM_DECOMPOSITION_CPP
#define FIRIEXP_LIBRARY_MATH_LINEAR_SYSTEM_DECOMPOSITION_CPP

#include "../modular/modint.cpp"

class LinearSystemDecomposition {
    struct Step {
        int swapped_row, column;
        mint inverse;
        vector<mint> factors;
    };
    int rows, columns;
    vector<Step> steps;
    vector<vector<mint>> kernel;

public:
    explicit LinearSystemDecomposition(vector<vector<mint>> a, int variables = -1, bool build_basis = true)
        : rows(a.size()), columns(variables < 0 ? (rows ? a[0].size() : 0) : variables) {
        assert(variables >= -1);
        for (const auto &row : a) assert((int)row.size() == columns);
        vector<char> is_pivot(columns);
        for (int col = 0; col < columns && rank() < rows; ++col) {
            int r = rank(), pivot = r;
            while (pivot < rows && !a[pivot][col].val) ++pivot;
            if (pivot == rows) continue;
            swap(a[r], a[pivot]);
            mint inverse = a[r][col].inv();
            for (int j = col; j < columns; ++j) a[r][j] *= inverse;
            steps.push_back({pivot, col, inverse, vector<mint>(rows)});
            for (int i = 0; i < rows; ++i) {
                if (i == r || !a[i][col].val) continue;
                mint factor = a[i][col];
                steps.back().factors[i] = factor;
                for (int j = col; j < columns; ++j) a[i][j] -= a[r][j] * factor;
            }
            is_pivot[col] = true;
        }
        if (!build_basis) return;
        for (int col = 0; col < columns; ++col) {
            if (is_pivot[col]) continue;
            vector<mint> v(columns);
            v[col] = 1;
            for (int r = 0; r < rank(); ++r) v[steps[r].column] = -a[r][col];
            kernel.push_back(move(v));
        }
    }

    int rank() const { return steps.size(); }
    const vector<vector<mint>> &basis() const { return kernel; }

    optional<vector<mint>> solve(vector<mint> b) const {
        assert((int)b.size() == rows);
        for (int r = 0; r < rank(); ++r) {
            const auto &step = steps[r];
            swap(b[r], b[step.swapped_row]);
            b[r] *= step.inverse;
            for (int i = 0; i < rows; ++i) {
                if (step.factors[i].val) b[i] -= b[r] * step.factors[i];
            }
        }
        for (int i = rank(); i < rows; ++i) if (b[i].val) return nullopt;
        vector<mint> result(columns);
        for (int r = 0; r < rank(); ++r) result[steps[r].column] = b[r];
        return result;
    }
};

#endif

/**
 * @brief 連立一次方程式の分解再利用
 */
