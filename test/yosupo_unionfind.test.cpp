#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = uint32_t;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../datastructure/unionfind.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        scanf("%d %d %d", &t, &u, &v);
        if(t) printf("%d\n", uf.same(u, v));
        else uf.unite(u, v);
    }
    return 0;
}