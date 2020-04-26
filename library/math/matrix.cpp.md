---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: math/matrix.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct matrix {
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
                (*this)[i][j] += B[i][j];
            }
        }
    }

    matrix &operator-= (const matrix &B){
        size_t h = height(), w = width();
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                (*this)[i][j] -= B[i][j];
            }
        }
    }

    matrix &operator*=(const matrix &B)
    {
        size_t n = height(), m = B.width(), p = width();
        matrix C (n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < p; ++k) {
                    C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }

    template <class U>
    matrix &operator%= (const U &m){
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) {
                (*this)[i][j] %= m;
            }
        }
    }

    matrix pow(ll n) const {
        matrix a = (*this), res = I(height());
        while(n > 0){
            if(n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    matrix operator+(const matrix &A) const {return matrix(*this) += A;}
    matrix operator-(const matrix &A) const {return matrix(*this) -= A;}
    matrix operator*(const matrix &A) const {return matrix(*this) *= A;}
    template <class U>
    matrix operator%(const U &m) const {return matrix(*this) %= m;}

};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/matrix.cpp"
template<class T>
struct matrix {
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
                (*this)[i][j] += B[i][j];
            }
        }
    }

    matrix &operator-= (const matrix &B){
        size_t h = height(), w = width();
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                (*this)[i][j] -= B[i][j];
            }
        }
    }

    matrix &operator*=(const matrix &B)
    {
        size_t n = height(), m = B.width(), p = width();
        matrix C (n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < p; ++k) {
                    C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }

    template <class U>
    matrix &operator%= (const U &m){
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) {
                (*this)[i][j] %= m;
            }
        }
    }

    matrix pow(ll n) const {
        matrix a = (*this), res = I(height());
        while(n > 0){
            if(n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    matrix operator+(const matrix &A) const {return matrix(*this) += A;}
    matrix operator-(const matrix &A) const {return matrix(*this) -= A;}
    matrix operator*(const matrix &A) const {return matrix(*this) *= A;}
    template <class U>
    matrix operator%(const U &m) const {return matrix(*this) %= m;}

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

