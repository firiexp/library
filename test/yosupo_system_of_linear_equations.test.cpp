#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/gauss_jordan_mint.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m;
    in.read(n, m);
    vector<vector<mint>> a(n, vector<mint>(m + 1));
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
        a[i][m] = x;
    }

    int rank = gauss_jordan(a, true);
    for (int row = rank; row < n; ++row) {
        if (a[row][m].val) {
            out.println(-1);
            return 0;
        }
    }

    vector<int> pivot(rank, -1);
    vector<int> is_pivot(m);
    for (int row = 0; row < rank; ++row) {
        for (int col = 0; col < m; ++col) {
            if (a[row][col].val) {
                pivot[row] = col;
                is_pivot[col] = 1;
                break;
            }
        }
    }

    vector<mint> particular(m);
    for (int row = 0; row < rank; ++row) {
        particular[pivot[row]] = a[row][m];
    }

    vector<vector<mint>> basis;
    for (int free_col = 0; free_col < m; ++free_col) {
        if (is_pivot[free_col]) continue;
        vector<mint> vec(m);
        vec[free_col] = 1;
        for (int row = 0; row < rank; ++row) {
            vec[pivot[row]] = -a[row][free_col];
        }
        basis.push_back(vec);
    }

    out.println((int)basis.size());
    for (int i = 0; i < m; ++i) {
        out.print(particular[i].val);
        out.print(i + 1 == m ? '\n' : ' ');
    }
    for (auto &&vec : basis) {
        for (int i = 0; i < m; ++i) {
            out.print(vec[i].val);
            out.print(i + 1 == m ? '\n' : ' ');
        }
    }
    return 0;
}
