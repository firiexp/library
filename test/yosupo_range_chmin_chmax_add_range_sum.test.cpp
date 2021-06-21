#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
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

#include "../datastructure/segbeats.cpp"
int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (auto &&i : v) scanf("%lld", &i);
    SegmentTreeBeats seg(v);
    while(q--){
        int t; scanf("%d", &t);
        if(t == 0){
            int l, r; ll b;
            scanf("%d %d %lld", &l, &r, &b);
            seg.chmin(l, r, b);
        }else if(t == 1){
            int l, r; ll b;
            scanf("%d %d %lld", &l, &r, &b);
            seg.chmax(l, r, b);
        }else if(t == 2){
            int l, r; ll b;
            scanf("%d %d %lld", &l, &r, &b);
            seg.add(l, r, b);
        }else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", seg.sum(l, r));
        }
    }
    return 0;
}