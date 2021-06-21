#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0294"
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

#include "../graph/dominatortree.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    DominatorTree G(n);
    for (int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        s--; t--;
        G.add_edge(s, t);
    }
    G.build(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        x--;
        if(!G.idom[x]) printf("%d\n", x+1);
        else printf("%d\n", G.idom[x]+1);
    }
    return 0;
}