#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
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
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../math/floor_sum.cpp"

int main() {
    int t;
    cin >> t;
    while(t--) {
        ll n, m, a, b;
        scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
        printf("%lld\n", floor_sum(n, m, a, b));
    }
    return 0;
}