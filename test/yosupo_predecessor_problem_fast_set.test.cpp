#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/fast_set.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    string bits;
    in.read(n, q, bits);
    vector<bool> present(n);
    for (int i = 0; i < n; ++i) present[i] = bits[i] == '1';
    FastSet s(present);
    while (q--) {
        int type, x;
        in.read(type, x);
        if (type == 0) s.insert(x);
        else if (type == 1) s.erase(x);
        else if (type == 2) out.println(int(s.contains(x)));
        else if (type == 3) out.println(s.next(x));
        else out.println(s.prev(x));
    }
}
