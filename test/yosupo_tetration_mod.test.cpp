#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../math/tetration.cpp"
int main() {
    int t;
    cin >> t;
    while(t--){
        int a, b, m;
        scanf("%d %d %d", &a, &b, &m);
        printf("%lld\n", tetration(a, b, m));
    }
    return 0;
}