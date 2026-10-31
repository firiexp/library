#include "../prime/get_prime.cpp"

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

template<class T>
vector<T> gcd_convolution(vector<T> a, vector<T> b) {
    int n = max(a.size(), b.size());
    if (a.size() <= 1 || b.size() <= 1) return vector<T>(n);
    a.resize(n);
    b.resize(n);
    a[0] = b[0] = T(0);
    gcd_transform(a);
    gcd_transform(b);
    for (int i = 1; i < n; ++i) a[i] *= b[i];
    gcd_itransform(a);
    return a;
}
