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
    vector<T> divisors{1}, buffer;
    for (size_t i = 0; i < factors.size();) {
        T p = factors[i];
        size_t end = i + 1;
        while (end < factors.size() && factors[end] == p) ++end;
        size_t run_size = divisors.size();
        size_t total = run_size * (end - i + 1);
        divisors.resize(total, p);
        for (size_t j = run_size; j < total; ++j) divisors[j] = divisors[j - run_size] * p;

        if (run_size > 1) {
            buffer.resize(total, p);
            for (size_t width = run_size; width < total; width *= 2) {
                for (size_t left = 0; left < total; left += 2 * width) {
                    size_t mid = min(left + width, total);
                    size_t right = min(left + 2 * width, total);
                    merge(divisors.begin() + left, divisors.begin() + mid,
                          divisors.begin() + mid, divisors.begin() + right, buffer.begin() + left);
                }
                divisors.swap(buffer);
            }
        }
        i = end;
    }
    return divisors;
}

/**
 * @brief 約数列挙(Divisor)
 */
