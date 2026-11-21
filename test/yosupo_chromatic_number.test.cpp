#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/chromatic_number.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) in.read(u, v);
    out.println(chromatic_number(n, edges));
}
