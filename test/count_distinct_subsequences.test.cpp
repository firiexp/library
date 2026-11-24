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

template<class Sequence>
long long brute_count(const Sequence& s) {
    set<Sequence> subsequences;
    for (int mask = 1; mask < (1 << s.size()); ++mask) {
        Sequence t;
        for (int i = 0; i < (int)s.size(); ++i) if (mask >> i & 1) t.push_back(s[i]);
        subsequences.insert(t);
    }
    return subsequences.size();
}

template<class T>
void check_vector(const vector<T>& a) {
    long long expected = brute_count(a);
    assert(count_distinct_subsequences<long long>(a) == expected);
    assert(count_distinct_subsequences<AdditiveCount>(a).value == expected);
    assert(count_distinct_subsequences<modint<3>>(a) == modint<3>(expected));
}

void check(const string& s) {
    long long expected = brute_count(s);
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
            check_vector(vector<int>(s.begin(), s.end()));
        }
    }
    check("abcdefghijkl");
    check("abababababab");
    check(string(12, '\xff'));
    check_vector(vector<long long>{});
    check_vector(vector<long long>{LLONG_MIN, 0, LLONG_MAX, 1LL << 40, LLONG_MIN, LLONG_MAX});
    check_vector(vector<int>{INT_MIN, 0, INT_MAX, INT_MIN});
    check_vector(vector<string>{"red", "blue", "red", "green"});
    check_vector(vector<bool>{true, false, true});
    mt19937 rng(313);
    for (int trial = 0; trial < 300; ++trial) {
        string s(rng() % 13, '\0');
        for (char& c : s) c = char(rng() % (trial % 2 ? 256 : 4));
        check(s);
    }
    assert(count_distinct_subsequences<long long>(string(100000, 'a')) == 100000);
    assert(count_distinct_subsequences<modint<3>>(string(100000, 'a')) == modint<3>(100000));
    assert(count_distinct_subsequences<long long>(vector<long long>(100000, LLONG_MIN)) == 100000);
}
