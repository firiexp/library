#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
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

#include "../graph/twosat.cpp"

int main() {
    string s, t;
    int n, m;
    cin >> s >> t >> n >> m;
    TwoSAT G(n);
    for (int i = 0; i < m; ++i) {
        int a, b; char x;
        scanf(" %d %d %c", &a, &b, &x);
        if(a < 0) a = n-a;
        if(b < 0) b = n-b;
        G.add_or(a-1, b-1);
    }
    auto ans = G.build();
    if(ans.empty()){
        puts("s UNSATISFIABLE");
    }else {
        puts("s SATISFIABLE");
        printf("v ");
        for (int i = 0; i < ans.size(); ++i) {
            if(ans[i]) printf("%d ", i+1);
            else printf("%d ", -(i+1));
        }
        puts("0");
    }
    return 0;
}