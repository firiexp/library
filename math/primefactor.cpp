vector<int> get_prime(int n){
    if(n <= 1) return vector<int>();
    vector<bool> is_prime(n+1, true);
    vector<int> prime;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j > n) break;
            is_prime[i*j] = false;
            if(i % j == 0) break;
        }
    }
    return prime;
}
const auto primes = get_prime(65535);

template<class T>
vector<T> prime_factor(T n){
    vector<T> res;
    for (auto &&i : primes) {
        while (n % i == 0){
            res.emplace_back(i);
            n /= i;
        }
    }
    if(n != 1) res.emplace_back(n);
    return res;
}