#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0349"
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

#include "../graph/SCC.cpp"

int main() {
    int n;
    cin >> n;
    SCC G(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if(x%n == 0) ans++;
        else G.add_edge(i, (i+x)%n);
    }
    G.build();

    for (auto &&j : G.sz) {
        if(j != 1) ans += j;
    }
    cout << ans << "\n";
    return 0;
}