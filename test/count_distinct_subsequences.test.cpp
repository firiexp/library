#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../math/modular/modint_base.cpp"
#include "../string/count_distinct_subsequences.cpp"
#include "../string/count_distinct_subsequences.cpp"

struct AdditiveCount {
    long long value;
    explicit AdditiveCount(long long value) : value(value) {}
    friend AdditiveCount operator+(AdditiveCount a, AdditiveCount b) { return AdditiveCount(a.value + b.value); }
    friend AdditiveCount operator-(AdditiveCount a, AdditiveCount b) { return AdditiveCount(a.value - b.value); }
};

void check(const string& s) {
    set<string> subsequences;
    for (int mask = 1; mask < (1 << s.size()); ++mask) {
        string t;
        for (int i = 0; i < (int)s.size(); ++i) if (mask >> i & 1) t += s[i];
        subsequences.insert(t);
    }
    long long expected = subsequences.size();
    auto original = s;
    assert(count_distinct_subsequences<long long>(s) == expected);
    assert(count_distinct_subsequences<AdditiveCount>(s).value == expected);
    assert(count_distinct_subsequences<modint<2>>(s) == modint<2>(expected));
    assert(count_distinct_subsequences<modint<3>>(s) == modint<3>(expected));
    assert(count_distinct_subsequences<modint<5>>(s) == modint<5>(expected));
    assert(count_distinct_subsequences<modint<998244353>>(s) == modint<998244353>(expected));
    string wrapped = "x" + s + "y";
    assert(count_distinct_subsequences<long long>(string_view(wrapped).substr(1, s.size())) == expected);
    assert(s == original);
}

int main() {
    for (int n = 0, total = 1; n <= 7; ++n, total *= 3) {
        for (int mask = 0; mask < total; ++mask) {
            int code = mask;
            string s;
            for (int i = 0; i < n; ++i) {
                s += char(array<int, 3>{0, 128, 255}[code % 3]);
                code /= 3;
            }
            check(s);
        }
    }
    check("abcdefghijkl");
    check("abababababab");
    check(string(12, '\xff'));
    mt19937 rng(313);
    for (int trial = 0; trial < 300; ++trial) {
        string s(rng() % 13, '\0');
        for (char& c : s) c = char(rng() % (trial % 2 ? 256 : 4));
        check(s);
    }
    assert(count_distinct_subsequences<long long>(string(100000, 'a')) == 100000);
    assert(count_distinct_subsequences<modint<3>>(string(100000, 'a')) == modint<3>(100000));
}
