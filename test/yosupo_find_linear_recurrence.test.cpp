#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/modint.cpp"
#include "../math/berlekamp_massey.cpp"

int main() {
    int n;
    cin >> n;
    vector<mint> a(n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    auto c = berlekamp_massey(a);
    printf("%d\n", (int)c.size());
    for (int i = 0; i < (int)c.size(); ++i) {
        if (i) printf(" ");
        printf("%u", c[i].val);
    }
    puts("");
    return 0;
}
