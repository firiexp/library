#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0396"
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

#include "../flow/dinic.cpp"
int main() {
    int w, h;
    cin >> w >> h;
    vector<int> a(h), b(w);
    int S = 0, T = 0;
    for (auto &&i : b) scanf("%d", &i), T += i;
    for (auto &&i : a) scanf("%d", &i), S += i;
    if(S != T) {
        puts("0");
        return 0;
    }
    Dinic<int, true> G(h+w+2);
    for (int i = 0; i < h; ++i) {
        G.add_edge(0, i+1, a[i]);
    }
    for (int i = 0; i < w; ++i) {
        G.add_edge(h+i+1, h+w+1, b[i]);
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            G.add_edge(i+1, h+j+1, 1);
        }
    }
    if(S != G.flow(0, h+w+1)) puts("0");
    else puts("1");
    return 0;
}