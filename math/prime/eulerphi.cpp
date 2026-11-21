#ifndef FIRIEXP_LIBRARY_MATH_PRIME_EULERPHI_CPP
#define FIRIEXP_LIBRARY_MATH_PRIME_EULERPHI_CPP

template<class T>
T eulerphi(T x) {
    T phi = x;
    for (T p = 2; ; ++p) {
        T quotient = x / p;
        if (p > quotient) break;
        if (quotient * p != x) continue;
        phi -= phi / p;
        x = quotient;
        while (x % p == 0) x /= p;
    }
    if (x > 1) phi -= phi / x;
    return phi;
}

template<class T>
T eulerphi_from_factors(const vector<T> &factors) {
    T phi = 1, previous = 0;
    for (T p : factors) {
        phi *= p == previous ? p : p - 1;
        previous = p;
    }
    return phi;
}

/**
 * @brief オイラーのφ関数(Euler Phi)
 */

#endif
