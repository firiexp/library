#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

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

#include "../datastructure/binaryindexedtree.cpp"
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (auto &&i : v) scanf("%d", &i);
    BIT<ll> S(n);
    for (int i = 0; i < n; ++i) S.add(i, v[i]);

    for (int i = 0; i < q; ++i) {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        if(c == 0) S.add(x, y);
        else printf("%lld\n", S.sum(y) - S.sum(x));
    }
    return 0;
}