#ifndef FIRIEXP_LIBRARY_STRING_ROLLING_HASH_COMMON_CPP
#define FIRIEXP_LIBRARY_STRING_ROLLING_HASH_COMMON_CPP

namespace rolling_hash_detail {

template<long long Mod, class T>
long long symbol(T x) {
    static_assert(is_integral_v<T> && sizeof(T) <= 8);
    if constexpr (is_same_v<T, char> || is_same_v<T, signed char> || is_same_v<T, unsigned char>) {
        return static_cast<unsigned char>(x);
    } else if constexpr (is_signed_v<T>) {
        long long r = static_cast<long long>(x) % Mod;
        return r < 0 ? r + Mod : r;
    } else {
        return static_cast<unsigned long long>(x) % Mod;
    }
}

template<class Hash>
int lcp(const Hash& a, int l1, int r1, const Hash& b, int l2, int r2) {
    int low = 0, high = min(r1 - l1, r2 - l2);
    while (low < high) {
        int mid = high - (high - low) / 2;
        if (a.get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
        else high = mid - 1;
    }
    return low;
}

}

#endif

/**
 * @brief Rolling Hashの共通処理
 */
