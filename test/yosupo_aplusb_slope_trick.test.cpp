#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/slope_trick.cpp"

template<class T>
void verify(const SlopeTrick<T> &st, T x) {
    using Wide = conditional_t<is_integral<T>::value, __int128, long double>;
    Wide expected = st.min_f;
    auto l = st.L;
    auto r = st.R;
    while (!l.empty()) {
        expected += max<Wide>(0, Wide(l.top()) + st.add_l - x);
        l.pop();
    }
    while (!r.empty()) {
        expected += max<Wide>(0, Wide(x) - r.top() - st.add_r);
        r.pop();
    }
    if constexpr (is_integral<T>::value) assert(st.eval(x) == expected);
    else assert(fabsl(st.eval(x) - expected) <= 1e-9L);
}

template<class T>
void random_check() {
    mt19937 rng(117);
    for (int tc = 0; tc < 1000; ++tc) {
        SlopeTrick<T> st;
        verify(st, T(0));
        for (int step = 0; step < 200; ++step) {
            T a = T((int(rng() % 101) - 50) * 0.5);
            switch (rng() % 10) {
                case 0: st.add_abs(a); break;
                case 1: st.add_a_minus_x(a); break;
                case 2: st.add_x_minus_a(a); break;
                case 3: st.add_all(a); break;
                case 4: st.shift(a); break;
                case 5: st.shift(a, a + int(rng() % 11)); break;
                case 6: st.clear_left(); break;
                case 7: st.clear_right(); break;
                case 8: {
                    SlopeTrick<T> other;
                    for (int i = 0; i < 8; ++i) other.add_abs(T(int(rng() % 101) - 50));
                    other.shift(-3, 7);
                    verify(other, a);
                    st.merge(other);
                    verify(other, a);
                    break;
                }
                default: break;
            }
            for (int i = 0; i < 5; ++i) verify(st, T(int(rng() % 1001) - 500));
        }
    }
}

void cache_check() {
    SlopeTrick<long long> st;
    st.add_abs(-4);
    st.add_abs(7);
    verify(st, 0LL);
    auto l = st.eval_l, r = st.eval_r;
    for (int i = 0; i < 100; ++i) {
        st.shift(-1, 2);
        st.add_all(-3);
        assert(st.eval_cache_valid);
        verify(st, (long long)i);
        assert(st.eval_l == l && st.eval_r == r);
    }
    SlopeTrick<double> real_st;
    real_st.add_abs(0.25);
    verify(real_st, 0.5);
    real_st.shift(-0.5, 1.25);
    assert(!real_st.eval_cache_valid);
    verify(real_st, 0.75);
    for (long long offset : {-9000000000000000000LL, 9000000000000000000LL}) {
        for (int n = 1; n <= 4; ++n) {
            SlopeTrick<long long> huge;
            huge.shift(offset);
            for (int i = 0; i < n; ++i) huge.add_abs(0);
            verify(huge, 0LL);
            verify(huge, -1000000000000000000LL);
            verify(huge, 1000000000000000000LL);
            huge.shift(-1, 1);
            verify(huge, 0LL);
            verify(huge, -1000000000000000000LL);
            verify(huge, 1000000000000000000LL);
        }
    }
}

int main() {
    random_check<long long>();
    random_check<int>();
    random_check<double>();
    cache_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
