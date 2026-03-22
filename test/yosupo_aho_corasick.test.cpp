#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include <array>
#include <string>
#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/ahocorasick.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    AhoCorasick<26, 'a'> aho;
    vector<int> parent(1, -1), terminal(n);
    for (int i = 0; i < n; ++i) {
        string s;
        sc.read(s);
        int cur = 0;
        for (char c : s) {
            int to = aho.v[cur].to[c - 'a'];
            if (!to) {
                aho.v[cur].to[c - 'a'] = aho.v.size();
                aho.v.emplace_back();
                parent.push_back(cur);
                to = (int)aho.v.size() - 1;
            }
            cur = to;
        }
        terminal[i] = cur;
    }
    aho.build();

    pr.println((int)aho.v.size());
    for (int v = 1; v < (int)aho.v.size(); ++v) {
        pr.print(parent[v]);
        pr.print(' ');
        pr.println(aho.v[v].fail);
    }
    for (int i = 0; i < n; ++i) {
        pr.print(terminal[i]);
        pr.print(i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
