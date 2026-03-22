#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include <algorithm>
#include <cassert>
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
#include "../fps/taylor_shift.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, c;
    in.read(n, c);
    poly f(n);
    for (int i = 0; i < n; ++i) {
        int x;
        in.read(x);
        f[i] = x;
    }
    poly g = taylor_shift(f, mint(c));
    for (int i = 0; i < n; ++i) {
        if (i) out.print(' ');
        out.print(g[i].val);
    }
    out.println();
    return 0;
}
