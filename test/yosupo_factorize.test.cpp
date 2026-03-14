#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <random>
#include <vector>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/primefactor_ll.cpp"

int main() {
    Scanner in;
    Printer out;
    int q;
    in.read(q);
    while (q--) {
        ull a;
        in.read(a);
        auto fac = prime_factor(a);
        out.write((int)fac.size());
        if (fac.empty()) out.writeln();
        else {
            out.write(' ');
            out.writeln(fac);
        }
    }
    return 0;
}
