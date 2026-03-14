#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <vector>

using ll = long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/binaryindexedtree.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, q;
    in.read(n, q);
    vector<ll> v(n);
    in.read(v);
    BIT<ll> S(n);
    for (int i = 0; i < n; ++i) S.add(i, v[i]);

    for (int i = 0; i < q; ++i) {
        int c, x, y;
        in.read(c, x, y);
        if(c == 0) S.add(x, y);
        else out.writeln(S.sum(y) - S.sum(x));
    }
    return 0;
}
