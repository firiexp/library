#define PROBLEM "https://yukicoder.me/problems/no/2867"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;

#include "../math/modular/modint.cpp"
#include "../util/fastio.cpp"
#include "../math/digit_dp.cpp"
#include "../string/avoid_patterns.cpp"

int main() {
    Scanner sc;
    Printer pr;
    string n;
    sc.read(n);
    auto a = avoid_patterns<10, '0'>({"404"});
    pr.println(digit_count<mint>("1", n, a).val);
}
