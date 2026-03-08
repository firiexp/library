#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <random>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/binaryindexedtree.cpp"

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 1; n <= 80; ++n) {
            for (int trial = 0; trial < 200; ++trial) {
                vector<int> a(n), b(n);
                BIT<int> bit(n), bit_nonneg(n);
                for (int i = 0; i < n; ++i) {
                    a[i] = uniform_int_distribution<int>(0, 4)(rng);
                    b[i] = uniform_int_distribution<int>(0, 4)(rng);
                    bit.add(i, a[i]);
                    bit_nonneg.add(i, b[i]);
                }
                for (int iter = 0; iter < 200; ++iter) {
                    int type = uniform_int_distribution<int>(0, 2)(rng);
                    if (type == 0) {
                        int i = uniform_int_distribution<int>(0, n - 1)(rng);
                        int x = uniform_int_distribution<int>(-2, 3)(rng);
                        a[i] += x;
                        bit.add(i, x);
                        int y = uniform_int_distribution<int>(0, 3)(rng);
                        b[i] += y;
                        bit_nonneg.add(i, y);
                    } else if (type == 1) {
                        int r = uniform_int_distribution<int>(0, n)(rng);
                        int expect = 0;
                        for (int i = 0; i < r; ++i) expect += a[i];
                        if (bit.sum(r) != expect) return 1;
                    } else {
                        int total = 0;
                        for (auto &&x : b) total += x;
                        if (total <= 0) continue;
                        int x = uniform_int_distribution<int>(1, total)(rng);
                        int expect = 0;
                        int sum = 0;
                        while (expect < n && sum < x) {
                            sum += b[expect];
                            ++expect;
                        }
                        if (bit_nonneg.lower_bound(x) != expect) return 1;
                    }
                }
            }
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
