namespace primefactor_trial_detail {

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
        return n * this->i <= this->t;
    }
};

vector<ExactDiv<uint>> get_odd_primes(uint n){
    vector<bool> is_prime(n+1, true);
    vector<ExactDiv<uint>> prime;
    for (uint i = 3; i <= n; i += 2) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j.val > n) break;
            is_prime[i*j.val] = false;
            if(j.divide(i)) break;
        }
    }
    return prime;
}
const auto odd_primes = get_odd_primes(46340);

}

template<class T>
vector<T> prime_factor_trial(T n) {
    static_assert(std::numeric_limits<T>::is_integer);
    if (n < 1 || n > INT_MAX) std::abort();
    vector<T> res;
    uint remaining = static_cast<uint>(n);
    while (remaining % 2 == 0) {
        res.emplace_back(2);
        remaining /= 2;
    }
    if (remaining == 1) return res;
    const auto &primes = primefactor_trial_detail::odd_primes;
    const auto end = std::upper_bound(primes.begin(), primes.end(), remaining,
        [](uint value, const auto &p) { return value < p.val * p.val; });
    for (auto p = primes.begin(); p != end; ++p) {
        while (p->divide(remaining)) {
            res.emplace_back(p->val);
            remaining /= p->val;
            if (remaining == 1) return res;
        }
    }
    res.emplace_back(remaining);
    return res;
}

/**
 * @brief 素因数分解(試し割り)
 */
