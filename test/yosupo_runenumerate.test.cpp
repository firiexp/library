#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/enumerate_runs.cpp"

int main() {
    Scanner sc;
    Printer pr;
    string s;
    sc.read(s);
    auto runs = enumerate_runs(s);
    pr.println(runs.size());
    for (auto [period, l, r] : runs) pr.println(period, l, r);
}
