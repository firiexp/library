#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../string/rolling_hash.cpp"
#include "../string/rolling_hash_ull.cpp"
#include "../string/lyndon_factorization.cpp"

constexpr int MOD = 1000000007;

void hash_check(const string &s) {
    rolling_hash<MOD> small(s);
    rolling_hash_ull large(s);
    for (int l = 0; l <= int(s.size()); ++l) {
        ull expected_small = 0, expected_large = 0;
        for (int r = l; r <= int(s.size()); ++r) {
            if (r > l) {
                unsigned char byte = s[r - 1];
                expected_small = (expected_small * 127 + byte) % MOD;
                expected_large = ((__uint128_t)expected_large * 127 + byte) % M;
            }
            string sub = s.substr(l, r - l);
            rolling_hash<MOD> small_sub(sub);
            rolling_hash_ull large_sub(sub);
            assert(small.get(l, r) == ll(expected_small));
            assert(small_sub.get(0, sub.size()) == ll(expected_small));
            assert(large.get(l, r) == expected_large);
            assert(large_sub.get(0, sub.size()) == expected_large);
            assert(rolling_hash_ull::val(sub) == expected_large);
        }
    }
}

void lyndon_check(const string &s) {
    auto factors = lyndon_factorization(s);
    int end = 0;
    string previous;
    for (auto [l, r] : factors) {
        assert(l == end && l < r && r <= int(s.size()));
        string word = s.substr(l, r - l);
        for (int i = 1; i < int(word.size()); ++i) assert(word < word.substr(i));
        if (l > 0) assert(previous >= word);
        previous = word;
        end = r;
    }
    assert(end == int(s.size()));
}

void shared_powers_check() {
    string s(64, 'a');
    rolling_hash_ull original(s);
    ull expected = rolling_hash_ull::val(s);
    size_t size = rolling_hash_ull::p().size();
    for (int n : {0, 1, 0, 32}) {
        rolling_hash_ull precompute(n);
        assert(rolling_hash_ull::p().size() == size);
        assert(original.get(0, s.size()) == expected);
        assert(original.get(1, 2) == 'a');
    }
    rolling_hash_ull grow(200);
    assert(rolling_hash_ull::p().size() >= 201);
    assert(original.get(0, s.size()) == expected);
    hash_check("abc");
    hash_check(string(80, '\0'));
}

int main() {
    rolling_hash<MOD>::B() = 127;
    rolling_hash_ull::B() = 127;
    shared_powers_check();
    hash_check(string{char(255), char(127), 1, 1, 1, 1, 1});
    // The unreduced product in get(17, 28) exceeds hash[28] + 3*M.
    string subtraction_case;
    for (int byte : {52, 238, 54, 138, 29, 92, 151, 22, 86, 21, 6, 9, 155, 217, 111, 94,
                    133, 220, 239, 101, 237, 127, 15, 83, 108, 190, 213, 198, 175, 154, 9, 95})
        subtraction_case += char(byte);
    hash_check(subtraction_case);
    const unsigned char alphabet[] = {0, 127, 128, 255};
    for (int n = 0, count = 1; n <= 6; ++n, count *= 4) {
        for (int mask = 0; mask < count; ++mask) {
            string s(n, '\0');
            int digits = mask;
            for (char &c : s) {
                c = char(alphabet[digits % 4]);
                digits /= 4;
            }
            lyndon_check(s);
            if (n <= 5) hash_check(s);
        }
    }
    mt19937 rng(57);
    for (int tc = 0; tc < 100; ++tc) {
        string s(rng() % 40, '\0');
        for (char &c : s) c = char(rng() % 256);
        hash_check(s);
        lyndon_check(s);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
