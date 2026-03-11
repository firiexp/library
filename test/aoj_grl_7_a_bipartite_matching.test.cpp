#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A"

#include <utility>
#include <vector>

using namespace std;

#include "../util/fastio.cpp"
#include "../graph/bipartite_matching.cpp"

int main() {
    Scanner in;
    Printer out;

    int l, r, m;
    in.read(l, r, m);
    Bipartite_Matching bm(l, r);
    for (int i = 0; i < m; ++i) {
        int a, b;
        in.read(a, b);
        bm.add_edge(a, b);
    }

    out.writeln(bm.matching());
    return 0;
}
