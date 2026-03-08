#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include <cstdint>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../math/primitive_root.cpp"

int main() {
    Scanner in;
    Printer out;
    int q;
    in.read(q);
    while (q--) {
        ll p;
        in.read(p);
        out.writeln(primitive_root(p));
    }
    return 0;
}
