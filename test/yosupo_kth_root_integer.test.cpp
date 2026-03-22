#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../math/kth_root_integer.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        ull a;
        int k;
        sc.read(a, k);
        pr.println(kth_root_integer(a, k));
    }
    return 0;
}
