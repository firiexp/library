#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/ahocorasick.cpp"

vector<string> words(int max_length) {
    vector<string> result;
    for (int n = 0, count = 1; n <= max_length; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            string s(n, 'a');
            int x = mask;
            for (char &c : s) c += x % 3, x /= 3;
            result.push_back(s);
        }
    }
    return result;
}

void check(vector<string> patterns, const vector<string> &texts) {
    AhoCorasick<3, 'a'> aho;
    vector<int> terminal;
    for (auto &s : patterns) terminal.push_back(aho.add(s));
    aho.build();
    auto before = aho.v;
    auto order = aho.ord;
    const auto &automaton = aho;
    for (const auto &text : texts) {
        auto counts = automaton.occurrence_counts(text);
        assert(counts.size() == before.size());
        assert(counts[0] == (long long)text.size() + 1);
        for (int i = 0; i < (int)patterns.size(); ++i) {
            long long expected = 0;
            const auto &s = patterns[i];
            for (int l = 0; l + s.size() <= text.size(); ++l)
                expected += text.compare(l, s.size(), s) == 0;
            assert(counts[terminal[i]] == expected);
        }
    }
    assert(aho.ord == order && aho.v.size() == before.size());
    for (int i = 0; i < (int)before.size(); ++i) {
        assert(aho.v[i].to == before[i].to);
        assert(aho.v[i].fail == before[i].fail && aho.v[i].val == before[i].val);
    }
}

int main() {
    auto patterns = words(4);
    patterns.push_back("");
    patterns.push_back("aa");
    auto texts = words(7);
    check(patterns, texts);
    check({}, texts);
    mt19937 rng(88);
    for (int tc = 0; tc < 200; ++tc) {
        shuffle(patterns.begin(), patterns.end(), rng);
        vector<string> subset(patterns.begin(), patterns.begin() + rng() % patterns.size());
        check(subset, {"", "aaaaaaa", "abcabc", "bacabca", texts[rng() % texts.size()]});
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
