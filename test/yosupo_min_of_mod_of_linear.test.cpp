#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/min_of_mod_of_linear.cpp"

int main() {
    Scanner in;
    Printer out;
    int t;
    in.read(t);
    while (t--) {
        ll n, m, a, b;
        in.read(n, m, a, b);
        out.println(min_of_mod_of_linear(n, m, a, b));
    }
}
