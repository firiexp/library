#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/pow.cpp"

template<class T>
void self_check() {
    for (T m = 1; m <= 200; ++m) {
        for (T a = 0; a <= 100; ++a) {
            T expected = 1 % m;
            for (T n = 0; n <= 30; ++n) {
                assert(pow_(a, n, m) == expected);
                expected = expected * a % m;
            }
        }
    }
}

int main() {
    self_check<long long>();
    self_check<unsigned long long>();
    Scanner sc;
    Printer pr;
    long long a, n;
    sc.read(a, n);
    pr.println(pow_(a, n, 1000000007LL));
}
