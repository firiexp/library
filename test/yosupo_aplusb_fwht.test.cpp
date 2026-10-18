#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../util/modint_base.cpp"
#include "../math/fwht.cpp"

template<class T>
vector<T> direct(const vector<T> &a, const vector<T> &b) {
    int n = 1;
    while (n < (int)a.size() || n < (int)b.size()) n <<= 1;
    vector<T> c(n);
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b.size(); ++j) c[i ^ j] += a[i] * b[j];
    }
    return c;
}

template<class T>
void roundtrip(vector<T> a) {
    auto expected = a;
    int n = 1;
    while (n < (int)a.size()) n <<= 1;
    expected.resize(n);
    fwht(a);
    ifwht(a);
    assert(a == expected);
}

template<class T>
void check(const vector<T> &a, const vector<T> &b) {
    auto saved_a = a, saved_b = b;
    assert(xor_convolution(a, b) == direct(a, b));
    assert(xor_convolution(b, a) == direct(b, a));
    assert(xor_convolution(a, a) == direct(a, a));
    assert(a == saved_a && b == saved_b);
    roundtrip(a);
    roundtrip(b);
}

template<class T>
void check_type() {
    mt19937 random(221);
    for (int n = 0; n <= 12; ++n) {
        for (int m = 0; m <= 12; ++m) {
            vector<T> a(n), b(m);
            for (auto &x : a) x = int(random() % 201) - 100;
            for (auto &x : b) x = int(random() % 201) - 100;
            check(a, b);
        }
    }
    for (int tc = 0; tc < 300; ++tc) {
        vector<T> a(random() % 66), b(random() % 66);
        for (auto &x : a) x = int(random() % 201) - 100;
        for (auto &x : b) x = int(random() % 201) - 100;
        check(a, b);
    }
    vector<T> empty;
    ifwht(empty);
    assert(empty == vector<T>{T(0)});
    vector<T> padded = {8, 4, -4};
    ifwht(padded);
    assert(padded == (vector<T>{2, 0, 4, 2}));
}

void self_check() {
    check_type<ll>();
    check_type<__int128>();
    check_type<modint<3>>();
    check_type<modint<17>>();
    check_type<modint<998244353>>();
    check_type<modint<1000000007>>();
    for (ll big : {numeric_limits<ll>::max() / 2, numeric_limits<ll>::min() / 2}) {
        vector<ll> a(4, big);
        ifwht(a);
        assert(a == (vector<ll>{big, 0, 0, 0}));
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
