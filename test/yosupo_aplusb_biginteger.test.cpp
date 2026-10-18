#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../util/biginteger.cpp"

string native_string(__int128 value, int base) {
    if (value == 0) return "0";
    bool negative = value < 0;
    if (negative) value = -value;
    string result;
    while (value) {
        int digit = value % base;
        result.push_back(char(digit < 10 ? '0' + digit : 'a' + digit - 10));
        value /= base;
    }
    if (negative) result.push_back('-');
    reverse(result.begin(), result.end());
    return result;
}

template<class BI> void check_small(int base) {
    vector<long long> values{LLONG_MIN, LLONG_MAX, 0, 1, -1, 99999999, 100000000,
                            4294967295LL, 4294967296LL, -4294967296LL};
    mt19937_64 rng(314159);
    for (int i = 0; i < 1500; ++i) values.push_back((long long)(rng() >> 3) - (1LL << 60));
    for (size_t i = 0; i < values.size(); ++i) {
        __int128 x = values[i], y = values[(i * 61 + 3) % values.size()];
        BI a(values[i]), b((long long)y);
        auto check = [&](const BI &value, __int128 expected) {
            assert(value.to_string(base) == native_string(expected, base));
        };
        check(a + b, x + y);
        check(a - b, x - y);
        check(a * b, x * y);
        BI alias = a;
        alias += alias; check(alias, x + x);
        alias = a; alias -= alias; check(alias, 0);
        alias = a; alias *= alias; check(alias, x * x);
        assert((a < b) == (x < y));
        assert((a == b) == (x == y));
        if (y) {
            auto qr = divmod(a, b);
            check(qr.first, x / y); check(qr.second, x % y);
            __int128 q = x / y, r = x % y;
            if (r && ((x < 0) != (y < 0))) { --q; r += y; }
            qr = floor_divmod(a, b);
            check(qr.first, q); check(qr.second, r);
        }
        if (x) {
            alias = a; alias /= alias; check(alias, 1);
            alias = a; alias %= alias; check(alias, 0);
        }
        for (int shift : {0, 1, 26, 27, 31, 32, 33, 63}) {
            __int128 power = __int128(1) << shift;
            check(a << shift, x * power);
            __int128 expected = x / power - (x < 0 && x % power != 0);
            check(a >> shift, expected);
        }
        check(a >> 1000000, x < 0 ? -1 : 0);
        if (i < 20) for (int radix = 2; radix <= 36; ++radix) {
            string s = native_string(x, radix);
            assert(a.to_string(radix) == s);
            assert(BI(s, radix) == a);
        }
    }
    for (string s : {"", "+", "-", "12?3", " 1", "1 ", "--1"}) {
        BI value(42);
        assert(!value.assign(s));
        assert(value.is_zero() && !value.is_negative());
    }
    for (string s : {"0", "-0", "+0000"}) {
        BI value(s);
        assert(value.is_zero() && !value.is_negative());
    }
}

template<class BI> void check_large(int base) {
    mt19937_64 rng(271828);
    auto random_value = [&](int limbs, int leading) {
        string s(8 * limbs, '0');
        for (char &c : s) c = "0123456789abcdef"[rng() % base];
        s[0] = "0123456789abcdef"[leading];
        return BI(s, base);
    };
    auto check = [&](const BI &b, const BI &q, const BI &r) {
        BI a = b * q + r;
        for (int signs = 0; signs < 4; ++signs) {
            BI dividend = signs & 1 ? -a : a;
            BI divisor = signs & 2 ? -b : b;
            auto qr = divmod(dividend, divisor);
            assert(qr.first == (((signs & 1) != ((signs >> 1) & 1)) ? -q : q));
            assert(qr.second == (signs & 1 ? -r : r));
        }
    };
    vector<pair<int, int>> sizes{{2, 5}, {63, 130}, {64, 129}, {65, 128},
        {511, 513}, {512, 513}, {513, 512}, {513, 513}, {1024, 512},
        {1024, 513}, {1025, 1025}, {513, 2000}, {4000, 65}, {2049, 2}, {700, 3300}};
    for (auto [m, n] : sizes) {
        for (int leading : {1, base / 2, base - 1}) {
            BI b = random_value(m, leading), q = random_value(n, base - 1);
            check(b, q, BI(0));
            check(b, q, BI(1));
            check(b, q, b - 1);
        }
    }
    for (int n : {65, 127, 128, 129, 255, 256, 257, 511, 512, 513, 1025}) {
        BI power("1" + string(8 * n, '0'), base);
        for (int delta : {-1, 0, 1}) {
            BI b = power + delta;
            check(b, power - 1, b - 1);
        }
    }
    BI power("1" + string(8 * 2048, '0'), base);
    BI b = (power + 1) * (power * power + 1);
    check(b, 2 * (power - 1), BI(0));
    check(b, 2 * (power - 1), b - 1);
    BI a = random_value(1400, base - 1);
    for (int shift : {31, 32, 33, 1000, 17000}) {
        BI scaled = a << shift;
        assert((scaled >> shift) == a);
        assert((-scaled >> shift) == -a);
        assert(((-scaled - 1) >> shift) == -a - 1);
    }
}

