#include "prime/get_prime.cpp"

template<class T>
void gcd_transform(vector<T> &v){
    if (v.size() <= 2) return;
    int r = (int)v.size() - 1;
    for (int p : get_prime(r)) {
        for (int j = r / p; j != 0; --j) v[j] += v[j * p];
    }
}

template<class T>
void gcd_itransform(vector<T> &v){
    if (v.size() <= 2) return;
    int r = (int)v.size() - 1;
    for (int p : get_prime(r)) {
        int limit = r / p;
        for (int j = 1; j <= limit; ++j) v[j] -= v[j * p];
    }
}
