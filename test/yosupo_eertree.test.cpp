#define PROBLEM "https://judge.yosupo.jp/problem/eertree"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../string/palindromic_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;

    string s;
    char c = sc.skip();
    while (true) {
        s.push_back(c);
        sc.ensure();
        if (sc.buf[sc.idx] <= ' ') break;
        c = sc.buf[sc.idx++];
    }

    PalindromicTree<26> pt(s);
    int n = pt.nodes.size();
    vector<int> parent(n, -1);
    for (int v = 0; v < n; ++v) {
        for (int c = 0; c < 26; ++c) {
            int u = pt.nodes[v].next[c];
            if (u != -1) parent[u] = v;
        }
    }

    pr.writeln(n - 2);
    for (int v = 2; v < n; ++v) {
        pr.writeln(parent[v] - 1, pt.nodes[v].link - 1);
    }
    for (int i = 0; i < (int)pt.path.size(); ++i) {
        if (i) pr.write(' ');
        pr.write(pt.path[i] - 1);
    }
    pr.writeln();
    return 0;
}
