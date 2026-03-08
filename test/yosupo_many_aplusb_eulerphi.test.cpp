#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../math/eulerphi.cpp"
#include "../math/eulerphi_all.cpp"
#include "../math/get_min_factor.cpp"

int brute_phi(int x) {
    int res = 0;
    for (int i = 1; i <= x; ++i) {
        if (gcd(i, x) == 1) ++res;
    }
    return res;
}

int brute_min_factor(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    for (int p = 2; p <= x; ++p) {
        if (x % p == 0) return p;
    }
    return x;
}

int main() {
    {
        for (int n = 1; n <= 300; ++n) {
            if (eulerphi(n) != brute_phi(n)) return 1;
        }

        for (int m = 1; m <= 300; ++m) {
            auto phi = eulerphi_all(m);
            if ((int)phi.size() != m) return 1;
            for (int i = 0; i < m; ++i) {
                if (phi[i] != (i == 0 ? 0 : brute_phi(i))) return 1;
            }
        }

        for (int n = 0; n <= 300; ++n) {
            auto min_factor = get_min_factor(n);
            if ((int)min_factor.size() != max(2, n + 1)) return 1;
            for (int i = 0; i <= n; ++i) {
                if (min_factor[i] != brute_min_factor(i)) return 1;
            }
        }

        mt19937 rng(123456789);
        for (int trial = 0; trial < 1000; ++trial) {
            int n = uniform_int_distribution<int>(1, 10000)(rng);
            if (eulerphi(n) != brute_phi(n)) return 1;
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
