#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include "../util/fastio.cpp"
#include "../math/kth_root_integer.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        unsigned long long a;
        int k;
        sc.read(a, k);
        pr.writeln(kth_root_integer(a, k));
    }
    return 0;
}
