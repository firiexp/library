#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334"
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

#include "../graph/bipartite_matching_lexmin.cpp"

int main() {
    int n;
    scanf("%d", &n); n--;
    Bipartite_Matching_LexMin G(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            scanf("%d", &x);
            if(x){
                G.add_edge(j, i);
            }
        }
    }
    auto matching = G.solve_LexMin();
    if(matching != n) {
        puts("no");
        return 0;
    }
    puts("yes");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", G.match[i]-n+1);
    }
    return 0;
}