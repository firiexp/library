#define PROBLEM "https://judge.yosupo.jp/problem/wildcard_pattern_matching"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/wildcard_pattern_matching.cpp"

int main() {
    Scanner sc;
    Printer pr;
    string s, t;
    sc.read(s, t);
    for (int matched : wildcard_pattern_matching(s, t)) pr.print((char)('0' + matched));
    pr.println();
}
