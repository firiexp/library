#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;

#include "../math/convolution/lcm_transform.cpp"
#include "../math/convolution/gcd_transform.cpp"
#include "../math/modular/modint.cpp"

template<class T>
void check_transform(vector<T> a) {
    auto original = a;
    vector<T> expected(a.size());
    if (!a.empty()) expected[0] = a[0];
    for (int i = 1; i < (int)a.size(); ++i) {
        for (int j = i; j < (int)a.size(); j += i) expected[j] += a[i];
    }
    lcm_transform(a);
    assert(a == expected);
    lcm_itransform(a);
    assert(a == original);
    lcm_itransform(a);
    lcm_transform(a);
    assert(a == original);
}

template<class T>
void check(const vector<T>& a, const vector<T>& b, int limit) {
    vector<T> expected(limit + 1);
    for (int i = 1; i < (int)a.size(); ++i) {
        for (int j = 1; j < (int)b.size(); ++j) {
            int k = lcm(i, j);
            if (k <= limit) expected[k] += a[i] * b[j];
        }
    }
    assert(lcm_convolution(a, b, limit) == expected);
    assert(lcm_convolution(b, a, limit) == expected);
    check_transform(a);
    check_transform(b);
}

int main() {
    for (int limit : {0, 1, 2, 3, 5, 6, 12, 64, 100}) {
        check<ll>({}, {}, limit);
        check<ll>({123}, {456}, limit);
        check<ll>({}, {9, 2, -3}, limit);
        check<ll>({99, 0, 2}, {-99, 0, 0, 3}, limit);
        check<ll>({99, -2}, {-99, 3}, limit);
    }
    assert(lcm_convolution(vector<ll>{99, 0, 2}, vector<ll>{-99, 0, 0, 3}, 6)[6] == 6);
    mt19937 rng(395);
    for (int trial = 0; trial < 1500; ++trial) {
        vector<ll> a(rng() % 100), b(rng() % 100);
        for (auto& x : a) x = (int)(rng() % 21) - 10;
        for (auto& x : b) x = (int)(rng() % 21) - 10;
        int limit = rng() % 150;
        check(a, b, limit);
        check(vector<mint>(a.begin(), a.end()), vector<mint>(b.begin(), b.end()), limit);
    }
}
