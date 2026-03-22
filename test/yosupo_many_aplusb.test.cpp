#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"

int main() {
    Scanner in;
    Printer out;
    int t;
    in.read(t);
    while (t--) {
        long long a, b;
        in.read(a, b);
        out.println(a + b);
    }
    return 0;
}
