#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/undoable_li_chao_tree.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<pair<long long, long long>> initial(n);
    for (auto &[a, b] : initial) in.read(a, b);
    vector<array<long long, 3>> queries(q);
    vector<long long> xs;
    for (auto &query : queries) {
        in.read(query[0], query[1]);
        if (query[0] == 0) in.read(query[2]);
        else xs.push_back(query[1]);
    }
    UndoableLiChaoTree<long long> tree(move(xs));
    int id = 0;
    for (auto [a, b] : initial) tree.add_line(a, b, id++);
    for (auto [type, a, b] : queries) {
        if (type == 0) tree.add_line(a, b, id++);
        else out.println(tree.query_with_id(a).first);
    }
}
