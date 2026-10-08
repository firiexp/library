#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 5;
#include "../util/fastio.cpp"
#include "../math/solve_linear_system.cpp"

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

void check(const vector<vector<mint>>& a, const vector<mint>& b, int m) {
    auto original_a = a;
    auto original_b = b;
    auto result = a.empty() ? solve_linear_system(a, b, m) : solve_linear_system(a, b);
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
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
