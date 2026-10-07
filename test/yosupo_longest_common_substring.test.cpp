#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_automaton.cpp"

int main() {
    Scanner sc;
    Printer pr;
    string s, t;
    sc.read(s, t);
    SuffixAutomaton<26> sam(s);
    auto match = sam.longest_common_substring(t);
    pr.print(match.s_l);
    pr.print(' ');
    pr.print(match.s_r);
    pr.print(' ');
    pr.print(match.t_l);
    pr.print(' ');
    pr.println(match.t_r);
}
