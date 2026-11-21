#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/z-algorithm.cpp"
#include "../string/z-algorithm.cpp"

template<class Sequence>
vector<int> naive_match(const Sequence& pattern, const Sequence& text) {
    vector<int> expected(text.size());
    for (int i = 0; i < (int)text.size(); ++i) {
        int& h = expected[i];
        while (h < (int)pattern.size() && i + h < (int)text.size() && pattern[h] == text[i + h]) ++h;
    }
    return expected;
}

template<class Sequence>
void check(const Sequence& pattern, const Sequence& text) {
    auto p = pattern, t = text;
    assert(z_match(pattern, text) == naive_match(pattern, text));
    assert(pattern == p && text == t);
}

template<class T>
void check_z(const vector<T>& s) {
    assert(Z_algorithm(s) == naive_match(s, s));
}

struct Value {
    int x;
    inline static int comparisons = 0;
    bool operator==(const Value& other) const {
        ++comparisons;
        return x == other.x;
    }
};

int main() {
    vector<string> words;
    for (int n = 0; n <= 5; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string s(n, '\0');
        for (int i = 0; i < n; ++i) s[i] = mask >> i & 1 ? char(255) : char(0);
        words.push_back(s);
        assert(Z_algorithm(s) == z_match(s, s));
        check_z(vector<int>(s.begin(), s.end()));
    }
    for (const auto& p : words) for (const auto& t : words) check(p, t);
    string bytes;
    for (int c = 0; c < 256; ++c) bytes.push_back(char(c));
    check(bytes, bytes + bytes);
    check(string("abababac"), string("ababababababac"));
    check(string(1000, 'a'), string(2000, 'a'));
    check(vector<int>{INT_MIN, INT_MAX, INT_MIN}, vector<int>{INT_MAX, INT_MIN, INT_MAX, INT_MIN});
    const vector<Value> values{{1}, {2}, {1}, {2}, {1}};
    check(vector<Value>{{1}, {2}, {1}}, values);
    check_z(values);
    mt19937 rng(280);
    for (int tc = 0; tc < 5000; ++tc) {
        vector<int> p(rng() % 100), t(rng() % 100);
        for (auto* s : {&p, &t}) for (int& x : *s) x = tc % 2 ? (int)rng() : (int)(rng() % 3);
        check(p, t);
        check_z(p);
    }
    vector<Value> p(100000, {1}), t(200000, {1});
    p.back().x = 2;
    Value::comparisons = 0;
    auto result = z_match(p, t);
    assert(Value::comparisons < 4 * (int)(p.size() + t.size()));
    for (int i = 0; i < (int)t.size(); ++i) assert(result[i] == min((int)p.size() - 1, (int)t.size() - i));
}
