template<class H, size_t SIZE>
struct SquareMatrix {
    using T = typename H::T;
    using ar = array<T, SIZE>;
    using mat = array<ar, SIZE>;
    mat A;
    SquareMatrix() {
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                A[i][j] = H::zero();
            }
        }
    }
    static SquareMatrix I(size_t n = SIZE){
        SquareMatrix X;
        for (size_t i = 0; i < n; ++i) {
            X[i][i] = H::one();
        }
        return X;
    }

    friend ar &operator*=(ar &x, const SquareMatrix &Y) {
        ar ans;
        fill(begin(ans), end(ans), H::zero());
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                H::add(ans[j], H::mul(x[i], Y[i][j]));
            }
        }
        x.swap(ans);
        return x;
    }
    friend ar operator*(ar x, const SquareMatrix &Y) { return x *= Y; }

    inline const ar &operator[](int k) const{ return (A.at(k)); }
    inline ar &operator[](int k) { return (A.at(k)); }
    SquareMatrix &operator+= (const SquareMatrix &B){
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                H::add((*this)[i][j], B[i][j]);
            }
        }
        return (*this);
    }

    SquareMatrix &operator-= (const SquareMatrix &B){
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                H::add((*this)[i][j], -B[i][j]);
            }
        }
        return (*this);
    }

    SquareMatrix &mul_assign(const SquareMatrix &B, size_t n = SIZE) {
        SquareMatrix C{};
        for (size_t i = 0; i < n; ++i) {
            for (size_t k = 0; k < n; ++k) {
                for (size_t j = 0; j < n; ++j) {
                    H::add(C[i][j],  H::mul((*this)[i][k], B[k][j]));
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }
    SquareMatrix &operator*=(const SquareMatrix &B) { return mul_assign(B); }

    SquareMatrix pow(ll n, size_t dim = SIZE) const {
        if (n == 0) return I(dim);
        SquareMatrix a = *this, res;
        bool started = false;
        while (n > 0) {
            if (n & 1) {
                if (started) res.mul_assign(a, dim);
                else {
                    for (size_t i = 0; i < dim; ++i) {
                        for (size_t j = 0; j < dim; ++j) res[i][j] = a[i][j];
                    }
                    started = true;
                }
            }
            n >>= 1;
            if(n) a.mul_assign(a, dim);
        }
        return res;
    }
    pair<SquareMatrix, SquareMatrix> pow_sum(ll n, size_t dim = SIZE) const {
        assert(n >= 0 && dim <= SIZE);
        if (n == 0) return {I(dim), SquareMatrix()};
        SquareMatrix power, sum = I(dim);
        for (size_t i = 0; i < dim; ++i) {
            for (size_t j = 0; j < dim; ++j) power[i][j] = A[i][j];
        }
        for (int bit = 62 - __builtin_clzll(n); bit >= 0; --bit) {
            SquareMatrix next_sum = power;
            next_sum.mul_assign(sum, dim);
            sum += next_sum;
            power.mul_assign(power, dim);
            if ((n >> bit) & 1) {
                sum += power;
                power.mul_assign(*this, dim);
            }
        }
        return {move(power), move(sum)};
    }
    SquareMatrix operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}
    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this) -= B;}
    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this) *= B;}
};

/**
 * @brief 固定長正方行列(Square Matrix)
 */
