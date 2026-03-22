#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0334"

#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/bipartite_matching_lexmin.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    n--;
    Bipartite_Matching_LexMin G(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            sc.read(x);
            if (x) {
                G.add_edge(j, i);
            }
        }
    }
    auto matching = G.solve_LexMin();
    if (matching != n) {
        pr.println("no");
        return 0;
    }
    pr.println("yes");
    for (int i = 0; i < n; ++i) {
        pr.println(G.match[i] - n + 1);
    }
    return 0;
}
