#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../util/is_palindrome.cpp"

bool brute_palindrome(string s, char wildcard) {
    auto pos = s.find(wildcard);
    if (pos == string::npos) {
        string reversed = s;
        reverse(reversed.begin(), reversed.end());
        return s == reversed;
    }
    for (char c : {'a', 'b'}) {
        s[pos] = c;
        if (brute_palindrome(s, wildcard)) return true;
    }
    return false;
}

void self_check() {
    assert(is_palindrome("aba"));
    assert(is_palindrome("a?"));
    assert(!is_palindrome("a?", '*'));
    assert(is_palindrome("?*", '*'));
    for (char wildcard : {'?', '*'}) {
        string alphabet = string("ab") + wildcard;
        int count = 1;
        for (int n = 0; n <= 8; ++n, count *= 3) {
            for (int code = 0; code < count; ++code) {
                string s(n, 'a');
                int x = code;
                for (char& c : s) {
                    c = alphabet[x % 3];
                    x /= 3;
                }
                bool expected = brute_palindrome(s, wildcard);
                assert(is_palindrome(s, wildcard) == expected);
                assert(is_parindrome(s, wildcard) == expected);
                if (wildcard == '?') {
                    assert(is_palindrome(s) == expected);
                    assert(is_parindrome(s) == expected);
                }
                string reversed = s;
                reverse(reversed.begin(), reversed.end());
                assert(is_palindrome(s, '#') == (s == reversed));
                assert(is_parindrome(s, '#') == (s == reversed));
            }
        }
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    long long a, b;
    sc.read(a, b);
    pr.println(a + b);
}
