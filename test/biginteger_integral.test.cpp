#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/biginteger.cpp"
#include "../util/biginteger.cpp"

template<class T>
string integer_string(T value) {
    bool negative = false;
    if constexpr (numeric_limits<T>::is_signed) negative = value < 0;
    unsigned __int128 magnitude = value;
    if (negative) magnitude = 0 - magnitude;
    string result;
    do {
        result += char('0' + magnitude % 10);
        magnitude /= 10;
    } while (magnitude);
    if (negative) result += '-';
    reverse(result.begin(), result.end());
    return result;
}

template<class BI, class T>
void check_value(T value) {
    string expected = integer_string(value);
    BI constructed(value), parsed(expected, 10), assigned(-42);
    assert(constructed.to_string(10) == expected);
    assert(constructed == parsed);
    assert(constructed.template to_integral<T>() == optional<T>(value));
    assert(parsed.template to_integral<T>() == optional<T>(value));
    assigned = value;
    assert(assigned == parsed && assigned.template to_integral<T>() == optional<T>(value));
    assert(assigned.is_negative() == (expected[0] == '-'));
    assigned = 0;
    assert(assigned.is_zero() && !assigned.is_negative());
}

template<class BI, class T>
void check_type() {
    T lo = numeric_limits<T>::min(), hi = numeric_limits<T>::max();
    for (T value : {lo, T(lo + 1), T(0), T(1), T(hi - 1), hi}) check_value<BI>(value);
    if constexpr (numeric_limits<T>::is_signed) check_value<BI>(T(-1));
    BI lower(integer_string(lo), 10), upper(integer_string(hi), 10);
    assert(!(lower - 1).template to_integral<T>());
    assert(!(upper + 1).template to_integral<T>());
    assert((lower + 1).template to_integral<T>() == optional<T>(T(lo + 1)));
    assert((upper - 1).template to_integral<T>() == optional<T>(T(hi - 1)));
    assert(!(upper + (BI(1) << 256)).template to_integral<T>());
    assert(!(lower - (BI(1) << 256)).template to_integral<T>());
}

template<class BI>
void check_all() {
    check_type<BI, bool>();
    check_type<BI, char>();
    check_type<BI, signed char>();
    check_type<BI, unsigned char>();
    check_type<BI, short>();
    check_type<BI, unsigned short>();
    check_type<BI, int>();
    check_type<BI, unsigned int>();
    check_type<BI, long>();
    check_type<BI, unsigned long>();
    check_type<BI, long long>();
    check_type<BI, unsigned long long>();
    check_type<BI, wchar_t>();
    check_type<BI, char16_t>();
    check_type<BI, char32_t>();
    check_type<BI, __int128>();
    check_type<BI, unsigned __int128>();
    for (int v = -512; v <= 512; ++v) {
        BI x(v);
        auto signed_value = x.template to_integral<signed char>();
        auto unsigned_value = x.template to_integral<unsigned char>();
        assert(bool(signed_value) == (SCHAR_MIN <= v && v <= SCHAR_MAX));
        assert(bool(unsigned_value) == (0 <= v && v <= UCHAR_MAX));
        if (signed_value) assert(*signed_value == v);
        if (unsigned_value) assert(*unsigned_value == v);
    }
    for (unsigned long long value : {99999999ULL, 100000000ULL, 100000001ULL,
                                    4294967295ULL, 4294967296ULL, 4294967297ULL,
                                    10000000000000000ULL, 1ULL << 63, ULLONG_MAX}) {
        check_value<BI>(value);
        BI x(integer_string(value), 10);
        auto signed_value = x.template to_integral<long long>();
        assert(bool(signed_value) == (value <= (unsigned long long)LLONG_MAX));
        if (signed_value) assert(*signed_value == (long long)value);
        assert(!(-x).template to_integral<unsigned long long>());
    }
    mt19937_64 rng(356);
    for (int i = 0; i < 5000; ++i) {
        unsigned long long value = rng();
        check_value<BI>(value);
        check_value<BI>(static_cast<long long>(value & LLONG_MAX));
        check_value<BI>(-static_cast<long long>(value & LLONG_MAX));
        unsigned __int128 wide = (static_cast<unsigned __int128>(value) << 64) | rng();
        check_value<BI>(wide);
        __int128 signed_wide = __int128(wide >> 1);
        check_value<BI>(signed_wide);
        check_value<BI>(-signed_wide);
    }
    BI zero = 0, one = 1, large = ULLONG_MAX;
    assert(zero + 1 == one && 1 + zero == one && large - ULLONG_MAX == zero);
    BI copy = large, moved = std::move(copy);
    copy = moved;
    assert(copy == large && moved == large);
    copy = std::move(moved);
    assert(copy == large);
    BI negative_zero("-0");
    assert(negative_zero.template to_integral<unsigned long long>() == optional<unsigned long long>(0));
}

int main() {
    check_all<BigInteger>();
    check_all<HexBigInteger>();
}
