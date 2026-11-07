int eulerphi(int x){
    int phi = x, xx = x;
    for (int i = 2; 1LL * i * i <= xx; ++i) {
        if (xx % i == 0) {
            phi -= phi / i;
            while(xx % i == 0) xx /= i;
        }
    }
    if(xx > 1) phi -= phi/xx;
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
