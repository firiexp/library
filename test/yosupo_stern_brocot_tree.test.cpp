#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include <cassert>
#include <utility>
#include <vector>
using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/stern_brocot_tree.cpp"

int main() {
    using namespace SternBrocotTree;

    Scanner sc;
    Printer pr;
    int q;
    sc.read(q);
    while (q--) {
        string op;
        sc.read(op);
        if (op == "ENCODE_PATH") {
            ll a, b;
            sc.read(a, b);
            auto path = encode_path(a, b);
            pr.print((int)path.size());
            for (auto move : path) {
                pr.print(' ');
                pr.print(move.dir == Left ? 'L' : 'R');
                pr.print(' ');
                pr.print(move.steps);
            }
            pr.println();
        } else if (op == "DECODE_PATH") {
            int k;
            sc.read(k);
            vector<Move> path(k);
            for (int i = 0; i < k; ++i) {
                char c;
                ll steps;
                sc.read(c, steps);
                path[i] = {c == 'L' ? Left : Right, steps};
            }
            auto node = decode_path(path);
            pr.println(node.num(), node.den());
        } else if (op == "LCA") {
            ll a, b, c, d;
            sc.read(a, b, c, d);
            auto node = lca(a, b, c, d);
            pr.println(node.num(), node.den());
        } else if (op == "ANCESTOR") {
            ll k, a, b;
            sc.read(k, a, b);
            auto path = encode_path(a, b);
            if (k > depth(path)) {
                pr.println(-1);
                continue;
            }
            auto node = decode_path(ancestor_path(path, k));
            pr.println(node.num(), node.den());
        } else {
            ll a, b;
            sc.read(a, b);
            auto node = range(a, b);
            pr.println(node.p, node.q, node.r, node.s);
        }
    }
    return 0;
}
