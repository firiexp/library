#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
using ll = long long;

#include "../util/fastio.cpp"
#include "../math/floor_sum.cpp"

int main() {
    Scanner in;
    Printer out;

    int t;
    in.read(t);
    while (t--) {
        ll n, m, a, b;
        in.read(n, m, a, b);
        out.writeln(floor_sum(n, m, a, b));
    }
    return 0;
}
