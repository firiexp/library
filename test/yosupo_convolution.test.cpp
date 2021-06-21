#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"


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
    int n, m;
    cin >> n >> m;
    poly a(n), b(m);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        b[i] = x;
    }
    a *= b;
    for (int i = 0; i < n+m-1; ++i) {
        if(i) printf(" ");
        printf("%d", a[i].val);
    }
    puts("");
    return 0;
}