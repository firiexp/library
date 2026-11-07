#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/shortest_word.cpp"
#include "../string/shortest_word.cpp"
#include "../string/avoid_patterns.cpp"

template<int W>
optional<vector<int>> brute(const DFA<W>& a) {
    if (a.initial == -1) return nullopt;
    for (int n = 0; n < (int)a.next.size(); ++n) {
        vector<int> word(n);
        auto enumerate = [&](auto&& self, int pos, int state) -> bool {
            if (state == -1) return false;
            if (pos == n) return a.accept[state];
            for (int c = 0; c < W; ++c) {
                word[pos] = c;
                if (self(self, pos + 1, a.next[state][c])) return true;
            }
            return false;
        };
        if (enumerate(enumerate, 0, a.initial)) return word;
    }
    return nullopt;
}

template<int W>
void check(const DFA<W>& a) {
    auto original = a;
    string alphabet(W, 'a');
    iota(alphabet.begin(), alphabet.end(), 'a');
    auto result = shortest_word(a, alphabet);
    auto expected = brute(a);
    assert(bool(result) == bool(expected));
    if (result) {
        string word;
        for (int c : *expected) word.push_back(alphabet[c]);
        assert(*result == word);
        int v = a.initial;
        for (char letter : *result) {
            int c = letter - 'a';
            assert(v != -1 && 0 <= c && c < W);
            v = a.next[v][c];
        }
        assert(v != -1 && a.accept[v]);
    }
    assert(a.next == original.next && a.accept == original.accept && a.initial == original.initial);
}

int main() {
    check(DFA<2>{});
    for (int edges = 0; edges < 81; ++edges) for (int mask = 0; mask < 4; ++mask) {
        DFA<2> a{vector<array<int, 2>>(2), vector<char>(2), -1};
        int code = edges;
        for (int v = 0; v < 2; ++v) {
            a.accept[v] = mask >> v & 1;
            for (int &to : a.next[v]) {
                to = code % 3 - 1;
                code /= 3;
            }
        }
        for (int initial = -1; initial < 2; ++initial) {
            a.initial = initial;
            check(a);
        }
    }
    mt19937 rng(432);
    for (int tc = 0; tc < 3000; ++tc) {
        int s = 1 + rng() % 8;
        DFA<3> a{vector<array<int, 3>>(s), vector<char>(s), int(rng() % s)};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 5 == 0;
            for (int &to : a.next[v]) to = int(rng() % (s + 1)) - 1;
        }
        check(a);
    }
    auto avoid = avoid_patterns<2, 'a'>({"a"});
    DFA<2> odd{{{1, 1}, {0, 0}}, {false, true}, 0};
    check(avoid);
    check(intersect(avoid, odd));
    assert(shortest_word(intersect(avoid, odd), "ab") == optional<string>("b"));
    assert(shortest_word(odd, "01") == optional<string>("0"));
    assert(shortest_word(odd, "za") == optional<string>("z"));
    assert(shortest_word(odd, string("\0\xff", 2)) == optional<string>(string(1, '\0')));
    assert(shortest_word(intersect(avoid, odd), string("\0\xff", 2)) == optional<string>(string(1, '\xff')));
    check(avoid_patterns<2, 'a'>({""}));
    check(DFA<2>{{{0, 0}, {1, 1}}, {false, true}, 0});
    const int n = 200000;
    DFA<2> chain{vector<array<int, 2>>(n), vector<char>(n), 0};
    for (int v = 0; v < n; ++v) chain.next[v] = {min(v + 1, n - 1), v};
    chain.accept.back() = true;
    assert(shortest_word(chain, "ab") == optional<string>(string(n - 1, 'a')));
    chain.accept.back() = false;
    chain.next.back()[0] = 0;
    assert(!shortest_word(chain, "ab"));
    for (int v = 0; v < n; ++v) {
        for (int c = 0; c < 2; ++c) chain.next[v][c] = 2 * v + c + 1 < n ? 2 * v + c + 1 : 0;
    }
    assert(!shortest_word(chain, "ab"));
}
