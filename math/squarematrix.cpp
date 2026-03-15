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
        SquareMatrix a = (*this), res = I(dim);

        while(n > 0){
            if(n & 1) res.mul_assign(a, dim);
            a.mul_assign(a, dim);
            n >>= 1;
        }
        return res;
    }
    SquareMatrix operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}
    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this) -= B;}
    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this) *= B;}
};

/**
 * @brief 固定長正方行列(Square Matrix)
 */
