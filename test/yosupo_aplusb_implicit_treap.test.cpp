#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/implicit_treap.cpp"

struct StringXor {
    using T = string;
    using L = unsigned char;
    static T f(const T &a, const T &b) { return a + b; }
    static T g(T a, L x) {
        for (char &c : a) c ^= x;
        return a;
    }
    static L h(L a, L b) { return a ^ b; }
    static T e() { return ""; }
    static L l() { return 0; }
};

void check() {
    mt19937 rng(25);
    for (int tc = 0; tc < 400; ++tc) {
        string expected(rng() % 50, '\0');
        for (char &c : expected) c = rng() % 128;
        vector<string> init;
        for (char c : expected) init.emplace_back(1, c);
        ImplicitTreap<StringXor> tr(init);
        for (int step = 0; step < 1000; ++step) {
            int n = expected.size();
            int op = rng() % 7;
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            char c = rng() % 128;
            if (op == 0 && n < 100) {
                tr.insert(l, string(1, c));
                expected.insert(expected.begin() + l, c);
            } else if (op == 1 && n) {
                int k = rng() % n;
                assert(tr.erase(k) == expected.substr(k, 1));
                expected.erase(k, 1);
            } else if (op == 2 && n) {
                int k = rng() % n;
                assert(tr.get(k) == expected.substr(k, 1));
            } else if (op == 3 && n) {
                int k = rng() % n;
                tr.set(k, string(1, c));
                expected[k] = c;
            } else if (op == 4) {
                tr.reverse(l, r);
                reverse(expected.begin() + l, expected.begin() + r);
            } else if (op == 5) {
                tr.apply(l, r, c);
                for (int i = l; i < r; ++i) expected[i] ^= c;
            } else {
                assert(tr.fold(l, r) == expected.substr(l, r - l));
            }
            assert(tr.size() == (int)expected.size());
            assert(tr.empty() == expected.empty());
            assert(tr.all_fold() == expected);
            assert(tr.fold(0, tr.size()) == expected);
            assert(tr.fold(tr.size(), tr.size()).empty());
            if (step % 100 == 0) {
                tr.reverse(0, tr.size());
                tr.apply(0, tr.size(), 37);
                reverse(expected.begin(), expected.end());
                for (char &x : expected) x ^= 37;
                for (int k = 0; k < tr.size(); ++k) {
                    assert(tr.get(k) == expected.substr(k, 1));
                    assert(tr.fold(k, tr.size()) == expected.substr(k));
                }
            }
        }
        while (!expected.empty()) {
            assert(tr.pop_back() == expected.substr(expected.size() - 1));
            expected.pop_back();
        }
        assert(tr.fold(0, 0).empty());
        tr.push_front("a");
        tr.set(0, "b");
        assert(tr.pop_front() == "b");
    }
}

int main() {
    check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
