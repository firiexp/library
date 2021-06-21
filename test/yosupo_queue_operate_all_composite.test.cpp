#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
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

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/modint.cpp"

#include "../datastructure/swag.cpp"

struct SemiGroup {
    using T = pair<mint, mint>;
    static T f(T a, T b) { return {a.first*b.first, a.second*b.first + b.second}; }
    static T e() { return {1, 0}; }
};

int main() {
    int q;
    cin >> q;
    SWAG<SemiGroup> Q;
    while(q--){
        int no; scanf("%d", &no);
        if(no == 0){
            int a, b; scanf("%d %d", &a, &b);
            Q.push(make_pair(mint(a), mint(b)));
        }else if(no == 1){
            Q.pop();
        }else {
            int x; scanf("%d", &x);
            auto ret = Q.fold();
            printf("%d\n", (ret.first*mint(x) + ret.second).val);
        }
    }
    return 0;
}