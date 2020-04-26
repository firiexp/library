vector<int> mobius_all(int M){
    vector<int> mobius(M), isprime(M);
    for (int i = 0; i < M; ++i) {
        mobius[i] = isprime[i] = 1;
    }
    for (int i = 2; i < M; ++i) {
        if(isprime[i]){
            for (int j = i; j < M; j += i) {
                mobius[j] = -mobius[j];
                isprime[j] = 0;
            }
            isprime[i] = 1;
            ll x = (ll)i*i;
            if(x <= M){
                for (int j = x; j < M; j += x) {
                    mobius[j] = 0;
                }
            }
        }
    }
    return mobius;
}