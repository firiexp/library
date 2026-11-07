#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/kth_word.cpp"
#include "../string/kth_word.cpp"
#include "../string/dfa_kth_word.cpp"
#include "../string/dfa_kth_word.cpp"
#include "../string/avoid_patterns.cpp"

template<int W>
bool accepts(const DFA<W>& a, const vector<int>& word) {
    int v = a.initial;
    for (int c : word) {
        if (v == -1) return false;
        assert(0 <= c && c < W);
        v = a.next[v][c];
    }
    return v != -1 && a.accept[v];
}

template<int W>
void check(const DFA<W>& a, int max_length = 8) {
    auto original = a;
    DFAKthWord index(a, max_length);
    DFAKthWord bounded(a, max_length, 3);
    for (int n = 0; n <= max_length; ++n) {
        vector<vector<int>> words;
        vector<int> word(n);
        auto enumerate = [&](auto&& self, int pos) -> void {
            if (pos == n) {
                if (accepts(a, word)) words.push_back(word);
                return;
            }
            for (int c = 0; c < W; ++c) {
                word[pos] = c;
                self(self, pos + 1);
            }
        };
        enumerate(enumerate, 0);
        for (size_t k = 0; k < words.size(); ++k) {
            auto result = kth_word(a, n, k);
            assert(result && *result == words[k]);
            assert(index.kth(n, k) == result);
            if (k <= 3) assert(bounded.kth(n, k) == result);
            assert(accepts(a, *result));
            if (k) assert(words[k - 1] < *result);
        }
        assert(!kth_word(a, n, words.size()));
        assert(!kth_word(a, n, ULLONG_MAX));
        assert(!index.kth(n, words.size()));
        assert(!index.kth(n, ULLONG_MAX));
        if (words.size() <= 3) assert(!bounded.kth(n, words.size()));
    }
    assert(a.next == original.next && a.accept == original.accept && a.initial == original.initial);
}

int main() {
    check(DFA<2>{});
    check(DFA<2>{{{-1, -1}}, {true}, 0});
    check(DFA<2>{{{0, 0}}, {false}, 0});
    check(DFA<2>{{{0, -1}}, {true}, 0});
    check(DFA<2>{{{0, 0}}, {true}, -1});
    DFA<2> all{{{0, 0}}, {true}, 0};
    check(all);
    DFAKthWord all_index(all, 200);
    DFAKthWord first_index(all, 200, 0);
    for (int n = 0; n <= 200; ++n) {
        for (auto k : {0ULL, 1ULL, 1ULL << 63, ULLONG_MAX}) {
            assert(all_index.kth(n, k) == kth_word(all, n, k));
        }
        assert(first_index.kth(n, 0) == optional<vector<int>>(vector<int>(n)));
    }
    auto changed = all;
    DFAKthWord snapshot(changed, 2);
    changed.next.clear();
    changed.accept.clear();
    changed.initial = -1;
    assert(snapshot.kth(2, 3) == optional<vector<int>>({1, 1}));
    auto copy = snapshot;
    assert(copy.kth(2, 1) == optional<vector<int>>({0, 1}));
    for (int n : {0, 1, 63, 64, 65, 200}) {
        assert(kth_word(all, n, 0) == optional<vector<int>>(vector<int>(n, 0)));
    }
    assert(!kth_word(all, 63, ULLONG_MAX));
    assert(!kth_word(all, 63, 1ULL << 63));
    assert(kth_word(all, 63, (1ULL << 63) - 1) == optional<vector<int>>(vector<int>(63, 1)));
    assert(kth_word(all, 64, ULLONG_MAX) == optional<vector<int>>(vector<int>(64, 1)));
    vector<int> large(200);
    fill(large.end() - 64, large.end(), 1);
    assert(kth_word(all, 200, ULLONG_MAX) == optional<vector<int>>(large));
    DFA<2> only_b{{{-1, 0}}, {true}, 0};
    assert(kth_word(only_b, 1024, 0) == optional<vector<int>>(vector<int>(1024, 1)));
    assert(!kth_word(only_b, 1024, 1));
    DFA<256> bytes{vector<array<int, 256>>(1), {true}, 0};
    for (int n : {0, 1, 7, 8, 9, 128}) {
        assert(kth_word(bytes, n, 0) == optional<vector<int>>(vector<int>(n, 0)));
        if (n < 8) assert(!kth_word(bytes, n, ULLONG_MAX));
        else {
            vector<int> expected(n);
            fill(expected.end() - 8, expected.end(), 255);
            assert(kth_word(bytes, n, ULLONG_MAX) == optional<vector<int>>(expected));
        }
    }
    bytes.next[0].fill(-1);
    bytes.next[0][255] = 0;
    check(bytes, 1);
    assert(kth_word(bytes, 128, 0) == optional<vector<int>>(vector<int>(128, 255)));
    assert(!kth_word(bytes, 128, 1));
    auto avoid = avoid_patterns<2, 'a'>({"aa", "aa", "bab"});
    check(avoid);
    check(avoid_patterns<2, 'a'>({""}));
    DFA<2> even_length{{{1, 1}, {0, 0}}, {true, false}, 0};
    check(intersect(avoid, even_length));
    auto example = kth_word(avoid_patterns<2, 'a'>({"aa"}), 3, 1);
    assert(example == optional<vector<int>>({0, 1, 1}));
    mt19937 rng(284);
    for (int tc = 0; tc < 500; ++tc) {
        int s = 1 + rng() % 8;
        DFA<2> a{vector<array<int, 2>>(s), vector<char>(s), (int)(rng() % (s + 1)) - 1};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 2;
            for (int& to : a.next[v]) to = (int)(rng() % (s + 1)) - 1;
        }
        check(a);
    }
    for (int tc = 0; tc < 50; ++tc) {
        int s = 1 + rng() % 6;
        DFA<3> a{vector<array<int, 3>>(s), vector<char>(s), (int)(rng() % s)};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 2;
            for (int& to : a.next[v]) to = (int)(rng() % (s + 1)) - 1;
        }
        check(a, 6);
    }
}
