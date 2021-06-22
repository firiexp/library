vector<int> eulerphi_all(int M){
    vector<int> phi(M);
    vector<bool> isprime(M);
    for (int i = 0; i < M; ++i) {
        mobius[i] = isprime[i] = 1;
    }
    for (int i = 2; i < M; ++i) {
        if(isprime[i]){
            for (int j = i; j < M; j += i) {
                phi[j] -= phi[j]/i;
                isprime[j] = 0;
            }
            isprime[i] = 1;
        }
    }
    return phi;
}