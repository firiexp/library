ll totient(ll n){
    ll res = n;
    for (ll i = 2; i*i <= n; ++i) {
        if(n%i == 0){
            res = res/i*(i-1);
            while(n%i == 0) n /= i;
        }
    }
    if(n > 1) res = res/n*(n-1);
    return res;
}

template <class T>
T pow_tetration(T x, T n, T M, bool &yojo){
    uint64_t u = 1, xx = x;
    if(x >= M) yojo = true;
    while (n > 0){
        if (n&1) {
            u = u * xx;  
            if(u >= M) yojo = true, u %= M;
        }
        if(!(n >>= 1)) break;
        xx = xx * xx;
        if(xx >= M) yojo = true, xx %= M;
    }
    return static_cast<T>(u);
};

ll tetration(ll a, ll n, const ll M, bool &yojo) {
    if(a == 0) return !(n&1);
    if(M == 1) return yojo = true, 1;
    if(a == 1 || n == 0) return 1;
    ll expo = tetration(a, n-1, totient(M), yojo);
    ll res = pow_tetration(a, expo, M, yojo);
    return res + (yojo ? M : 0);
}

ll tetration(ll a, ll n, const ll M){
    bool yojo = false;
    return tetration(a, n, M, yojo)%M;
}
