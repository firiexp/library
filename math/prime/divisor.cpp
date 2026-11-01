template<class T>
vector<T> divisor(T n){
    vector<T> ret;
    for(T i = 1; ; i++) {
        T q = n / i;
        if(i > q) break;
        if(n - q * i == 0) {
            ret.push_back(i);
            if(i != q) ret.push_back(q);
        }
    }
    sort(begin(ret), end(ret));
    return(ret);
}

template<class T>
vector<T> divisor_from_factors(const vector<T> &factors) {
    vector<T> ret{1};
    for (size_t i = 0; i < factors.size();) {
        size_t size = ret.size();
        T p = factors[i], power = 1;
        do {
            power *= p;
            for (size_t j = 0; j < size; ++j) ret.push_back(ret[j] * power);
            ++i;
        } while (i < factors.size() && factors[i] == p);
    }
    sort(ret.begin(), ret.end());
    return ret;
}
