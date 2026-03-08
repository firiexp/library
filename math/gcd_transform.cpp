template<class T>
void gcd_transform(vector<T> &v){
    int r = (int)v.size() - 1;
    vector<bool> sieve(v.size());
    for (int i = 2; i <= r; ++i) {
        if(!sieve[i]){
            for (int j = r/i; j != 0; --j) {
                if(j != 1) sieve[j*i] = true;
                v[j] += v[j*i];
            }
        }
    }
}

template<class T>
void gcd_itransform(vector<T> &v){
    int r = (int)v.size() - 1;
    vector<bool> sieve(v.size());
    for (int i = 2; i <= r; ++i) {
        if(!sieve[i]){
            for (int j = 1; j*i <= r; ++j) {
                if(j != 1) sieve[j*i] = true;
                v[j] -= v[j*i];
            }
        }
    }
}
