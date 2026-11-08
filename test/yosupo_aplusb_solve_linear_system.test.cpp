#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 5;
#include "../util/fastio.cpp"
#include "../math/linear_algebra/solve_linear_system.cpp"
#include "../math/linear_algebra/linear_system_decomposition.cpp"
#include "../math/linear_algebra/linear_system_decomposition.cpp"

int power5(int n) {
    int result = 1;
    while (n--) result *= 5;
    return result;
}

vector<mint> decode(int code, int m) {
    vector<mint> result(m);
    for (auto& x : result) {
        x = code % 5;
        code /= 5;
    }
    return result;
}

void check(const vector<vector<mint>>& a, const vector<mint>& b, int m,
           const LinearSystemDecomposition *decomposition = nullptr) {
    auto original_a = a;
    auto original_b = b;
    auto result = a.empty() ? solve_linear_system(a, b, m) : solve_linear_system(a, b);
    auto single = solve_linear_system(a, b, m, false);
    const LinearSystemDecomposition single_decomposition(a, m, false);
    auto single_particular = single_decomposition.solve(b);
    assert(bool(single) == bool(result));
    assert(bool(single_particular) == bool(result));
    assert(single_decomposition.basis().capacity() == 0);
    assert(single_particular == single_decomposition.solve(b));
    if (single) {
        assert(single->rank == result->rank && single_decomposition.rank() == result->rank);
        assert(single->particular == result->particular && *single_particular == result->particular);
        assert(single->basis.capacity() == 0);
    }
    optional<LinearSystemDecomposition> local;
    if (!decomposition) {
        local.emplace(a, m);
        decomposition = &*local;
    }
    const auto *basis_data = decomposition->basis().data();
    auto particular = decomposition->solve(b);
    assert(particular == decomposition->solve(b));
    assert(basis_data == decomposition->basis().data());
    assert(bool(particular) == bool(result));
    if (result) {
        assert(*particular == result->particular);
        assert(decomposition->rank() == result->rank);
        assert(decomposition->basis() == result->basis);
    }
    assert(a == original_a && b == original_b);
    vector<bool> generated(power5(m));
    if (result) {
        assert(result->rank >= 0 && result->rank <= min((int)a.size(), m));
        assert((int)result->particular.size() == m);
        assert((int)result->basis.size() == m - result->rank);
        for (const auto& v : result->basis) {
            assert((int)v.size() == m);
            for (const auto& row : a) {
                mint sum = 0;
                for (int j = 0; j < m; ++j) sum += row[j] * v[j];
                assert(sum.val == 0);
            }
        }
        for (int i = 0; i < (int)a.size(); ++i) {
            mint sum = 0;
            for (int j = 0; j < m; ++j) sum += a[i][j] * result->particular[j];
            assert(sum == b[i]);
        }
        for (int code = 0; code < power5(result->basis.size()); ++code) {
            vector<mint> x = result->particular;
            int coefficients = code;
            for (const auto& v : result->basis) {
                for (int j = 0; j < m; ++j) x[j] += mint(coefficients % 5) * v[j];
                coefficients /= 5;
            }
            int id = 0;
            for (int j = m - 1; j >= 0; --j) id = 5 * id + x[j].val;
            assert(!generated[id]);
            generated[id] = true;
        }
    }
    for (int code = 0; code < power5(m); ++code) {
        auto x = decode(code, m);
        bool valid = true;
        for (int i = 0; i < (int)a.size(); ++i) {
            mint sum = 0;
            for (int j = 0; j < m; ++j) sum += a[i][j] * x[j];
            valid &= sum == b[i];
        }
        assert(valid == generated[code]);
    }
}

void self_check() {
    auto empty = solve_linear_system({}, {});
    assert(empty && empty->rank == 0 && empty->particular.empty() && empty->basis.empty());
    const int width = 200000;
    for (int n : {0, 2}) {
        vector<vector<mint>> a(n, vector<mint>(width));
        vector<mint> b(n, 3);
        if (n) a[0][width - 1] = a[1][width - 1] = 1;
        auto single = solve_linear_system(a, b, width, false);
        const LinearSystemDecomposition decomposition(a, width, false);
        auto x = decomposition.solve(b);
        assert(single && x && single->rank == (n != 0));
        assert(single->particular.size() == width && single->basis.capacity() == 0);
        assert(decomposition.basis().capacity() == 0 && *x == single->particular);
        for (int j = 0; j < width; ++j) assert((*x)[j] == mint(n && j == width - 1 ? 3 : 0));
        if (n) {
            b[1] = 4;
            assert(!solve_linear_system(a, b, width, false) && !decomposition.solve(b));
        }
    }
    check({}, {}, 5);
    check({{}, {}}, {0, 0}, 0);
    check({{}, {}}, {0, 1}, 0);
    check({{0, 1, 2, 0, 3}, {0, 0, 0, 1, 2}, {0, 2, 4, 0, 1}}, {1, 2, 2}, 5);
    for (int n = 0; n <= 3; ++n) {
        for (int m = 0; m <= 3; ++m) {
            if (n * (m + 1) > 6) continue;
            for (int code = 0; code < power5(n * (m + 1)); ++code) {
                vector<vector<mint>> a(n, vector<mint>(m));
                vector<mint> b(n);
                int rest = code;
                for (int i = 0; i < n; ++i) {
                    for (auto& x : a[i]) {
                        x = rest % 5;
                        rest /= 5;
                    }
                    b[i] = rest % 5;
                    rest /= 5;
                }
                check(a, b, m);
            }
        }
    }
    mt19937 rng(75);
    LinearSystemDecomposition empty_decomposition({});
    assert(empty_decomposition.rank() == 0 && empty_decomposition.basis().empty());
    assert(empty_decomposition.solve({}) == optional<vector<mint>>(vector<mint>{}));
    for (int n = 0; n <= 3; ++n) for (int m = 0; m <= 3; ++m) {
        for (int trial = 0; trial < 20; ++trial) {
            vector<vector<mint>> a(n, vector<mint>(m));
            for (auto &row : a) for (auto &value : row) value = trial % 4 ? rng() % 5 : 0;
            const LinearSystemDecomposition decomposition(a, m);
            for (int code = 0; code < power5(n); ++code) check(a, decode(code, n), m, &decomposition);
        }
    }
    for (int tc = 0; tc < 1000; ++tc) {
        int n = rng() % 5, m = rng() % 6;
        vector<vector<mint>> a(n, vector<mint>(m));
        vector<mint> b(n);
        for (auto& row : a) for (auto& x : row) x = rng() % 5;
        for (auto& x : b) x = rng() % 5;
        check(a, b, m);
    }
}

int main() {
    self_check();
}
