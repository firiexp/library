#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include <vector>
#include <optional>
#include <cassert>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/solve_linear_system.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m;
    in.read(n, m);
    vector<vector<mint>> a(n, vector<mint>(m));
    vector<mint> b(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            in.read(x);
            a[i][j] = x;
        }
    }
    for (int i = 0; i < n; ++i) {
        int x;
        in.read(x);
        b[i] = x;
    }

    auto solution = solve_linear_system(a, b, m);
    if (!solution) {
        out.println(-1);
        return 0;
    }

    out.println((int)solution->basis.size());
    for (int i = 0; i < m; ++i) {
        out.print(solution->particular[i].val);
        out.print(i + 1 == m ? '\n' : ' ');
    }
    for (auto &&vec : solution->basis) {
        for (int i = 0; i < m; ++i) {
            out.print(vec[i].val);
            out.print(i + 1 == m ? '\n' : ' ');
        }
    }
    return 0;
}
