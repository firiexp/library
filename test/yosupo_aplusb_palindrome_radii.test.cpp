#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/manacher.cpp"

void check(const string &s) {
    const PalindromeRadii radii(s);
    int n = s.size();
    assert((int)radii.odd.size() == n && (int)radii.even.size() == n);
    assert(radii.odd == manacher(s));
    for (int i = 0; i < n; ++i) {
        int odd = 1, even = 0;
        while (i >= odd && i + odd < n && s[i - odd] == s[i + odd]) ++odd;
        while (i > even && i + even < n && s[i - even - 1] == s[i + even]) ++even;
        assert(radii.odd[i] == odd && radii.even[i] == even);
    }
    for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
        string t = s.substr(l, r - l), reversed = t;
        reverse(reversed.begin(), reversed.end());
        assert(radii.is_palindrome(l, r) == (t == reversed));
    }
}

int main() {
    for (int n = 0, count = 1; n <= 8; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            string s(n, 'a');
            int x = mask;
            for (char &c : s) c += x % 3, x /= 3;
            check(s);
        }
    }
    mt19937 rng(89);
    for (int tc = 0; tc < 300; ++tc) {
        string s(rng() % 40, '\0');
        for (char &c : s) c = rng() % 256;
        check(s);
        string t = s;
        reverse(t.begin(), t.end());
        check(s + '$' + t);
        check(s + t);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
