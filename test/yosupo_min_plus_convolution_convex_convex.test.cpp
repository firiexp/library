#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"

#include <algorithm>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/min_plus_convolution.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    vector<long long> a(n), b(m);
    for (auto &x : a) sc.read(x);
    for (auto &x : b) sc.read(x);

    auto c = min_plus_convolution_convex_convex(a, b);
    for (int i = 0; i < (int)c.size(); ++i) {
        pr.print(c[i]);
        pr.print(i + 1 == (int)c.size() ? '\n' : ' ');
    }
    return 0;
}
