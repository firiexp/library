#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0355"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <chrono>

static const int MOD1 = 1000000861, MOD2 = 1000000933;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include "../string/rolling_hash.cpp"

vector<rolling_hash<MOD1>> hashs1;
vector<rolling_hash<MOD2>> hashs2;

#include "../datastructure/lazysegtree.cpp"

struct Monoid{
    using T = array<ll, 3>;
    using L = char;
    static T f(T a, T b) {
        return {(a[0]*rolling_hash<MOD1>::p()[b[2]]+b[0])%MOD1, (a[1]*rolling_hash<MOD2>::p()[b[2]]+b[1])%MOD2, a[2]+b[2]};
    }
    static T g(T a, L b) {
        if(b == l()) return a;
        else {
            return {hashs1[b-'a'].get(0, a[2]), hashs2[b-'a'].get(0, a[2]), a[2]};
        }
    }
    static L h(L a, L b) {
        if(b == l()) return a; else return b;
    }
    static T e() { return {0, 0, 0}; }
    static L l() { return 0; }
};

int main() {
    int n;
    string s;
    cin >> n >> s;
    for (int i = 'a'; i <= 'z'; ++i) {
        hashs1.emplace_back(string(n, i));
        hashs2.emplace_back(string(n, i));
    }
    LazySegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) {
        seg.set(i, {s[i], s[i], 1});
    }
    seg.build();
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string qq;
        cin >> qq;
        if(qq == "comp"){
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            a--; c--;
            int ok = 0, ng = min(b-a+1, d-c+1);
            while(ng-ok > 1){
                int mid = (ok+ng)/2;
                if(seg.query(a, a+mid) == seg.query(c, c+mid)) ok = mid;
                else ng = mid;
            }
            if(a+ok == b && c+ok == d){
                puts("e");
            }else if(a+ok == b){
                puts("s");
            }else if(c+ok == d){
                puts("t");
            }else if(seg.query(a+ok, a+ng) < seg.query(c+ok, c+ng)){
                puts("s");
            }else {
                puts("t");
            }
        }else {
            int a, b; char c;
            cin >> a >> b >> c;
            a--;
            seg.update(a, b, c);
        }
    }
    return 0;
}