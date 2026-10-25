#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../string/lex_trie.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    LexTrie trie(n);
    for (int v = 1; v < n; ++v) {
        int p;
        sc.read(p);
        int id = trie.append(p, v);
        assert(id == v);
        (void)id;
    }
    while (q--) {
        int a, b;
        sc.read(a, b);
        pr.println(trie.lca(a, b));
    }
}
