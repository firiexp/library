#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../util/fastio.cpp"
#include "../math/mod_sqrt.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long y, p;
        sc.read(y, p);
        pr.writeln(mod_sqrt(y, p));
    }
    return 0;
}
