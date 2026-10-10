#define PROBLEM "https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/xor_basis.cpp"

int main() {
    Scanner in;
    Printer out;
    int t;
    in.read(t);
    while (t--) {
        XorBasis<unsigned> a, b;
        for (auto *space : {&a, &b}) {
            int n;
            in.read(n);
            for (int i = 0; i < n; ++i) {
                unsigned x;
                in.read(x);
                space->add(x);
            }
        }
        auto common = a.intersection(b);
        out.print(common.size());
        for (auto x : common.basis) {
            if (x != 0) {
                out.print(' ');
                out.print(x);
            }
        }
        out.println();
    }
}
