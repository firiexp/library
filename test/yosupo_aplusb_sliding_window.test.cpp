#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/slidingwindow.cpp"

template<class T>
void check() {
    mt19937 rng(59);
    vector<T> values(400);
    for (int i = 0; i < int(values.size()); ++i) values[i] = T(rng() % 17);
    const auto initial = values;
    for (bool maximum : {false, true}) {
        values = initial;
        auto cmp = [=](T a, T b) { return maximum ? a > b : a < b; };
        sliding_window<T, decltype(cmp)> sw(values, cmp);
        static_assert(is_same_v<decltype(sw.get_index()), int>);
        static_assert(is_same_v<decltype(sw.value()), T>);
        auto verify = [&](int width) {
            assert(sw.l == 0 && sw.r == 0);
            assert(sw.get_index() == 0 && sw.value() == T(0));
            for (int r = 1; r <= int(values.size()); ++r) {
                sw.slideR();
                if (sw.r - sw.l > width) sw.slideL();
                int best = sw.l;
                for (int i = sw.l + 1; i < sw.r; ++i)
                    if (!cmp(values[best], values[i])) best = i;
                assert(sw.get_index() == best);
                assert(sw.value() == values[best]);
            }
            while (sw.l < sw.r) sw.slideL();
            assert(sw.get_index() == 0 && sw.value() == T(0));
        };
        for (int width : {1, 7, 65}) {
            sw.reset();
            verify(width);
        }
        reverse(values.begin(), values.end());
        sw.set(values);
        verify(23);
        values.assign(33001, T(1));
        values.back() = T(0);
        sw.set(values);
        verify(1);
        values.resize(400);
    }
}

int main() {
    check<unsigned char>();
    check<signed char>();
    check<short>();
    check<bool>();
    check<int>();
    check<long long>();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
