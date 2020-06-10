#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

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

#include "../graph/dominatortree.cpp"

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    DominatorTree G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    G.build(s);
    for (int i = 0; i < n; ++i) {
        if(i) printf(" ");
        printf("%d", (i == s ? s : G.idom[i]));
    }
    puts("");
    return 0;
}