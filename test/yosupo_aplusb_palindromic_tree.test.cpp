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

int main() {
    self_check();

    Scanner sc;
    Printer pr;
    long long a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
