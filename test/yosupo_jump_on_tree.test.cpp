#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <algorithm>
#include <queue>
#include <random>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/jump_on_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    JumpOnTree jt(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        sc.read(u, v);
        jt.add_edge(u, v);
    }
    jt.build(0);
    while (q--) {
        int s, t, k;
        sc.read(s, t, k);
        pr.writeln(jt.jump(s, t, k));
    }
    return 0;
}
