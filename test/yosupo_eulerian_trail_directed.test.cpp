#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

#include <algorithm>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/eulerian_trail.cpp"

int main() {
    Scanner in;
    Printer out;
    int t;
    in.read(t);
    while (t--) {
        int n, m;
        in.read(n, m);
        EulerianTrail<true> g(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            in.read(a, b);
            g.add_edge(a, b);
        }
        auto res = g.solve();
        if (!res.exists) {
            out.writeln("No");
            continue;
        }
        out.writeln("Yes");
        for (int i = 0; i < (int)res.vertices.size(); ++i) {
            if (i) out.write(' ');
            out.write(res.vertices[i]);
        }
        out.writeln();
        for (int i = 0; i < (int)res.edge_ids.size(); ++i) {
            if (i) out.write(' ');
            out.write(res.edge_ids[i]);
        }
        out.writeln();
    }
    return 0;
}
