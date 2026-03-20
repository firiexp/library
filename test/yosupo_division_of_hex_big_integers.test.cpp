#define PROBLEM "https://judge.yosupo.jp/problem/division_of_hex_big_integers"

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
    auto to_upper_hex = [](string s) {
        for (char &c : s) {
            if ('a' <= c && c <= 'f') c = char(c - 'a' + 'A');
        }
        return s;
    };
    int t;
    sc.read(t);
    while (t--) {
        string a, b;
        sc.read(a, b);
        BigInteger x(a, 16), y(b, 16);
        auto qr = BigInteger::divmod(x, y);
        pr.writeln(to_upper_hex(qr.first.to_string(16)), ' ', to_upper_hex(qr.second.to_string(16)));
    }
    return 0;
}
