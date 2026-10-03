#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <cassert>
#include <random>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;


#include "../string/suffix_array.cpp"

void self_check() {
    auto check = [](const string &s) {
        vector<int> bytes;
        for (unsigned char c : s) bytes.push_back(c);
        int n = s.size();
        vector<int> expected(n);
        iota(expected.begin(), expected.end(), 0);
        sort(expected.begin(), expected.end(), [&](int a, int b) {
            return lexicographical_compare(bytes.begin() + a, bytes.end(),
                                           bytes.begin() + b, bytes.end());
        });
        vector<int> expected_lcp;
        for (int i = 1; i < n; ++i) {
            int a = expected[i - 1], b = expected[i], h = 0;
            while (a + h < n && b + h < n && bytes[a + h] == bytes[b + h]) ++h;
            expected_lcp.push_back(h);
        }
        assert(suffix_array(s) == expected);
        assert(suffix_array(bytes) == expected);
        assert(suffix_array(bytes, 255) == expected);
        assert(lcp(s, expected) == expected_lcp);
        assert(lcp(bytes, expected) == expected_lcp);
    };
    check("");
    check(string{char(128), 'a', 'b'});
    check(string{char(0), char(127), char(128), char(255), char(0), char(255)});
    for (int c : {0, 127, 128, 255}) {
        check(string(1, char(c)));
        check(string(65, char(c)));
    }
    mt19937 rng(13);
    for (int tc = 0; tc < 1000; ++tc) {
        string s(rng() % 80, '\0');
        for (char &c : s) c = char(rng() % (tc % 2 ? 256 : 4));
        check(s);
    }
}

int main() {
    self_check();
    string s;
    cin >> s;
    auto ans = suffix_array(s);
    for (int i = 0; i < ans.size(); ++i) {
        if(i) printf(" ");
        printf("%d", ans[i]);
    }
    puts("");
    return 0;
}
