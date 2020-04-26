class Fast_Kitamasa {
    poly c, b, ic;
    int k;
    int mod;
public:
    explicit Fast_Kitamasa(vector<int> &c, int mod) : c(c), mod(mod){
        k = static_cast<int>(c.size() - 1);
        calc_ic();
    }
    void multiply_mod(poly &a, poly x){
        auto beta = a*x;
        auto q = beta*ic;
        q.cut(k-1);
        auto result = c*q;
        for (int i = k-1; i <= 2*k-2; ++i) {
            (result[i] += beta[i]) %= mod;
        }
        a = poly(vector<int>(result.v.begin()+k-1, result.v.begin()+2*k-1));
    }

    void calc_ic() {
        ic = poly(vector<int>(1, 1));
        int t = 1;
        while(t <= k){
            t = min(2*t, k+1);
            auto cc = poly(vector<int>(c.v.begin(), c.v.begin()+t));
            auto current = cc*ic;
            (current[0] += 2) %= mod;
            ic = ic*current;
        }
        ic.cut(t);
    }

    poly kitamasa(int n){
        b = poly(vector<int>(k, 0));
        auto x = poly(vector<int>(k, 0));
        b[k-1] = 1;
        x[k-2] = 1;
        while (n != 0){
            if ((n & 1) == 1){
                multiply_mod(b, x);
            }
            n /= 2;
            multiply_mod(x, x);
        }
        return b;
    }
};