#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../math/ntt.cpp"

int main() {
    int n;
    cin >> n;
    poly f(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        f[i] = x;
    }
    poly g = f.exp(n);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << g[i].val;
    }
    cout << '\n';
    return 0;
}
