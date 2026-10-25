#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../string/lex_trie.cpp"

void check_pair(const LexTrie& trie, const vector<vector<int>>& words, int a, int b) {
    const auto& x = words[a];
    const auto& y = words[b];
    int common = 0;
    while (common < (int)min(x.size(), y.size()) && x[common] == y[common]) ++common;
    int order = (x > y) - (x < y);
    assert(trie.compare(a, b) == order);
    assert(trie.less(a, b) == (order < 0));
    assert(trie.compare(b, a) == -order);
    assert(trie.lcp(a, b) == common);
    int p = trie.lca(a, b);
    assert(trie.length(p) == common);
    assert(trie.jump(a, x.size() - common) == p);
    assert(trie.jump(b, y.size() - common) == p);
}

void exhaustive_check() {
    LexTrie trie;
    vector<vector<int>> words(1);
    const int alphabet[] = {INT_MIN, -1, INT_MAX};
    for (int p = 0; p < (int)words.size(); ++p) {
        if (words[p].size() == 5) continue;
        for (int c : alphabet) {
            int v = trie.append(p, c);
            assert(v == (int)words.size());
            auto s = words[p];
            s.push_back(c);
            words.push_back(s);
            assert(trie.append(p, c) == v);
        }
    }
    for (int a = 0; a < trie.size(); ++a) {
        assert(trie.jump(a, -1) == -1);
        assert(trie.jump(a, INT_MAX) == -1);
        assert(trie.jump(a, trie.length(a) + 1) == -1);
        assert(trie.jump(a, 0) == a);
        assert(trie.jump(a, trie.length(a)) == 0);
        for (int b = 0; b < trie.size(); ++b) check_pair(trie, words, a, b);
    }
}

void string_check() {
    LexTrie trie(1);
    assert(trie.size() == 1 && trie.length(0) == 0);
    assert(trie.insert("") == 0);
    vector<string> words = {"", "a", "ab", "abc", "abd", "b", "ba", "ab", "a"};
    for (int c = 0; c < 256; ++c) {
        words.push_back(string(1, char(c)));
        words.push_back(string{'a', char(c), '\0'});
    }
    vector<int> ids;
    for (const auto& s : words) {
        int v = trie.insert(s);
        ids.push_back(v);
        assert(trie.length(v) == (int)s.size());
        int size = trie.size();
        assert(trie.insert(string_view(s)) == v);
        assert(trie.append(v, "") == v);
        int p = 0;
        for (char c : s) p = trie.append(p, c);
        assert(p == v && trie.size() == size);
        for (int i = 0; i <= (int)s.size(); ++i) {
            int prefix = trie.insert(string_view(s).substr(0, i));
            assert(trie.append(prefix, string_view(s).substr(i)) == v);
        }
    }
    for (int a = 0; a < (int)words.size(); ++a) {
        for (int b = 0; b < (int)words.size(); ++b) {
            int order = (words[a] > words[b]) - (words[a] < words[b]);
            assert(trie.compare(ids[a], ids[b]) == order);
        }
    }
    int byte = trie.insert(string(1, char(255)));
    assert(byte == trie.append(0, 255));
    assert(trie.less(trie.append(0, -1), byte));
    assert(trie.append(0, INT_MIN) != trie.append(0, 0));
    assert(trie.append(0, INT_MAX) != trie.append(0, -1));
}

void random_check() {
    mt19937 rng(296);
    LexTrie trie;
    vector<vector<int>> words(1);
    map<pair<int, int>, int> edges;
    for (int step = 0; step < 20000; ++step) {
        int p = rng() % trie.size();
        int c = int(rng() % 17) - 8;
        if (step % 5 == 0) c = int(rng() & INT_MAX);
        int v = trie.append(p, c);
        auto [it, added] = edges.emplace(make_pair(p, c), words.size());
        assert(v == it->second);
        if (added) {
            auto s = words[p];
            s.push_back(c);
            words.push_back(s);
        }
        assert(trie.size() == (int)words.size());
        assert(trie.length(v) == (int)words[v].size());
        assert(trie.append(p, c) == v);
        if (step % 2000 == 0) trie.reserve(trie.size() + 3000);
        for (int rep = 0; rep < 8; ++rep)
            check_pair(trie, words, rng() % trie.size(), rng() % trie.size());
    }
    vector<int> order(trie.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return trie.less(a, b); });
    for (int i = 1; i < (int)order.size(); ++i) assert(words[order[i - 1]] < words[order[i]]);
    auto copied = trie;
    int size = trie.size();
    assert(copied.append(0, INT_MIN) == size);
    assert(trie.size() == size);
    for (auto [edge, v] : edges) assert(copied.append(edge.first, edge.second) == v);
    LexTrie moved = move(copied);
    for (int rep = 0; rep < 1000; ++rep)
        check_pair(moved, words, rng() % size, rng() % size);
}

void deep_check() {
    const int n = 200000;
    LexTrie trie;
    vector<int> chain(n + 1);
    for (int i = 1; i <= n; ++i) chain[i] = trie.append(chain[i - 1], 0);
    for (int d = 0; d <= n; ++d) assert(trie.jump(chain[n], n - d) == chain[d]);
    for (int d = 0; d <= n; d += 997) {
        int branch = trie.append(chain[d], -1);
        int tail = branch;
        for (int k = 0; k < 1000; ++k) tail = trie.append(tail, 1);
        assert(trie.lca(tail, chain[n]) == chain[d]);
        assert(trie.lcp(chain[n], tail) == d);
        assert(trie.less(chain[d], tail));
        assert(trie.less(tail, chain[n]));
        assert(trie.jump(tail, 1000) == branch);
        assert(trie.jump(tail, 1001) == chain[d]);
    }
    for (int k = 1; k < 18; ++k) {
        for (int delta : {-1, 0, 1}) {
            int d = (1 << k) + delta;
            assert(trie.lca(chain[d], chain[n]) == chain[d]);
            assert(trie.less(chain[d], chain[n]));
        }
    }
    for (int c = -50000; c <= 50000; ++c) trie.append(0, c);
    for (int c = -50000; c < 50000; ++c) {
        int a = trie.append(0, c), b = trie.append(0, c + 1);
        assert(trie.less(a, b));
        assert(trie.lca(a, b) == 0);
    }
    assert(trie.insert(string(n, '\0')) == chain[n]);
}

int main() {
    exhaustive_check();
    string_check();
    random_check();
    deep_check();
}
