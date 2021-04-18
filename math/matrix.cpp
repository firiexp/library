template<class H>
struct matrix {
    using T = typename H::T;
    vector<vector<T>> A;
    matrix() = default;
    matrix(size_t n, size_t m) : A(n, vector<T>(m)) {}
    explicit matrix(size_t n) : A(n, vector<T> (n)) {};
    size_t height() const { return (A.size()); }
    size_t width() const { return (A[0].size()); }

    const vector<T> &operator [] (int k) const { return A[k]; }
    vector<T> &operator[] (int k) { return A[k]; }

    static matrix I(size_t n){
        matrix mat(n);
        for (int i = 0; i < n; ++i) mat[i][i] = 1;
        return mat;
    }

    matrix &operator+= (const matrix &B){
        size_t h = height(), w = width();
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                add((*this)[i][j], B[i][j]);
            }
        }
    }

    matrix &operator-= (const matrix &B){
        size_t h = height(), w = width();
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                add((*this)[i][j], -B[i][j]);
            }
        }
    }

    matrix &operator*=(const matrix &B) {
        size_t n = height(), m = B.width(), p = width();
        matrix C(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < p; ++k) {
                    add(C[i][j], mul((*this)[i][k],B[k][j]));
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }

    matrix pow(ll n) const {
        matrix a = (*this), res = I(height());
        while(n > 0){
            if(n & 1) mul(res, a);
            mul(a, a);
            n >>= 1;
        }
        return res;
    }
    matrix operator+(const matrix &B) const {return matrix(*this) += B;}
    matrix operator-(const matrix &B) const {return matrix(*this) -= B;}
    matrix operator*(const matrix &B) const {return matrix(*this) *= B;}

    mint detarminant(){
        mint res = 1;
        int rank = 0;
        for (int c = 0; c < width(); ++c) {
            int k = -1;
            for (int i = rank; i < height(); ++i) {
                if(A[i][c] != H::zero()){
                    k = i;
                    break;
                }
            }
            if(!~k) continue;
            swap(A[k], A[rank]);
            res *= A[rank][c];
            T x = T(1)/A[rank][c];
            for (int j = 0; j < width(); ++j) A[rank][j] *= x;
            for (int i = 0; i < height(); ++i) {
                if(i != rank && A[i][c] != H::zero()){
                    T coeff = A[i][c];
                    for (int j = 0; j < width(); ++j) {
                        A[i][j] -= A[rank][j]*coeff;
                    }
                }
            }
            rank++;
        }
        for (int i = 0; i < min(width(), height()); ++i) {
            res *= A[i][i];
        }
        return res;
    }
};

struct SemiRing {
    using T = mint;
    static inline T mul(T x, T y){ return x * y; }
    static inline void add(T &x, T y){ x += y; }
    static inline T one(){ return 1; }
    static inline T zero(){ return 0; }
};