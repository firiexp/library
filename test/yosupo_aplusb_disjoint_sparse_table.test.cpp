#define STANDALONE

#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/disjoint_sparse_table.cpp"

struct Sum {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

struct Concat {
    using T = string;
    static T f(const T &a, const T &b) { return a + b; }
    static T e() { return ""; }
};

template<class Monoid>
void check(const vector<typename Monoid::T> &v, DisjointSparseTable<Monoid> &dst) {
    dst.build(v);
    for (int l = 0; l <= (int)v.size(); ++l) {
        auto expected = Monoid::e();
        for (int r = l; r <= (int)v.size(); ++r) {
            assert(dst.query(l, r) == expected);
            if (r < (int)v.size()) expected = Monoid::f(expected, v[r]);
        }
    }
}

void self_check() {
    DisjointSparseTable<Sum> sum;
    DisjointSparseTable<Concat> concat;
    for (int n = 130; n >= 0; --n) {
        vector<long long> a(n);
        vector<string> b(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i * 37 % 101) - 50;
            b[i] = string(1, char('a' + i % 26));
        }
        check<Sum>(a, sum);
        check<Concat>(b, concat);
    }
}

int main() {
    self_check();
}
