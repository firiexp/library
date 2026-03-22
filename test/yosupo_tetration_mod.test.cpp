#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"
using ll = long long;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/tetration.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        int a, b, m;
        sc.read(a, b, m);
        pr.println(tetration(a, b, m));
    }
    return 0;
}
