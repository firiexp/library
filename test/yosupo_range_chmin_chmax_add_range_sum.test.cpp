#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include <limits>
#include <vector>

using ll = long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/fastio.cpp"
#include "../datastructure/segbeats.cpp"
int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<ll> v(n);
    for (auto &&i : v) sc.read(i);
    SegmentTreeBeats<ll> seg(v);
    while(q--){
        int t;
        sc.read(t);
        if(t == 0){
            int l, r;
            ll b;
            sc.read(l, r, b);
            seg.chmin(l, r, b);
        }else if(t == 1){
            int l, r;
            ll b;
            sc.read(l, r, b);
            seg.chmax(l, r, b);
        }else if(t == 2){
            int l, r;
            ll b;
            sc.read(l, r, b);
            seg.add(l, r, b);
        }else {
            int l, r;
            sc.read(l, r);
            pr.writeln(seg.sum(l, r));
        }
    }
    return 0;
}
