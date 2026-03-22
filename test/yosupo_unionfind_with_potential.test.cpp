#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/weightedunionfind.cpp"

struct PotentialGroup {
    struct T {
        int v;

        T(long long x = 0) {
            x %= 998244353;
            if (x < 0) x += 998244353;
            v = (int)x;
        }

        friend bool operator==(const T &lhs, const T &rhs) {
            return lhs.v == rhs.v;
        }
    };

    static T op(T lhs, const T &rhs) {
        lhs.v += rhs.v;
        if (lhs.v >= 998244353) lhs.v -= 998244353;
        return lhs;
    }

    static T inv(T x) {
        if (x.v) x.v = 998244353 - x.v;
        return x;
    }

    static T e() {
        return T(0);
    }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    WeightedUnionFind<PotentialGroup> uf(n);
    while (q--) {
        int t, u, v;
        sc.read(t, u, v);
        if (t == 0) {
            int x;
            sc.read(x);
            PotentialGroup::T w(x);
            if (uf.same(u, v)) {
                pr.println(uf.diff(v, u) == w);
            } else {
                uf.unite(v, u, w);
                pr.println(1);
            }
        } else {
            if (!uf.same(u, v)) pr.println(-1);
            else pr.println(uf.diff(v, u).v);
        }
    }
    return 0;
}
