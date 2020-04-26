template <class T>
T pow_ (T x, T n, T M){
    uint64_t u = 1, xx = x;
    while (n > 0){
        if (n&1) u = u * xx % M;
        xx = xx * xx % M;
        n >>= 1;
    }
    return static_cast<T>(u);
};


template<typename T>
T extgcd(T a, T b, T &x ,T &y){
    for (T u = y = 1, v = x = 0; a; ) {
        ll q = b/a;
        swap(x -= q*u, u);
        swap(y -= q*v, v);
        swap(b -= q*a, a);
    }
    return b;
}

template<typename T>
T mod_inv(T x, T m){
    T s, t;
    extgcd(x, m, s, t);
    return (m+s)% m;
}

ll Garner(vector<pair<ll, ll>> a, ll mod){
    a.emplace_back(0, mod);
    vector<ll> A(a.size(), 1), B(a.size(), 0);
    for (int i = 0; i < a.size(); ++i) {
        ll t = (a[i].first+a[i].second-B[i])* mod_inv(A[i], a[i].second) % a[i].second;
        for (int j = i+1; j < a.size() ; ++j) {
            (B[j] += t * A[j]) %= a[j].second;
            (A[j] *= a[i].second) %= a[j].second;
        }
    }
    return B.back();
}
