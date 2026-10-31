#define STANDALONE

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
void verify_add_abs(SlopeTrick<T> &st, T a) {
    verify(st, a);
    auto reference = st;
    reference.add_a_minus_x(a);
    reference.add_x_minus_a(a);
    st.add_abs(a);
    assert(!st.eval_cache_valid);
    auto actual = st.query(), expected = reference.query();
    assert(actual.lx == expected.lx && actual.rx == expected.rx && actual.min_f == expected.min_f);
    assert(st.L.size() == reference.L.size() && st.R.size() == reference.R.size());
    for (int dx : {-20, -1, 0, 1, 20}) {
        T x = a + T(dx);
        assert(st.eval(x) == reference.eval(x));
        verify(st, x);
    }
}

template<class T>
void abs_check() {
    for (int mode = 0; mode < 8; ++mode) {
        SlopeTrick<T> st;
        if (mode != 0) {
            st.add_a_minus_x(T(-4));
            st.add_x_minus_a(T(7));
        }
        if (mode == 2) st.clear_left();
        if (mode == 3) st.clear_right();
        if (mode == 4) st.shift(T(-8), T(12));
        if (mode == 5) {
            SlopeTrick<T> other;
            other.add_a_minus_x(T(-10));
            other.add_x_minus_a(T(13));
            other.shift(T(-2), T(3));
            verify(other, T(0));
            st.merge(other);
        }
        if (mode == 6) st.clear_left(), st.clear_right();
        if (mode == 7) st.shift(T(-1000000), T(1000000));
        st.add_all(T(-17));
        for (T a : {T(0), T(-30), T(30), T(-4), T(7), T(7), T(0.5)}) verify_add_abs(st, a);
    }
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
                case 0: verify_add_abs(st, a); break;
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
            for (int i = 0; i < n; ++i) verify_add_abs(huge, 0LL);
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

template<class Q>
vector<typename Q::value_type> heap_values(Q q) {
    vector<typename Q::value_type> values;
    while (!q.empty()) {
        values.push_back(q.top());
        q.pop();
    }
    return values;
}

template<class T>
void cache_rebuild_check() {
    SlopeTrick<T> st;
    static_assert(is_same_v<decltype(st.L), priority_queue<T>>);
    static_assert(is_same_v<decltype(st.R), priority_queue<T, vector<T>, greater<T>>>);
    for (int step = 0; step < 20; ++step) {
        for (int i = 0; i < 32; ++i) st.add_abs(T(i % 9 - 4) / T(2));
        st.shift(T(-0.5), T(1.5));
        auto l = heap_values(st.L), r = heap_values(st.R);
        for (int x = -10; x <= 10; ++x) verify(st, T(x));
        assert(heap_values(st.L) == l && heap_values(st.R) == r);
        assert(st.eval_cache_valid);
        assert(st.eval_l.size() == st.L.size() && st.eval_r.size() == st.R.size());
        st.L.push(T(-100) - st.add_l);
        st.R.push(T(100) - st.add_r);
        st.eval_cache_valid = false;
        verify(st, T(-200));
        verify(st, T(200));
        st.clear_left();
        verify(st, T(-10));
        assert(st.eval_l.empty());
        st.clear_right();
        verify(st, T(10));
        assert(st.eval_r.empty());
    }
}

void large_hinge_check() {
    using T = long long;
    const T inf = SlopeTrick<T>::INF;
    mt19937 rng(301);
    for (T center : {-inf - 1, -inf, -inf + 1, T(0), inf - 1, inf, inf + 1}) {
        for (bool left : {false, true}) {
            SlopeTrick<T> st;
            if (left) st.add_a_minus_x(center);
            else st.add_x_minus_a(center);
            assert(st.query().min_f == 0);
            assert(st.eval(center) == 0);
        }
        for (int mode = 0; mode < 4; ++mode) {
            SlopeTrick<T> st;
            vector<pair<T, bool>> hinges;
            if (mode != 0) {
                st.add_abs(center);
                st.eval(center);
                if (mode == 1) {
                    st.clear_left();
                    hinges.emplace_back(center, false);
                } else if (mode == 2) {
                    st.clear_right();
                    hinges.emplace_back(center, true);
                } else {
                    st.clear_left();
                    st.clear_right();
                }
            }
            for (int step = 0; step < 20; ++step) {
                T shift = T(rng() % 21) - 10;
                st.shift(shift);
                for (auto &h : hinges) h.first += shift;
                T a = center + T(rng() % 21) - 10;
                bool left = rng() % 2;
                if (left) st.add_a_minus_x(a);
                else st.add_x_minus_a(a);
                hinges.emplace_back(a, left);
                T minimum = numeric_limits<T>::max();
                for (T x = center - 250; x <= center + 250; ++x) {
                    __int128 expected = 0;
                    for (auto [point, is_left] : hinges) {
                        expected += max<__int128>(0, is_left ? __int128(point) - x : __int128(x) - point);
                    }
                    assert(st.eval(x) == expected);
                    minimum = min(minimum, T(expected));
                }
                assert(st.query().min_f == minimum);
            }
        }
    }
}

int main() {
    large_hinge_check();
    abs_check<long long>();
    abs_check<int>();
    abs_check<double>();
    random_check<long long>();
    random_check<int>();
    random_check<double>();
    cache_check();
    cache_rebuild_check<long long>();
    cache_rebuild_check<double>();
}
