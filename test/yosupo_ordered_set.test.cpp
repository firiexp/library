#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include <cassert>
#include <cstdint>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/order_statistic_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);

    OrderStatisticTree<int> st;
    st.reserve(n + q);
    for (int i = 0; i < n; ++i) {
        int a;
        sc.read(a);
        st.insert(a);
    }

    for (int i = 0; i < q; ++i) {
        int t, x;
        sc.read(t, x);
        if (t == 0) {
            if (!st.contains(x)) st.insert(x);
        } else if (t == 1) {
            st.erase_one(x);
        } else if (t == 2) {
            if (st.size() < x) pr.println(-1);
            else pr.println(st.find_by_order(x - 1));
        } else if (t == 3) {
            pr.println(st.order_of_key(x + 1));
        } else if (t == 4) {
            int k = st.order_of_key(x + 1);
            if (k == 0) pr.println(-1);
            else pr.println(st.find_by_order(k - 1));
        } else {
            int k = st.order_of_key(x);
            if (k == st.size()) pr.println(-1);
            else pr.println(st.find_by_order(k));
        }
    }
    return 0;
}
