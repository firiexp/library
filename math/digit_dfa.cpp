#ifndef FIRIEXP_LIBRARY_MATH_DIGIT_DFA_CPP
#define FIRIEXP_LIBRARY_MATH_DIGIT_DFA_CPP

#include "../string/dfa.cpp"

DFA<10> digit_value_mod(int m, int r = 0) {
    assert(m > 0 && 0 <= r && r < m);
    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};
    a.accept[r] = true;
    for (int v = 0; v < m; ++v) {
        for (int d = 0; d < 10; ++d) a.next[v][d] = (10LL * v + d) % m;
    }
    return a;
}

DFA<10> digit_sum_mod(int m, int r = 0) {
    assert(m > 0 && 0 <= r && r < m);
    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};
    a.accept[r] = true;
    for (int v = 0; v < m; ++v) {
        for (int d = 0; d < 10; ++d) a.next[v][d] = (v + (long long)d) % m;
    }
    return a;
}

DFA<10> digit_sum_exact(int k) {
    assert(0 <= k && k < numeric_limits<int>::max());
    DFA<10> a{vector<array<int, 10>>(k + 1), vector<char>(k + 1), 0};
    a.accept[k] = true;
    for (int v = 0; v <= k; ++v) {
        for (int d = 0; d < 10; ++d) a.next[v][d] = d <= k - v ? v + d : -1;
    }
    return a;
}

DFA<10> no_equal_adjacent() {
    DFA<10> a{vector<array<int, 10>>(11), vector<char>(11, true), 10};
    for (int v = 0; v <= 10; ++v) {
        for (int d = 0; d < 10; ++d) a.next[v][d] = v == d ? -1 : d;
    }
    return a;
}

DFA<10> required_digits(int mask) {
    assert(0 <= mask && mask < (1 << 10));
    array<int, 10> bit{};
    int n = 1;
    for (int d = 0; d < 10; ++d) {
        if (mask >> d & 1) bit[d] = n, n *= 2;
    }
    DFA<10> a{vector<array<int, 10>>(n), vector<char>(n), 0};
    a.accept[n - 1] = true;
    for (int v = 0; v < n; ++v) {
        for (int d = 0; d < 10; ++d) a.next[v][d] = v | bit[d];
    }
    return a;
}

#endif

/**
 * @brief 数字列の条件を表す有限オートマトン
 */
