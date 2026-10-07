#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/lis.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    vector<int> a(n);
    sc.read(a);
    auto indices = lis_indices(a);
    pr.println(indices.size());
    for (int i = 0; i < (int)indices.size(); ++i) {
        if (i) pr.print(' ');
        pr.print(indices[i]);
    }
    pr.println();
}
