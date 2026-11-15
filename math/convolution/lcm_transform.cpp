#ifndef FIRIEXP_LIBRARY_MATH_CONVOLUTION_LCM_TRANSFORM_CPP
#define FIRIEXP_LIBRARY_MATH_CONVOLUTION_LCM_TRANSFORM_CPP

#include "../prime/get_prime.cpp"

namespace lcm_transform_detail {
template<bool Inverse, class T>
void transform(vector<T>& v, const vector<int>& primes) {
    int n = (int)v.size() - 1;
    for (int p : primes) {
        int limit = n / p;
        if constexpr (Inverse) {
            for (int i = limit; i > 0; --i) v[i * p] -= v[i];
        } else {
            for (int i = 1; i <= limit; ++i) v[i * p] += v[i];
        }
    }
}
}

template<class T>
void lcm_transform(vector<T>& v) {
    if (v.size() <= 2) return;
    lcm_transform_detail::transform<false>(v, get_prime((int)v.size() - 1));
}

template<class T>
void lcm_itransform(vector<T>& v) {
    if (v.size() <= 2) return;
    lcm_transform_detail::transform<true>(v, get_prime((int)v.size() - 1));
}

template<class T>
vector<T> lcm_convolution(const vector<T>& a, const vector<T>& b, int limit) {
    assert(limit >= 0);
    vector<T> result((size_t)limit + 1);
    if (limit == 0 || a.size() <= 1 || b.size() <= 1) return result;
    vector<T> other((size_t)limit + 1);
    for (int i = 1; i <= limit && i < (int)a.size(); ++i) result[i] = a[i];
    for (int i = 1; i <= limit && i < (int)b.size(); ++i) other[i] = b[i];
    auto primes = get_prime(limit);
    lcm_transform_detail::transform<false>(result, primes);
    lcm_transform_detail::transform<false>(other, primes);
    for (int i = 1; i <= limit; ++i) result[i] *= other[i];
    lcm_transform_detail::transform<true>(result, primes);
    return result;
}

#endif

/**
 * @brief 約数の総和変換とLCM畳み込み
 */
