#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_array_query.cpp"

int main() {
    Scanner sc;
    Printer pr;
    string s;
    sc.read(s);
    int n = (int)s.size();
    const SuffixArrayQuery q(s);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return q.compare(i, n, j, n) < 0; });
    for (int i = 0; i < n; ++i) {
        if (i) pr.print(' ');
        pr.print(order[i]);
    }
    pr.println();
}
