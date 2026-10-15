#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/pow.cpp"

template<class T>
void self_check() {
    for (T m = 1; m <= 200; ++m) {
        T first = 0;
        if constexpr (is_signed_v<T>) first = -100;
        for (T a = first; a <= 100; ++a) {
            T expected = 1 % m;
            for (T n = 0; n <= 30; ++n) {
                assert(pow_(a, n, m) == expected);
                expected = expected * a % m;
                if constexpr (is_signed_v<T>) {
                    if (expected < 0) expected += m;
                }
            }
        }
    }
    vector<T> bases = {0, 1, 2, numeric_limits<T>::max()};
    if constexpr (is_signed_v<T>) {
        bases.push_back(-1);
        bases.push_back(-2);
        bases.push_back(numeric_limits<T>::min());
    }
    vector<T> moduli = {1, 2, 5, 998244353, numeric_limits<T>::max()};
    for (T a : bases) for (T m : moduli) {
        T expected = 1 % m;
        for (T n = 0; n <= 64; ++n) {
            assert(pow_(a, n, m) == expected);
            if constexpr (is_signed_v<T>) {
                __int128 next = (__int128)expected * a % m;
                expected = static_cast<T>(next < 0 ? next + m : next);
            } else {
                expected = (unsigned __int128)expected * a % m;
            }
        }
    }
}

int main() {
    self_check<long long>();
    self_check<unsigned long long>();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
