#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../fps/nth_term.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int d;
    ll n;
    sc.read(d, n);
    vector<mint> a(d), c(d);
    for (int i = 0; i < d; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }
    for (int i = 0; i < d; ++i) {
        int x;
        sc.read(x);
        c[i] = x;
    }

    poly q(d + 1);
    q[0] = 1;
    for (int i = 0; i < d; ++i) q[i + 1] = -c[i];
    poly p = (poly(a) * q).cut(d);
    pr.writeln(nth_term(p, q, n).val);
    return 0;
}
