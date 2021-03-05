struct Prime { // Wheel factorization
    static constexpr int wheel[] = {4, 2, 4, 2, 4, 6, 2, 6},
            wheel2[] = {7, 11, 13, 17, 19, 23, 29, 31},
            wheel_sum[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7};
    static inline int f(int n){ return (n-1)/30*8 + wheel_sum[(n-1)%30]; }
    static inline int g(int n){ return ((n-1) >> 3)*30 + wheel2[(n-1)&7]; }
    vector<ll> primes;

    Prime(int M) {
        primes = {2, 3, 5};
        if(M < 7){
            while(!primes.empty() && M < primes.back()) primes.pop_back();
            return;
        }
        int n = f(M), m = g(n), k = f(int(floor(sqrt(M))));
        primes.reserve(3+max(0, (int)(n/(log(n)-1.12))));
        vector<bool> sieve(n+1, true);
        for (int i = 1; i <= k; ++i) {
            if(sieve[i]){
                ll p = g(i), q = p*p;
                int j = (i-1)&7;
                while(q <= m){
                    sieve[f(q)] = false;
                    q += wheel[j] * p;
                    j = (j+1)&7;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            if(sieve[i]) primes.emplace_back(g(i));
        }
    }
};
constexpr int Prime::wheel[], Prime::wheel2[], Prime::wheel_sum[];

