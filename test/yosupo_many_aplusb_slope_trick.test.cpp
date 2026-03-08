#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <random>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/slope_trick.cpp"

int main() {
    {
        mt19937 rng(123456789);
        constexpr long long INF = (1LL << 60);
        constexpr int LIM = 200;
        auto idx = [&](int x) { return x + LIM; };

        auto make_zero = [&]() {
            return vector<long long>(2 * LIM + 1, 0);
        };

        auto apply_add_all = [&](vector<long long> &f, int a) {
            for (auto &x : f) x += a;
        };
        auto apply_add_a_minus_x = [&](vector<long long> &f, int a) {
            for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += max(0, a - x);
        };
        auto apply_add_x_minus_a = [&](vector<long long> &f, int a) {
            for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += max(0, x - a);
        };
        auto apply_add_abs = [&](vector<long long> &f, int a) {
            for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += abs(x - a);
        };
        auto apply_merge = [&](vector<long long> &f, const vector<long long> &g) {
            for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += g[idx(x)];
        };

        for (int trial = 0; trial < 200; ++trial) {
            SlopeTrick<long long> st;
            auto brute = make_zero();
            for (int step = 0; step < 40; ++step) {
                int op = uniform_int_distribution<int>(0, 4)(rng);
                int a = uniform_int_distribution<int>(-20, 20)(rng);
                if (op == 0) {
                    st.add_all(a);
                    apply_add_all(brute, a);
                } else if (op == 1) {
                    st.add_a_minus_x(a);
                    apply_add_a_minus_x(brute, a);
                } else if (op == 2) {
                    st.add_x_minus_a(a);
                    apply_add_x_minus_a(brute, a);
                } else if (op == 3) {
                    st.add_abs(a);
                    apply_add_abs(brute, a);
                } else {
                    SlopeTrick<long long> other;
                    auto brute_other = make_zero();
                    int kind = uniform_int_distribution<int>(0, 3)(rng);
                    int c = uniform_int_distribution<int>(-20, 20)(rng);
                    if (kind == 0) {
                        other.add_a_minus_x(c);
                        apply_add_a_minus_x(brute_other, c);
                    } else if (kind == 1) {
                        other.add_x_minus_a(c);
                        apply_add_x_minus_a(brute_other, c);
                    } else if (kind == 2) {
                        other.add_abs(c);
                        apply_add_abs(brute_other, c);
                    } else {
                        other.add_all(c);
                        apply_add_all(brute_other, c);
                    }
                    st.merge(other);
                    apply_merge(brute, brute_other);
                }

                long long brute_min = INF;
                for (int x = -LIM; x <= LIM; ++x) {
                    long long got = st.eval(x);
                    long long want = brute[idx(x)];
                    if (got != want) return 1;
                    brute_min = min(brute_min, want);
                }
                if (st.query().min_f != brute_min) return 1;
            }
        }

        {
            SlopeTrick<long long> st;
            st.add_abs(3);
            st.clear_right();
            for (int x = -LIM; x <= LIM; ++x) {
                if (st.eval(x) != max(0, 3 - x)) return 1;
            }
            if (st.query().min_f != 0) return 1;
        }
        {
            SlopeTrick<long long> st;
            st.add_abs(3);
            st.clear_left();
            for (int x = -LIM; x <= LIM; ++x) {
                if (st.eval(x) != max(0, x - 3)) return 1;
            }
            if (st.query().min_f != 0) return 1;
        }
        {
            SlopeTrick<long long> st;
            st.add_abs(3);
            st.shift(2);
            for (int x = -LIM; x <= LIM; ++x) {
                if (st.eval(x) != abs(x - 5)) return 1;
            }
            if (st.query().min_f != 0) return 1;
        }
        {
            SlopeTrick<long long> st;
            st.add_abs(0);
            st.shift(1, 3);
            for (int x = -LIM; x <= LIM; ++x) {
                long long want = 0;
                if (x < 1) want = 1 - x;
                if (x > 3) want = x - 3;
                if (st.eval(x) != want) return 1;
            }
            if (st.query().min_f != 0) return 1;
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
