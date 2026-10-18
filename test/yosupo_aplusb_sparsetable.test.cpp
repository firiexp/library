#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/sparsetable.cpp"

struct Min {
    using T = int;
    static T f(T a, T b) { return min(a, b); }
};

struct Max {
    using T = int;
    static T f(T a, T b) { return max(a, b); }
};

struct Gcd {
    using T = int;
    static T f(T a, T b) { return gcd(a, b); }
};

template<class F>
void check() {
    mt19937 rng(202);
    vector<int> sizes;
    for(int n = 0; n <= 129; ++n) sizes.push_back(n);
    for(int n : {255, 256, 257, 1, 0, 17, 0}) sizes.push_back(n);
    SparseTable<F> table;
    for(int n : sizes) {
        vector<int> a(n);
        for(auto &x : a) x = rng() % 1000;
        table.build(a);
        const auto &view = table;
        for(int l = 0; l < n; ++l) {
            int value = a[l];
            for(int r = l + 1; r <= n; ++r) {
                value = F::f(value, a[r - 1]);
                assert(view.query(l, r) == value);
            }
        }
    }
}

int main() {
    check<Min>();
    check<Max>();
    check<Gcd>();
}
