#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

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
#include "../fps/multipoint_evaluation.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    poly f(n);
    for (int i = 0; i < n; ++i) {
        int x;
        in.read(x);
        f[i] = x;
    }
    vector<mint> xs(m);
    for (int i = 0; i < m; ++i) {
        int x;
        in.read(x);
        xs[i] = x;
    }
    vector<mint> ys = f.multipoint_eval(xs);
    for (int i = 0; i < m; ++i) {
        if (i) out.write(' ');
        out.write(ys[i].val);
    }
    out.writeln();
    return 0;
}
