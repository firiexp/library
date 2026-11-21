#define STANDALONE
#include <bits/stdc++.h>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;


#include "../string/suffix_array.cpp"

#include "../util/fastio.cpp"

void check_integers(const vector<int>& s, int upper) {
    int n = s.size();
    vector<int> expected(n);
    iota(expected.begin(), expected.end(), 0);
    sort(expected.begin(), expected.end(), [&](int a, int b) {
        return lexicographical_compare(s.begin() + a, s.end(),
                                       s.begin() + b, s.end());
    });
    vector<int> expected_lcp;
    for (int i = 1; i < n; ++i) {
        int a = expected[i - 1], b = expected[i], h = 0;
        while (a + h < n && b + h < n && s[a + h] == s[b + h]) ++h;
        expected_lcp.push_back(h);
    }
    assert(suffix_array(s) == expected);
    assert(suffix_array(s, upper) == expected);
    assert(lcp(s, expected) == expected_lcp);
}

template<class T>
void check_sequence(const vector<T>& s) {
    auto original = s;
    auto sa = suffix_array(s);
    vector<int> expected;
    for (int i = 1; i < (int)sa.size(); ++i) {
        int a = sa[i - 1], b = sa[i], h = 0;
        while (a + h < (int)s.size() && b + h < (int)s.size() && s[a + h] == s[b + h]) ++h;
        expected.push_back(h);
    }
    assert(lcp(s, sa) == expected);
    assert(s == original);
}

void check_short_substring_ranks(const string& s) {
    string_view text(s);
    set<string_view> expected;
    for (size_t l = 0; l < s.size(); ++l)
        for (size_t r = l + 1; r <= s.size(); ++r)
            expected.insert(text.substr(l, r - l));

    const SuffixArray sa(s);
    assert(sa.kth_substring(-1) == make_pair(-1, -1));
    long long k = 0;
    for (string_view word : expected) {
        auto [l, r] = sa.kth_substring(k++);
        assert(0 <= l && l < r && r <= sa.size());
        assert(text.substr(l, r - l) == word);
    }
    assert(sa.kth_substring(k) == make_pair(-1, -1));
    if (s.size() < 8) {
        for (char c : {char(0), char(128), char(255)}) check_short_substring_ranks(s + c);
    }
}

void check_large_substring_ranks() {
    const int n = 65'536;
    const SuffixArray sa(string(n, 'a') + string(n, 'b'));
    const long long ab_rank = 1LL * n * n;
    const long long total = ab_rank + 2 * n;
    assert(sa.kth_substring(total) == make_pair(-1, -1));
    assert(sa.kth_substring(ab_rank) == make_pair(n - 1, n + 1));
    assert(sa.kth_substring(n - 1) == make_pair(0, n));
    assert(sa.kth_substring(total - 1) == make_pair(n, 2 * n));
    assert(sa.kth_substring(LLONG_MAX) == make_pair(-1, -1));
}

void self_check() {
    check_short_substring_ranks("");
    check_large_substring_ranks();
    const SuffixArray integers(vector<int>{-3, 4, -3});
    assert(integers.kth_substring(2) == make_pair(0, 3));

    auto check = [](const string &s) {
        vector<int> bytes;
        for (unsigned char c : s) bytes.push_back(c);
        check_integers(bytes, 255);
        auto sa = suffix_array(bytes, 255);
        assert(suffix_array(s) == sa);
        assert(lcp(s, sa) == lcp(bytes, sa));
    };
    check("");
    check(string{char(128), 'a', 'b'});
    check(string{char(0), char(127), char(128), char(255), char(0), char(255)});
    for (int c : {0, 127, 128, 255}) {
        check(string(1, char(c)));
        check(string(65, char(c)));
    }
    for (int n = 0; n <= 11; ++n) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            string s(n, '\0');
            for (int i = 0; i < n; ++i) s[i] = mask >> i & 1 ? char(255) : char(0);
            check(s);
        }
    }
    check_sequence(vector<int>{INT_MIN, -2, -2, INT_MAX, INT_MIN, -2});
    check_sequence(vector<string>{"ab", "", "ab", "", "z", "ab"});
    mt19937 rng(13);
    for (int n = 0; n <= 8; ++n) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> s(n);
            for (int i = 0; i < n; ++i) s[i] = mask >> i & 1;
            check_integers(s, 1);
        }
    }
    for (int n : {3, 4, 7, 32, 129, 512}) {
        vector<int> s(n);
        iota(s.begin(), s.end(), 0);
        for (int rep = 0; rep < 5; ++rep) {
            shuffle(s.begin(), s.end(), rng);
            check_integers(s, n - 1);
        }
        for (int period : {1, 2, 7}) {
            for (int i = 0; i < n; ++i) s[i] = i % period;
            check_integers(s, period - 1);
        }
        for (int i = 0; i < n; ++i) s[i] = i % 2 ? 0 : i;
        check_integers(s, n - 1);
    }
    for (int tc = 0; tc < 1000; ++tc) {
        string s(rng() % 80, '\0');
        for (char &c : s) c = char(rng() % (tc % 2 ? 256 : 4));
        check(s);
    }
}

int main() {
    self_check();
}
