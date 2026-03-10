template<class T>
void subset_zeta_transform(vector<T> &v){
    int n = 1;
    while (n < (int)v.size()) n <<= 1;
    v.resize(n);
    for (int i = 1; i < n; i <<= 1) {
        for (int s = 0; s < n; ++s) {
            if ((s & i) == 0) v[s | i] += v[s];
        }
    }
}

template<class T>
void subset_mobius_transform(vector<T> &v){
    int n = 1;
    while (n < (int)v.size()) n <<= 1;
    v.resize(n);
    for (int i = 1; i < n; i <<= 1) {
        for (int s = 0; s < n; ++s) {
            if ((s & i) == 0) v[s | i] -= v[s];
        }
    }
}

template<class T>
vector<T> or_convolution(vector<T> a, vector<T> b){
    int n = 1;
    while (n < (int)a.size() || n < (int)b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);
    subset_zeta_transform(a);
    subset_zeta_transform(b);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    subset_mobius_transform(a);
    return a;
}

/**
 * @brief OR畳み込み(Bitwise OR Convolution)
 */
