#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/wildcard_pattern_matching.cpp"
#include "../string/wildcard_pattern_matching.cpp"

void check(const string& s, const string& t, char wildcard = '*') {
    vector<int> expected;
    for (int i = 0; i + (int)t.size() <= (int)s.size(); ++i) {
        bool ok = true;
        for (int j = 0; j < (int)t.size(); ++j)
            ok &= s[i + j] == wildcard || t[j] == wildcard || s[i + j] == t[j];
        expected.push_back(ok);
    }
    assert(wildcard_pattern_matching(s, t, wildcard) == expected);
}

int main() {
    vector<string> words{string()};
    for (int n = 1, total = 3; n <= 4; ++n, total *= 3) {
        for (int mask = 0; mask < total; ++mask) {
            int code = mask;
            string s(n, ' ');
            for (char& c : s) {
                c = "ab*"[code % 3];
                code /= 3;
            }
            words.push_back(s);
        }
    }
    for (const auto& s : words) for (const auto& t : words) check(s, t);
    mt19937 rng(124);
    for (int tc = 0; tc < 500; ++tc) {
        string s(rng() % 100, '\0'), t(rng() % 100, '\0');
        char wildcard = (char)rng();
        for (char& c : s) c = rng() % 4 ? (char)rng() : wildcard;
        for (char& c : t) c = rng() % 4 ? (char)rng() : wildcard;
        check(s, t, wildcard);
    }
    for (int n : {31, 32, 33, 63, 64, 65, 127, 128, 129}) {
        check(string(n, '\xff'), string(n / 2 + 1, '\0'));
        check(string(n, '\xff'), string(n / 2 + 1, '\xff'));
        check(string(n, '*'), string(n / 2 + 1, '\xff'));
    }
    string s = string(179, 'z') + string(60488, 'g');
    string t = string(179, 'a') + string(60488, 'f');
    assert((wildcard_pattern_matching(s, t) == vector<int>{0}));
    Scanner sc;
    Printer pr;
    long long a, b;
    sc.read(a, b);
    pr.println(a + b);
}
