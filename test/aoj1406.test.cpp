#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1406"
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
using ll = long long;
using namespace std;

const int INF = 1000000000;

#include "../datastructure/radixheap.cpp"
int main() {
    int n;
    cin >> n;
    vector<int> val(n), len(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        len[i] = s.size();
        reverse(s.begin(), s.end());
        while(!s.empty()){
            val[i] *= 2;
            val[i] += s.back()-'0';
            s.pop_back();
        }
    }
    vector<vector<int>> dp(17);
    for (int i = 1; i <= 16; ++i) {
        dp[i].resize(1<<i);
        fill(dp[i].begin(), dp[i].end(), INF);
    }
    RadixHeap<int, int> Q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i == j) continue;
            if(len[i] < len[j] && ((val[j] >> (len[j]-len[i])) == val[i])){
                dp[len[j]-len[i]][(val[j] & ((1 << (len[j]-len[i]))-1))] = min(dp[len[j]-len[i]][(val[j] & (1 << (len[j]-len[i])-1))], len[j]);
            }else continue;
        }
    }
    for (int i = 1; i <= 16; ++i) {
        for (int j = 0; j < 1<<i; ++j) {
            if(dp[i][j] != INF){
                Q.emplace(i + (j << 5), dp[i][j]);
            }
        }
    }
    auto f = [&](int i, int j){
        return i + (j << 5);
    };
    int ans = INF;
    while(!Q.empty()){
        int a, b; tie(a, b) = Q.top(); Q.pop();
        int p = a & 31, q = a >> 5;
        if(dp[p][q] < b) continue;
        for (int i = 0; i < n; ++i) {
            if(len[i] < p) {
                if(val[i] == (q >> (p-len[i]))){
                    if(dp[p-len[i]][(q & ((1 << (p-len[i]))-1))] > b){
                        dp[p-len[i]][(q & ((1 << (p-len[i]))-1))] = b;
                        Q.emplace(f(p-len[i], (q & ((1 << (p-len[i]))-1))), b);
                    }
                }
            }else if(len[i] == p){
                if(val[i] == q){
                    ans = min(ans, b);
                }
            }else {
                if((val[i] >> (len[i]-p)) == q){
                    if(dp[len[i]-p][(val[i] & ((1 << (len[i]-p))-1))] > b+len[i]-p){
                        dp[len[i]-p][(val[i] & ((1 << (len[i]-p))-1))] = b+len[i]-p;
                        Q.emplace(f(len[i]-p, (val[i] & ((1 << (len[i]-p))-1))), b+len[i]-p);
                    }
                }
            }
        }
    }
    if(ans < INF) cout << ans << "\n";
    else puts("0");
    return 0;
}
