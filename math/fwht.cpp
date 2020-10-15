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

template<class T>
void ifwht(vector<T> &v){
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