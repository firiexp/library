template<class T>
void fwht(vector<T> &v){
    int sz = 1;
    while(sz < v.size()) sz <<= 1;
    v.resize(sz);
    for (int i = 1; i < sz; i <<= 1) {
        for (int j = 0; j < sz; j += (i<<1)) {
            for (int k = 0; k < i; ++k) {
                T x = v[j+k], y = v[j+k+i];
                v[j+k] = (x+y), v[j+k+i] = (x-y);
            }
        }
    }
}

namespace fwht_detail {
template<class T>
auto inverse(vector<T> &v, int) -> decltype(T(1).inv(), void()) {
    fwht(v);
    T inverse_size = T(v.size()).inv();
    for (auto &x : v) x *= inverse_size;
}

template<class T>
void inverse(vector<T> &v, long) {
    int sz = 1;
    while(sz < v.size()) sz <<= 1;
    v.resize(sz);
    for (int i = 1; i < sz; i <<= 1) {
        for (int j = 0; j < sz; j += (i<<1)) {
            for (int k = 0; k < i; ++k) {
                T x = v[j+k], y = v[j+k+i];
                v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;
            }
        }
    }
}
}

template<class T>
void ifwht(vector<T> &v) {
    fwht_detail::inverse(v, 0);
}

template<class T>
vector<T> xor_convolution(vector<T> a, vector<T> b) {
    int n = 1;
    while (n < (int)a.size() || n < (int)b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);
    fwht(a);
    fwht(b);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    ifwht(a);
    return a;
}

/**
 * @brief 高速Walsh-Hadamard変換(FWHT)
 */
