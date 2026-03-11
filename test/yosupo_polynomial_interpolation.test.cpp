#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include <algorithm>
#include <utility>
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
#include "../fps/polynomial_interpolation.cpp"

int main() {
    Scanner in;
    Printer out;
    int n;
    in.read(n);
    vector<mint> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        int x;
        in.read(x);
        xs[i] = x;
    }
    for (int i = 0; i < n; ++i) {
        int y;
        in.read(y);
        ys[i] = y;
    }
    poly f = polynomial_interpolation(xs, ys);
    for (int i = 0; i < n; ++i) {
        if (i) out.write(' ');
        out.write(f[i].val);
    }
    out.writeln();
    return 0;
}
