#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/fast_set.cpp"

void self_check() {
    mt19937 rng(101);
    for (int n : {0, 1, 2, 63, 64, 65, 127, 128, 129, 4095, 4096, 4097, 262145}) {
        for (int mode = 0; mode < 3; ++mode) {
            vector<bool> present(n);
            set<int> expected;
            for (int i = 0; i < n; ++i) {
                present[i] = mode == 1 || (mode == 2 && rng() % 17 == 0);
                if (present[i]) expected.insert(i);
            }
            FastSet s(present), built(n);
            for (int x : expected) built.insert(x);
            assert(s.next(n) == -1 && s.prev(-1) == -1);
            for (int i = 0; i < n; ++i) assert(s.contains(i) == built.contains(i));
            for (int op = 0; op < 10000; ++op) {
                int x = rng() % (n + 1);
                auto next = expected.lower_bound(x);
                assert(s.next(x) == (next == expected.end() ? -1 : *next));
                int y = x - 1;
                auto prev = expected.upper_bound(y);
                assert(s.prev(y) == (prev == expected.begin() ? -1 : *--prev));
                if (x == n) continue;
                assert(s.contains(x) == bool(expected.count(x)));
                if (rng() & 1) {
                    s.insert(x);
                    s.insert(x);
                    expected.insert(x);
                } else {
                    s.erase(x);
                    s.erase(x);
                    expected.erase(x);
                }
            }
            for (int x : expected) s.erase(x);
            assert(s.next(0) == -1 && s.prev(n - 1) == -1);
        }
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
