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
