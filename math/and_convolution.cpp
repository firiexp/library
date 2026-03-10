template<class T>
void superset_zeta_transform(vector<T> &v){
    int n = 1;
    while (n < (int)v.size()) n <<= 1;
    v.resize(n);
    for (int i = 1; i < n; i <<= 1) {
        for (int s = 0; s < n; ++s) {
            if (s & i) v[s ^ i] += v[s];
        }
    }
}

template<class T>
void superset_mobius_transform(vector<T> &v){
    int n = 1;
    while (n < (int)v.size()) n <<= 1;
    v.resize(n);
    for (int i = 1; i < n; i <<= 1) {
        for (int s = 0; s < n; ++s) {
            if (s & i) v[s ^ i] -= v[s];
        }
    }
}

template<class T>
vector<T> and_convolution(vector<T> a, vector<T> b){
    int n = 1;
    while (n < (int)a.size() || n < (int)b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);
    superset_zeta_transform(a);
    superset_zeta_transform(b);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    superset_mobius_transform(a);
    return a;
}

/**
 * @brief AND畳み込み(Bitwise AND Convolution)
 */
