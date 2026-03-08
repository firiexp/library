#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B"

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/topological_sort.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        sc.read(a, b);
        g[a].push_back(b);
    }
    auto ord = topological_sort(g);
    for (auto &&x : ord) pr.writeln(x);
    return 0;
}
