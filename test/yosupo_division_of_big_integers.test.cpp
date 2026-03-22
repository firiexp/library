#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <type_traits>
#include <vector>

#include "../util/fastio.cpp"
#include "../util/biginteger.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        string a, b;
        sc.read(a, b);
        BigInteger x(a), y(b);
        auto qr = BigInteger::divmod(x, y);
        pr.println(qr.first.to_string(), ' ', qr.second.to_string());
    }
    return 0;
}
