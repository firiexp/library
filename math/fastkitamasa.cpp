class Fast_Kitamasa {
    poly c, ic;
    int k;

public:
    explicit Fast_Kitamasa(const vector<mint> &coefficients)
        : c(coefficients), k((int)coefficients.size() - 1) {
        assert(k >= 1 && c[k] != mint(0));
        calc_ic();
    }

    explicit Fast_Kitamasa(const vector<int> &coefficients, int mod = mint::get_mod())
        : Fast_Kitamasa(vector<mint>(coefficients.begin(), coefficients.end())) {
        assert(mod == (int)mint::get_mod());
        (void)mod;
    }

    void calc_ic() {
        if (k == 1) {
            ic = poly();
            return;
        }
        poly reversed(vector<mint>(c.v.rbegin(), c.v.rend()));
        reversed.v.resize(k - 1);
        ic = reversed.inv();
    }

    void multiply_mod(poly &a, const poly &x) const {
        assert(a.size() <= k && x.size() <= k);
        poly product = a * x;
        product.v.resize(2 * k - 1);
        if (k == 1) {
            a = product;
            return;
        }
        poly high(vector<mint>(product.v.rbegin(), product.v.rbegin() + k - 1));
        poly quotient = high * ic;
        quotient.v.resize(k - 1);
        reverse(quotient.v.begin(), quotient.v.end());
        poly removed = c * quotient;
        a = poly(k);
        for (int i = 0; i < k; ++i) a[i] = product[i] - removed[i];
    }

    poly kitamasa(long long n) const {
        assert(n >= 0);
        poly result(k), x(k);
        result[0] = 1;
        if (k == 1) x[0] = -c[0] / c[1];
        else x[1] = 1;
        while (n != 0) {
            if (n & 1) multiply_mod(result, x);
            n >>= 1;
            if (n != 0) multiply_mod(x, x);
        }
        return result;
    }
};

/**
 * @brief 多項式剰余の冪計算(高速Kitamasa法)
 */
