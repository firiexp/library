template<class T>
class BIT {
    vector<T> bit;
    int n;
public:
    BIT(int n): n(n), bit(n){}

    T sum(int k){
        T ret = 0;
        for (; k > 0; k -= (k & -k)) ret += bit[k-1];
        return ret;
    }

    void add(int k, T x){
        for (++k; k < bit.size(); k  += (k & -k)) bit[k] += x;
    }
    
    T lower_bound(T x){
        int i = 0;
        for (int j = m; j > 0; j >>= 1) {
            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];
        }
        return i;
    }
};
/**
 * @brief BinaryIndexedTree (BIT)
 * @docs _md/binaryindexedtree.md
 */