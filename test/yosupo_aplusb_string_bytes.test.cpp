#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr ull M = (1ULL << 61) - 1;
enum { MASK30, MASK31, rd };
#include "../util/fastio.cpp"
#include "../string/rolling_hash.cpp"
#include "../string/rolling_hash_ull.cpp"
#include "../string/lyndon_factorization.cpp"

constexpr int MOD = 1000000007;

void hash_check(const string &s) {
    const rolling_hash<MOD> small(s);
    const rolling_hash_ull large(s);
    for (int l = 0; l <= int(s.size()); ++l) {
        ull expected_small = 0, expected_large = 0;
        for (int r = l; r <= int(s.size()); ++r) {
            if (r > l) {
                unsigned char byte = s[r - 1];
                expected_small = (expected_small * 127 + byte) % MOD;
                expected_large = ((__uint128_t)expected_large * 127 + byte) % M;
            }
            const string sub = s.substr(l, r - l);
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

void standalone_hash_check() {
    mt19937 rng(179);
    for (int n : {0, 1, 255, 1024}) {
        string s(n, '\0');
        ull expected = 0;
        for (char &c : s) {
            c = char(rng() % 256);
            expected = ((__uint128_t)expected * rolling_hash_ull::B() + (unsigned char)c) % M;
        }
        for (int prepared : {1, n + 20}) {
            rolling_hash_ull::p() = {1, rolling_hash_ull::B()};
            rolling_hash_ull precompute(prepared);
            const auto powers = rolling_hash_ull::p();
            const auto capacity = rolling_hash_ull::p().capacity();
            assert(rolling_hash_ull::val(s) == expected);
            assert(rolling_hash_ull::p() == powers);
            assert(rolling_hash_ull::p().capacity() == capacity);
            rolling_hash_ull rh(s);
            assert(rh.get(0, n) == expected);
            rolling_hash_ull grow(n + 100);
            assert(rolling_hash_ull::p().size() >= size_t(n + 101));
            assert(rh.get(0, n) == expected);
        }
    }
}

void large_base_hash_check() {
    mt19937_64 rng(224);
    for (ull base : {2ULL, 911382323ULL, M / 2, M - 2, M - 1}) {
        rolling_hash_ull::B() = base;
        rolling_hash_ull::p() = {1, base};
        for (int tc = 0; tc < 100; ++tc) {
            string s(tc, '\0');
            for (char &c : s) c = char(rng() % 256);
            rolling_hash_ull rh(s);
            for (int l = 0; l <= int(s.size()); ++l) {
                ull expected = 0;
                for (int r = l; r <= int(s.size()); ++r) {
                    if (r > l) expected = ((__uint128_t)expected * base + (unsigned char)s[r - 1]) % M;
                    assert(rh.get(l, r) == expected);
                }
            }
            assert(rolling_hash_ull::val(s) == rh.get(0, s.size()));
        }
    }
    rolling_hash_ull::B() = 127;
    rolling_hash_ull::p() = {1, 127};
}

template<class Hash, class T>
void check_symbols(const vector<T>& input, const vector<__int128_t>& symbols, ull mod) {
    const Hash hash(input);
    int n = input.size();
    assert(symbols.size() == input.size());
    for (int l = 0; l <= n; ++l) {
        __int128_t expected = 0;
        for (int r = l; r <= n; ++r) {
            if (r > l) {
                expected = (expected * Hash::B() + symbols[r - 1]) % mod;
                if (expected < 0) expected += mod;
            }
            assert(hash.get(l, r) == expected);
        }
    }
    assert(Hash::val(input) == hash.get(0, n));
}

template<class Hash>
void check_ranges(const string& a, const string& b) {
    const string padded = "(" + b + ")";
    const string_view view(padded.data() + 1, b.size());
    const Hash first(a), second(view);
    assert(Hash::val(view) == second.get(0, b.size()));
    for (int l = 0; l <= int(a.size()); ++l) {
        for (int r = l; r <= int(a.size()); ++r) {
            for (int i = 0; i <= int(b.size()); ++i) {
                for (int j = i; j <= int(b.size()); ++j) {
                    int length = 0;
                    while (l + length < r && i + length < j && a[l + length] == b[i + length]) ++length;
                    assert(first.lcp(l, r, second, i, j) == length);
                    auto joined = Hash::concat(first.get(l, r), second.get(i, j), j - i);
                    assert(joined == Hash::val(a.substr(l, r - l) + b.substr(i, j - i)));
                }
            }
        }
    }
}

template<class Hash>
void api_check(ull mod) {
    const Hash literal("abc");
    assert(literal.get(0, 3) == Hash::val("abc"));
    const vector<int> numbers = {-1, 0, 1, -1};
    const vector<ull> residues = {mod - 1, 0, 1};
    const Hash integer_hash(numbers), residue_hash(residues);
    assert(integer_hash.lcp(0, 4, residue_hash, 0, 3) == 3);
    assert(Hash::val(numbers) == Hash::concat(Hash::val(residues), Hash::val(vector<int>{-1}), 1));

    check_symbols<Hash>(vector<char>{char(255), 0, char(128)}, {255, 0, 128}, mod);
    check_symbols<Hash>(vector<signed char>{-1, -128, 0, 1}, {255, 128, 0, 1}, mod);
    check_symbols<Hash>(vector<unsigned char>{0, 128, 255}, {0, 128, 255}, mod);
    check_symbols<Hash>(vector<bool>{true, false, true}, {1, 0, 1}, mod);
    check_symbols<Hash>(vector<short>{-1, 10}, {-1, 10}, mod);
    check_symbols<Hash>(vector<ll>{LLONG_MIN, -1, ll(mod), LLONG_MAX}, {LLONG_MIN, -1, mod, LLONG_MAX}, mod);
    check_symbols<Hash>(vector<ull>{ULLONG_MAX, mod + 1, 0}, {ULLONG_MAX, mod + 1, 0}, mod);
    check_symbols<Hash>(vector<int>{}, {}, mod);

    const string tail(500, 'z');
    Hash::p() = {1, Hash::B()};
    auto h = Hash::concat(Hash::val("x"), Hash::val(tail), tail.size());
    assert(h == Hash::val("x" + tail));
    assert(Hash::p().size() > tail.size());

    check_ranges<Hash>("banana", "ananas");
    check_ranges<Hash>("", "");
    check_ranges<Hash>(string("a\0\xff", 3), string("\0\xff!", 3));
    mt19937 rng(516);
    for (int t = 0; t < 80; ++t) {
        string a(rng() % 9, 'a'), b(rng() % 9, 'a');
        for (char& c : a) c += rng() % 3;
        for (char& c : b) c += rng() % 3;
        check_ranges<Hash>(a, b);
    }
}

int main() {
    static_assert(is_convertible_v<const string&, rolling_hash_ull>);
    using Other = rolling_hash<1000000009>;
    {
        const Other other("abc");
        const rolling_hash_ull first("abc"), second("zabc");
        assert(other.lcp(0, 3, Other("zabc"), 1, 4) == 3);
        assert(first.lcp(0, 3, second, 1, 4) == 3);
    }
    rolling_hash<MOD>::B() = 911382323;
    rolling_hash_ull::B() = 911382323;
    rolling_hash_ull::p() = {1, 911382323};
    api_check<rolling_hash<MOD>>(MOD);
    api_check<rolling_hash_ull>(M);
    check_symbols<rolling_hash<3>>(vector<unsigned char>{255, 254, 128}, {255, 254, 128}, 3);
    rolling_hash<INT_MAX>::B() = INT_MAX - 1;
    check_symbols<rolling_hash<INT_MAX>>(vector<ull>{ULLONG_MAX, 0, INT_MAX - 1},
                                         {ULLONG_MAX, 0, INT_MAX - 1}, INT_MAX);
    rolling_hash_ull::B() = M - 1;
    rolling_hash_ull::p() = {1, M - 1};
    check_symbols<rolling_hash_ull>(vector<ull>{M - 1, M - 2, ULLONG_MAX}, {M - 1, M - 2, ULLONG_MAX}, M);
    rolling_hash<MOD>::B() = 127;
    rolling_hash<MOD>::p() = {1, 127};
    rolling_hash_ull::B() = 127;
    assert(rolling_hash_ull::val("ab") == 'a' * 127 + 'b');
    large_base_hash_check();
    standalone_hash_check();
    shared_powers_check();
    hash_check(string{char(255), char(127), 1, 1, 1, 1, 1});
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
}
