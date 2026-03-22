#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include <algorithm>
#include <cassert>
#include <limits>
#include <tuple>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../flow/hungarian.cpp"

int main() {
    Scanner in;
    Printer out;
    int n;
    in.read(n);
    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in.read(a[i][j]);
        }
    }
    auto [ans, match, row, col] = hungarian<long long>(a);
    out.println(ans);
    for (int i = 0; i < n; ++i) {
        if (i) out.print(' ');
        out.print(match[i]);
    }
    out.println();

    long long dual_sum = 0;
    for (int i = 0; i < n; ++i) dual_sum += row[i];
    for (int j = 0; j < n; ++j) dual_sum += col[j];
    assert(dual_sum == ans);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(row[i] + col[j] <= a[i][j]);
        }
    }
    return 0;
}
