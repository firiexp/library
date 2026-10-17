#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/trie.cpp"

template<int W, class F>
void check(Trie<W, F>& trie, const vector<pair<string, int>>& entries) {
    const auto& const_trie = trie;
    static_assert(is_same_v<decltype(const_trie.idxs(0)), const vector<int>&>);
    assert(const_trie.idxs(-1).empty());
    auto index = const_trie.prefix_intervals();
    auto sorted = entries;
    stable_sort(sorted.begin(), sorted.end(), [&](const auto& a, const auto& b) {
        return lexicographical_compare(a.first.begin(), a.first.end(), b.first.begin(), b.first.end(),
            [&](char x, char y) { return trie.f(x) < trie.f(y); });
    });
    vector<int> order;
    set<string> prefixes{""};
    for (const auto& [word, id] : sorted) {
        order.push_back(id);
        for (int i = 1; i <= (int)word.size(); ++i) prefixes.insert(word.substr(0, i));
    }
    assert(index.order == order && index.range.size() == trie.v.size());
    for (const auto& prefix : prefixes) {
        int node = trie.find(prefix);
        assert(node >= 0);
        auto [l, r] = index.range[node];
        assert(0 <= l && l <= r && r <= (int)order.size());
        vector<int> expected;
        vector<int> terminal_ids;
        for (const auto& [word, id] : sorted) {
            if (word.compare(0, prefix.size(), prefix) == 0) expected.push_back(id);
            if (word == prefix) terminal_ids.push_back(id);
        }
        assert(vector<int>(order.begin() + l, order.begin() + r) == expected);
        assert(const_trie.idxs(node) == terminal_ids);
        vector<int> iterated;
        for (int id : const_trie.idxs(node)) iterated.push_back(id);
        assert(iterated == terminal_ids);
        auto copied = const_trie.idxs(node);
        copied.push_back(123);
        assert(const_trie.idxs(node) == terminal_ids);
        assert(trie.id(node) == (terminal_ids.empty() ? -1 : terminal_ids.back()));
    }
}

void self_check() {
    auto alphabet = [](char c) { return c - 'a'; };
    Trie<3, decltype(alphabet)> fixed(alphabet);
    vector<pair<string, int>> fixed_entries{{"", 5}, {"", 5}, {"ab", 7}, {"ab", 2}, {"ab", 7}};
    for (const auto& [word, id] : fixed_entries) fixed.add(word, id);
    check(fixed, fixed_entries);
    auto saved = fixed.idxs(fixed.find("ab"));
    fixed.add("ab", 9);
    fixed.add(string(1000, 'c'), 10);
    assert((saved == vector<int>{7, 2, 7}));
    mt19937 rng(147);
    for (int tc = 0; tc < 800; ++tc) {
        auto f = [tc](char c) { return tc % 2 ? 'c' - c : c - 'a'; };
        Trie<3, decltype(f)> trie(f);
        vector<pair<string, int>> entries;
        check(trie, entries);
        int n = rng() % 35;
        for (int i = 0; i < n; ++i) {
            string word(rng() % 10, 'a');
            for (auto& c : word) c += rng() % 3;
            if (i % 4 == 0 && !entries.empty()) word = entries.back().first;
            int id = int(rng() % 9) - 4;
            entries.emplace_back(word, id);
            trie.add(word, id);
        }
        check(trie, entries);
        auto snapshot = trie.prefix_intervals();
        auto old_order = snapshot.order;
        auto old_range = snapshot.range;
        trie.add("ccba", 99);
        entries.emplace_back("ccba", 99);
        check(trie, entries);
        assert(snapshot.order == old_order && snapshot.range == old_range);
    }
    auto byte_index = [](char c) { return (unsigned char)c; };
    Trie<256, decltype(byte_index)> bytes(byte_index);
    vector<pair<string, int>> entries = {{"", 4}, {string(1, '\0'), 3}, {string(1, char(255)), 3}};
    for (const auto& [word, id] : entries) bytes.add(word, id);
    check(bytes, entries);
    auto single = [](char) { return 0; };
    Trie<1, decltype(single)> deep(single);
    deep.add(string(200000, 'a'), 7);
    auto index = deep.prefix_intervals();
    assert(index.order == vector<int>{7});
    for (auto range : index.range) assert(range == make_pair(0, 1));
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
