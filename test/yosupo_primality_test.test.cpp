#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include <cstdint>
#include <vector>

using ull = unsigned long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/miller_rabin.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int q;
    sc.read(q);
    while (q--) {
        ull n;
        sc.read(n);
        pr.writeln(miller_rabin(n) ? "Yes" : "No");
    }
    return 0;
}
