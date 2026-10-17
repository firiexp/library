#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../string/palindromic_tree.cpp"

void verify_count(const PalindromicTree<2>& pt) {
    vector<int> expected(pt.nodes.size());
    vector<int> occ;
    for (const auto& node : pt.nodes) occ.push_back(node.occ);
    expected[1] = pt.s.size();
    for (int v = 2; v < (int)pt.nodes.size(); ++v) {
        const auto& node = pt.nodes[v];
        assert(0 <= node.link && node.link < v);
        string palindrome = pt.s.substr(node.first_pos - node.len + 1, node.len);
        for (int i = 0; i + node.len <= (int)pt.s.size(); ++i) {
            expected[v] += pt.s.compare(i, node.len, palindrome) == 0;
        }
    }
    assert(pt.count() == expected);
    assert(pt.count() == expected);
    for (int v = 0; v < (int)pt.nodes.size(); ++v) {
        assert(pt.nodes[v].occ == occ[v]);
    }
}

void self_check() {
    for (int n = 0; n <= 16; ++n) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            string s(n, 'a');
            for (int i = 0; i < n; ++i) s[i] += (mask >> i) & 1;
            verify_count(PalindromicTree<2>(s));
        }
    }

    for (const string& s : {string(32, 'a'), string(32, 'b'),
                            string("abababababababab"), string("aababbabaaabbabba")}) {
        PalindromicTree<2> pt;
        verify_count(pt);
        for (char c : s) {
            pt.add(c);
            verify_count(pt);
        }
    }

    const int n = 10000;
    PalindromicTree<2> pt(string(n, 'a'));
    for (int step = 0; step < 2; ++step) {
        vector<int> counts = pt.count();
        assert(counts.size() == (size_t)(n + step + 2));
        assert(counts[0] == 0 && counts[1] == n + step);
        for (int v = 2; v < (int)pt.nodes.size(); ++v) {
            assert(pt.nodes[v].link < v);
            assert(counts[v] == n + step - pt.nodes[v].len + 1);
        }
        assert(pt.count() == counts);
        if (step == 0) pt.add('a');
    }
}

template<int W>
void verify_partitions(const PalindromicTree<W> &pt) {
    const string &s = pt.s;
    int n = s.size();
    vector<vector<bool>> palindrome(n, vector<bool>(n));
    for (int l = n - 1; l >= 0; --l) for (int r = l; r < n; ++r) {
        palindrome[l][r] = s[l] == s[r] && (r - l < 2 || palindrome[l + 1][r - 1]);
    }
    vector<int> expected(n + 1, n + 1);
    expected[0] = 0;
    for (int r = 1; r <= n; ++r) for (int l = 0; l < r; ++l) {
        if (palindrome[l][r - 1]) expected[r] = min(expected[r], expected[l] + 1);
    }
    auto counts = pt.count();
    auto dp = pt.min_partitions();
    assert(dp.count == expected);
    assert(dp.prev.size() == (size_t)n + 1 && dp.prev[0] == -1);
    for (int prefix = 1; prefix <= n; ++prefix) {
        int parts = 0;
        for (int r = prefix; r > 0; r = dp.prev[r]) {
            int l = dp.prev[r];
            assert(0 <= l && l < r);
            assert(palindrome[l][r - 1]);
            assert(dp.count[r] == dp.count[l] + 1);
            ++parts;
        }
        assert(parts == expected[prefix]);
    }
    auto again = pt.min_partitions();
    assert(again.count == dp.count && again.prev == dp.prev);
    assert(pt.count() == counts);
}

void partition_check() {
    for (int n = 0; n <= 13; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string s(n, 'a');
        for (int i = 0; i < n; ++i) s[i] += (mask >> i) & 1;
        verify_partitions(PalindromicTree<2>(s));
    }
    mt19937 rng(234);
    for (int tc = 0; tc < 1000; ++tc) {
        string s(1 + rng() % 100, 'a');
        for (char &c : s) c += rng() % 3;
        PalindromicTree<3> pt(s.substr(0, s.size() / 2));
        verify_partitions(pt);
        pt.build(s.substr(s.size() / 2));
        verify_partitions(pt);
    }
    for (const string &s : {string(100, 'a'), string("abababababababab"), string("abacdcababcbab")}) {
        PalindromicTree<4> pt;
        verify_partitions(pt);
        for (char c : s) {
            pt.add(c);
            verify_partitions(pt);
        }
    }
    string zimin;
    for (char c = 'a'; c <= 'h'; ++c) zimin = zimin + c + zimin;
    verify_partitions(PalindromicTree<8>(zimin));
    PalindromicTree<2> uniform(string(300000, 'a'));
    auto dp = uniform.min_partitions();
    for (int i = 1; i <= 300000; ++i) assert(dp.count[i] == 1 && dp.prev[i] == 0);
}

int main() {
    self_check();
    partition_check();

    Scanner sc;
    Printer pr;
    long long a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
