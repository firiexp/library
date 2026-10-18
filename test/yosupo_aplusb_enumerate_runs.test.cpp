#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/enumerate_runs.cpp"
#include "../string/enumerate_runs.cpp"

void check(const string& s) {
    int n = (int)s.size();
    vector<array<int, 3>> expected, actual;
    for (int l = 0; l < n; ++l) for (int r = l + 2; r <= n; ++r) {
        for (int p = 1; 2 * p <= r - l; ++p) {
            bool periodic = true;
            for (int i = l + p; i < r; ++i) periodic &= s[i] == s[i - p];
            if (!periodic) continue;
            if ((l == 0 || s[l - 1] != s[l - 1 + p]) &&
                (r == n || s[r] != s[r - p])) expected.push_back({p, l, r});
            break;
        }
    }
    sort(expected.begin(), expected.end());
    auto original = s;
    for (auto [p, l, r] : enumerate_runs(s)) actual.push_back({p, l, r});
    assert(s == original);
    assert(actual == expected);
}

int main() {
    for (int alphabet : {2, 3}) {
        int limit = alphabet == 2 ? 11 : 7;
        for (int n = 0, total = 1; n <= limit; ++n, total *= alphabet) {
            for (int mask = 0; mask < total; ++mask) {
                int code = mask;
                string s(n, '\0');
                for (char& c : s) {
                    c = (char)array<int, 3>{0, 128, 255}[code % alphabet];
                    code /= alphabet;
                }
                check(s);
            }
        }
    }
    mt19937 rng(81);
    for (int tc = 0; tc < 1000; ++tc) {
        string s(rng() % 31, '\0');
        int alphabet = tc % 2 ? 256 : 3;
        for (char& c : s) c = (char)(rng() % alphabet);
        check(s);
    }
    for (const char* s : {"aababaababb", "abababab", "abcabcabc", "mississippi"}) check(s);
}
