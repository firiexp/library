#define PROBLEM "https://judge.yosupo.jp/problem/many_factorials"

#include <algorithm>
#include <cassert>
#include <vector>
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/many_factorials.cpp"

int main() {
    Scanner in;
    Printer out;
    int n;
    in.read(n);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) in.read(a[i]);
    vector<mint> ans = many_factorials(a);
    for (int i = 0; i < n; ++i) out.println(ans[i].val);
    return 0;
}
