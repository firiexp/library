#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <bits/stdc++.h>

using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/binarytrie.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int q;
    sc.read(q);
    Binarytrie<unsigned int, 30> trie;
    while (q--) {
        int t;
        unsigned int x;
        sc.read(t, x);
        if (t == 0) {
            if (!trie.contains(x)) trie.add(x);
        } else if (t == 1) {
            trie.erase(x);
        } else {
            pr.writeln(trie.xor_min(x));
        }
    }
    return 0;
}