template<class Radix> void check_cyclic() {
    using Ops = BigIntegerDetail::Magnitude<Radix>;
    using Digits = typename Ops::Digits;
    for (size_t size : {2, 128, 65536}) {
        Digits a(size, static_cast<unsigned int>(Ops::BASE - 1));
        assert(Ops::cyclic_product(a, a, size).empty());
        assert(Ops::cyclic_difference(a, Digits{}, size).empty());
        --a[0];
        assert(Ops::cyclic_product(a, a, size) == Digits{1});
    }
}

void check_power_two_io() {
    const string alphabet = "0123456789abcdefghijklmnopqrstuv";
    const vector<int> bases{2, 4, 8, 16, 32};
    auto check = [&](const string &s, int base) {
        BigInteger expected(s, base);
        HexBigInteger actual(s, base);
        assert(actual.to_string(10) == expected.to_string());
        assert(actual.is_zero() == expected.is_zero());
        assert(actual.is_negative() == expected.is_negative());
        for (int output_base : bases) {
            string out = actual.to_string(output_base);
            assert(out == expected.to_string(output_base));
            assert(HexBigInteger(out, output_base) == actual);
        }
    };
    for (int bits = 0; bits <= 200; ++bits) {
        BigInteger power = BigInteger(1) << bits;
        for (int delta : {-1, 0, 1}) {
            BigInteger value = power + delta;
            for (int base : bases) {
                string s = value.to_string(base);
                check(s, base);
                check("-000" + s, base);
            }
        }
    }
    mt19937 rng(228);
    for (int tc = 0; tc < 2000; ++tc) {
        int base = bases[rng() % bases.size()];
        string s(rng() % 200 + 1, '0');
        for (char &c : s) {
            c = alphabet[rng() % base];
            if (c >= 'a' && rng() % 2) c += 'A' - 'a';
        }
        s = (tc % 3 == 0 ? "-000" : tc % 3 == 1 ? "+00" : "") + s;
        check(s, base);
    }
    for (int base : bases) {
        for (string s : {"0", "-000", "+00000"}) check(s, base);
        vector<string> invalid{"", "+", "-", "--1", " 1", "1 ", "1?0", string(1, char(128))};
        invalid.push_back(string(1, "0123456789abcdefghijklmnopqrstuvwxyz"[base]));
        invalid.push_back(string(100, '1') + "?");
        for (const string &s : invalid) {
            HexBigInteger value(-42);
            assert(!value.assign(s, base));
            assert(value.is_zero() && !value.is_negative());
        }
    }
    for (int base : {-1, 0, 1, 37}) {
        HexBigInteger value(-42);
        assert(!value.assign("10", base));
        assert(value.is_zero() && !value.is_negative());
    }
}

int main() {
    check_power_two_io();
    check_small<BigInteger>(10);
    check_small<HexBigInteger>(16);
    check_large<BigInteger>(10);
    check_large<HexBigInteger>(16);
    check_cyclic<BigIntegerDetail::DecimalRadix>();
    check_cyclic<BigIntegerDetail::HexRadix>();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
