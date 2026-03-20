#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

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
        pr.writeln((x * y).to_string());
    }
    return 0;
}
