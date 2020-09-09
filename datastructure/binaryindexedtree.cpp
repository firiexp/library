template<class T>
class BIT {
    vector<T> bit;
    int n, m;
public:
    BIT(int n): n(n), bit(n){
        m = 1;
        while(m < n) m <<= 1;
    }

    T sum(int k){
        T ret = 0;
        for (; k > 0; k -= (k & -k)) ret += bit[k-1];
        return ret;
    }

    void add(int k, T x){
        for (k++; k <= bit.size(); k  += (k & -k)) bit[k-1] += x;
    }

    T lower_bound(T x){
        int i = -1;
        for (int j = m; j; j >>= 1) {
            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];
        }
        return i;
    }
};