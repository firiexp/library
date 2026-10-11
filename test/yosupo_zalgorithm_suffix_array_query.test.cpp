#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_array_query.cpp"

int main() {
    Scanner sc;
    Printer pr;
    string s;
    sc.read(s);
    const SuffixArrayQuery q(s);
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i) pr.print(' ');
        pr.print(q.lce(0, i));
    }
    pr.println();
}
