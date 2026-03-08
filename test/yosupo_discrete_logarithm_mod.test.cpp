#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../util/fastio.cpp"
#include "../math/discrete_logarithm.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long x, y, mod;
        sc.read(x, y, mod);
        pr.writeln(discrete_logarithm(x, y, mod));
    }
    return 0;
}
