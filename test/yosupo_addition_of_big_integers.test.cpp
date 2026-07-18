#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"

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
        BigInteger x, y;
        sc.read(x, y);
        pr.println(x + y);
    }
    return 0;
}
