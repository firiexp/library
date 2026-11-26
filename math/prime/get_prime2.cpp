#ifndef FIRIEXP_LIBRARY_MATH_PRIME_GET_PRIME2_CPP
#define FIRIEXP_LIBRARY_MATH_PRIME_GET_PRIME2_CPP

#include "linear_sieve.cpp"

template<typename T>
struct ExactDiv {
    T t, i, val;
    ExactDiv() {}
    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n)) , val(n) {};
    T mul_inv(T n) {
        T x = n;
        for (int i = 0; i < 5; ++i) x *= 2 - n * x;
        return x;
    }
    bool divide(T n) const {
        if(val == 2) return !(n & 1);
        return n * this->i <= this->t;
    }
};

vector<ExactDiv<uint>> get_prime_exact_div(int n) {
    vector<ExactDiv<uint>> res;
    auto primes = LinearSieve(n).primes;
    res.reserve(primes.size());
    for (auto &&p : primes) res.emplace_back((uint)p);
    return res;
}

#endif

/**
 * @brief 高速素数列挙(ExactDiv)
 */
