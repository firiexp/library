#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2257"
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

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/modint.cpp"
#include "../datastructure/ahocorasick.cpp"

mint dp[32][501][601][2];
int to[601][501];
int to2[601][501];
int dp0[601];
void solve(int n, int m, int K){
    vector<string> words;
    vector<vector<int>> G;
    fill(dp0, dp0+601, 0);
    vector<string> kigo(K);
    int sz = 0;
    {
        int cur = 0;
        map<string, int> exist;
        for (int i = 0; i < n; ++i) {
            string s, t;
            cin >> s >> t;
            if(!exist.count(s)) {
                exist[s] = cur++;
                words.emplace_back(s);
                G.emplace_back();
            }
            if(!exist.count(t)){
                exist[t] = cur++;
                words.emplace_back(t);
                G.emplace_back();
            }
            G[exist[s]].emplace_back(exist[t]);
        }
        n = words.size();
        AhoCorasick<26, 'a'> aho;
        for (int i = 0; i < K; ++i) {
            cin >> kigo[i];
            dp0[aho.add(kigo[i])]++;
        }
        aho.build();
        for (auto &&i : aho.ord) if(i) dp0[i] += dp0[aho.v[i].fail];
        sz = aho.v.size();
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < n; ++j) {
                to[i][j] = i;
                to2[i][j] = 0;
                for (auto &&c : words[j]) {
                    to[i][j] = aho.next(to[i][j], c);
                    to2[i][j] += dp0[to[i][j]];
                }
            }
        }
    }
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < sz; ++k) {
                for (int l = 0; l < 2; ++l) {
                    dp[i][j][k][l] = 0;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if(to2[0][i] < 2) dp[words[i].size()&31][i][to[0][i]][to2[0][i]] += mint(1);
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < sz; ++k) {
                for (int l = 0; l < 2; ++l) {
                    dp[(i+22)&31][j][k][l] = 0;
                }
            }
        }
        for (int o = 0; o < n; ++o) {
            for (auto &&j : G[o]) {
                if(i+words[j].size() > m) continue;
                int now = i&31, next = (now+words[j].size())&31;
                for (int k = 0; k < sz; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        if(l + to2[k][j] >= 2) continue;
                        dp[next][j][to[k][j]][l+to2[k][j]] += dp[now][o][k][l];
                    }
                }
            }
        }
    }
    mint ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz; ++j) {
            ans += dp[m&31][i][j][1];
        }
    }
    cout << ans.val << "\n";
}

int main() {
    int n, m, k;
    while(cin >> n >> m >> k, n){
        solve(n, m, k);
    }
    return 0;
}