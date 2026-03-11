#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../util/fastio.cpp"
#include "../datastructure/fenwick_tree_2d.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);

    struct Operation {
        int type;
        int x, y, z, w;
        long long add;
    };

    vector<Operation> ops;
    ops.reserve(n + q);
    FenwickTree2D<long long> fw;
    for (int i = 0; i < n; ++i) {
        int x, y;
        long long w;
        sc.read(x, y, w);
        fw.add_point(x, y);
        ops.push_back({0, x, y, 0, 0, w});
    }
    for (int i = 0; i < q; ++i) {
        int t;
        sc.read(t);
        if (t == 0) {
            int x, y;
            long long w;
            sc.read(x, y, w);
            fw.add_point(x, y);
            ops.push_back({0, x, y, 0, 0, w});
        } else {
            int l, d, r, u;
            sc.read(l, d, r, u);
            ops.push_back({1, l, d, r, u, 0});
        }
    }

    fw.build();
    for (auto op : ops) {
        if (op.type == 0) {
            fw.add(op.x, op.y, op.add);
        } else {
            pr.writeln(fw.sum(op.x, op.y, op.z, op.w));
        }
    }
    return 0;
}
