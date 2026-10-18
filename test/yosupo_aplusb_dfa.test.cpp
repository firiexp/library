#define STANDALONE
#include <bits/stdc++.h>
using namespace std;

#include "../math/digit_dfa.cpp"
#include "../string/dfa_minimize.cpp"
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

void check_boolean(const DFA<2>& a, const DFA<2>& b) {
    auto both = intersect(a, b), either = unite(a, b);
    auto negated = complement(a), twice = complement(negated);
    auto same = unite(a, a), reversed = unite(b, a);
    auto compact = minimize(either), compact_not = minimize(negated);
    auto neither = complement(either);
    check_reachable(both);
    check_reachable(either);
    for (int n = 0; n <= 8; ++n) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            string s(n, 'a');
            for (int i = 0; i < n; ++i) s[i] += mask >> i & 1;
            bool x = accepts(a, s, 'a'), y = accepts(b, s, 'a');
            assert(accepts(both, s, 'a') == (x && y));
            assert(accepts(either, s, 'a') == (x || y));
            assert(accepts(negated, s, 'a') == !x);
            assert(accepts(twice, s, 'a') == x);
            assert(accepts(same, s, 'a') == x);
            assert(accepts(reversed, s, 'a') == (x || y));
            assert(accepts(compact, s, 'a') == (x || y));
            assert(accepts(compact_not, s, 'a') == !x);
            assert(accepts(neither, s, 'a') == (!x && !y));
        }
    }
}

void self_check() {
    DFA<2> empty_only{vector<array<int, 2>>(1), {true}, 0};
    empty_only.next[0].fill(-1);
    DFA<2> recover{{{1, -1}, {1, 2}, {2, 2}}, {false, true, false}, 0};
    DFA<2> universal{{{0, 0}}, {true}, 0};
    for (const auto& a : vector<DFA<2>>{{}, empty_only, recover, universal}) {
        for (const auto& b : vector<DFA<2>>{{}, empty_only, recover, universal}) check_boolean(a, b);
    }
    assert(complement(DFA<2>{}).next.size() == 1);
    assert(complement(universal).next.size() == 1);
    assert(complement(empty_only).next.size() == 2);
    mt19937 rng(149);
    for (int tc = 0; tc < 300; ++tc) {
        auto random_dfa = [&]() {
            int n = rng() % 7;
            DFA<2> a{vector<array<int, 2>>(n), vector<char>(n), int(rng() % (n + 1)) - 1};
            for (int v = 0; v < n; ++v) {
                a.accept[v] = rng() % 2;
                for (int& to : a.next[v]) to = int(rng() % (n + 1)) - 1;
            }
            return a;
        };
        auto a = random_dfa(), b = random_dfa();
        check_boolean(a, b);
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
}
