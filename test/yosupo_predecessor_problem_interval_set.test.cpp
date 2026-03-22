#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/interval_set.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    string t;
    sc.read(n, q, t);

    IntervalSet<int, int> st;
    for (int i = 0; i < n; ++i) {
        if (t[i] == '1') st.insert(i, i + 1);
    }

    while (q--) {
        int c, k;
        sc.read(c, k);
        if (c == 0) {
            st.insert(k, k + 1);
        } else if (c == 1) {
            st.erase(k, k + 1);
        } else if (c == 2) {
            pr.println(st.contains(k) ? 1 : 0);
        } else if (c == 3) {
            auto seg = st.next_interval(k);
            if (seg.l == -1) pr.println(-1);
            else pr.println(max(k, seg.l));
        } else {
            auto seg = st.prev_interval(k);
            if (seg.l == -1) pr.println(-1);
            else pr.println(min(k, seg.r - 1));
        }
    }
    return 0;
}
