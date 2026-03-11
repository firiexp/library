#define PROBLEM "https://atcoder.jp/contests/abc127/tasks/abc127_f"

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/slope_trick.cpp"

int main() {
    Scanner in;
    Printer out;

    int q;
    in.read(q);

    SlopeTrick<ll> st;
    while (q--) {
        int t;
        in.read(t);
        if (t == 1) {
            ll a, b;
            in.read(a, b);
            st.add_abs(a);
            st.add_all(b);
        } else {
            auto qu = st.query();
            out.writeln(qu.lx, qu.min_f);
        }
    }
    return 0;
}
