#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
constexpr int MOD = 1000000007;

#include "../util/fastio.cpp"
#include "../math/fft.cpp"
#include "../math/fastkitamasa.cpp"
#include "fastkitamasa_self_check.cpp"

int main() {
    fastkitamasa_test::self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
