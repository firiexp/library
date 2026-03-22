#define PROBLEM "https://yukicoder.me/problems/no/2672"

#include <cassert>
#include <cstdint>
#include <random>
#include <vector>
using namespace std;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/xor_basis.cpp"

bool brute(const vector<int> &a) {
    int n = a.size();
    for (int mask = 1; mask < (1 << n) - 1; ++mask) {
        int xb = 0;
        int xc = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) xb ^= a[i];
            else xc ^= a[i];
        }
        if (xb == 0 && xc == 0) return true;
    }
    return false;
}

void self_check() {
    {
        for (int n = 2; n <= 12; ++n) {
            for (int mask = 0; mask < (1 << n); ++mask) {
                vector<int> a(n);
                for (int i = 0; i < n; ++i) a[i] = (mask >> i) & 1;
                XorBasis<int> xb;
                int total = 0;
                for (int x : a) {
                    xb.add(x);
                    total ^= x;
                }
                bool ok = total == 0 && xb.size() < n - 1;
                assert(ok == brute(a));
            }
        }
    }
    {
        mt19937 rng(0);
        for (int tc = 0; tc < 1000; ++tc) {
            int n = rng() % 14 + 2;
            vector<int> a(n);
            for (int i = 0; i < n; ++i) a[i] = rng() % 16;
            XorBasis<int> xb;
            int total = 0;
            for (int x : a) {
                xb.add(x);
                total ^= x;
            }
            bool ok = total == 0 && xb.size() < n - 1;
            assert(ok == brute(a));
        }
    }
}

int main() {
    self_check();

    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    XorBasis<int> xb;
    int total = 0;
    for (int i = 0; i < n; ++i) {
        int a;
        sc.read(a);
        xb.add(a);
        total ^= a;
    }
    pr.println(total == 0 && xb.size() < n - 1 ? "Yes" : "No");
    return 0;
}
