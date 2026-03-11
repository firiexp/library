#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include <vector>
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../fps/sample_point_shift.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m, c;
    in.read(n, m, c);
    vector<mint> ys(n);
    for (int i = 0; i < n; ++i) {
        int x;
        in.read(x);
        ys[i] = x;
    }
    vector<mint> ans = sample_point_shift(ys, mint(c), m);
    for (int i = 0; i < m; ++i) {
        if (i) out.write(' ');
        out.write(ans[i].val);
    }
    out.writeln();
    return 0;
}
