template<class T>
class BIT {
    vector<T> bit;
    int m, n;
public:
    BIT(int n): bit(n), m(1), n(n) {
        while (m < n) m <<= 1;
    }

    T sum(int k){
        T ret = 0;
        for (; k > 0; k -= (k & -k)) ret += bit[k - 1];
        return ret;
    }

    void add(int k, T x){
        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;
    }

    int lower_bound(T x) {
        if (x <= 0) return 0;
        int i = 0;
        for (int j = m; j; j >>= 1) {
            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j - 1], i += j;
        }
        return min(i + 1, n);
    }
};
