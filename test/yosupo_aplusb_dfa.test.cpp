#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <bits/stdc++.h>
using namespace std;

#include "../math/digit_dfa.cpp"
#include "../util/fastio.cpp"

template<int W>
bool accepts(const DFA<W>& a, const string& s, char start) {
    int v = a.initial;
    for (char c : s) {
        if (v == -1) return false;
        v = a.next[v][c - start];
    }
    return v != -1 && a.accept[v];
}

template<int W>
void check_reachable(const DFA<W>& a) {
    assert(a.accept.size() == a.next.size());
    if (a.initial == -1) {
        assert(a.next.empty());
        return;
    }
    vector<char> seen(a.next.size());
    vector<int> q{a.initial};
    seen[a.initial] = true;
    for (size_t i = 0; i < q.size(); ++i) {
        for (int v : a.next[q[i]]) {
            assert(-1 <= v && v < (int)a.next.size());
            if (v != -1 && !seen[v]) seen[v] = true, q.push_back(v);
        }
    }
    assert(q.size() == a.next.size());
}

void self_check() {
    mt19937 rng(149);
    for (int tc = 0; tc < 300; ++tc) {
        auto random_dfa = [&]() {
            int n = 1 + rng() % 8;
            DFA<2> a{vector<array<int, 2>>(n), vector<char>(n), int(rng() % (n + 1)) - 1};
            for (int v = 0; v < n; ++v) {
                a.accept[v] = rng() % 2;
                for (int& to : a.next[v]) to = int(rng() % (n + 1)) - 1;
            }
            return a;
        };
        auto a = random_dfa(), b = random_dfa();
        auto c = intersect(a, b);
        check_reachable(c);
        for (int n = 0; n <= 8; ++n) {
            for (int mask = 0; mask < (1 << n); ++mask) {
                string s(n, 'a');
                for (int i = 0; i < n; ++i) s[i] += mask >> i & 1;
                assert(accepts(c, s, 'a') == (accepts(a, s, 'a') && accepts(b, s, 'a')));
            }
        }
    }
    assert(intersect(digit_value_mod(2), digit_value_mod(4)).next.size() == 4);
    assert(intersect(DFA<10>{}, digit_value_mod(1)).initial == -1);
    for (int m = 1; m <= 12; ++m) {
        for (int r = 0; r < m; ++r) {
            auto value = digit_value_mod(m, r), sum = digit_sum_mod(m, r);
            for (int x = 0; x <= 2000; ++x) {
                string s = to_string(x);
                int total = 0;
                for (char c : s) total += c - '0';
                assert(accepts(value, s, '0') == (x % m == r));
                assert(accepts(sum, s, '0') == (total % m == r));
                assert(accepts(value, "00" + s, '0') == (x % m == r));
            }
        }
    }
    for (int k = 0; k <= 30; ++k) {
        auto exact = digit_sum_exact(k);
        for (int x = 0; x <= 2000; ++x) {
            string s = to_string(x);
            int total = 0;
            for (char c : s) total += c - '0';
            assert(accepts(exact, s, '0') == (total == k));
        }
    }
    for (int mask = 0; mask < 1024; ++mask) {
        auto a = required_digits(mask);
        assert(a.next.size() == size_t(1 << __builtin_popcount(unsigned(mask))));
        assert(accepts(a, "", '0') == (mask == 0));
        for (int x = 0; x <= 2000; ++x) {
            string s = to_string(x);
            int seen = 0;
            for (char c : s) seen |= 1 << (c - '0');
            assert(accepts(a, s, '0') == ((seen & mask) == mask));
        }
    }
    auto adjacent = no_equal_adjacent();
    for (int x = 0; x <= 2000; ++x) {
        string s = to_string(x);
        assert(accepts(adjacent, s, '0') == (adjacent_find(s.begin(), s.end()) == s.end()));
    }
    assert(accepts(adjacent, "", '0'));
    assert(!accepts(adjacent, "00", '0'));
    assert(accepts(digit_sum_exact(0), "", '0'));
    assert(!accepts(digit_sum_exact(1), "", '0'));
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
