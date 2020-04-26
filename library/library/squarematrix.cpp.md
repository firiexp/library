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


# :warning: library/squarematrix.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/squarematrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class H, size_t SIZE>
struct SquareMatrix {
    using T = typename H::T;
    using ar = array<T, SIZE>;
    using mat = array<ar, SIZE>;
    mat A;
    SquareMatrix() = default;
    static SquareMatrix I(){
        SquareMatrix X{};
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if(i == j) X[i][j] = H::one();
                else X[i][j] = H::zero();
            }
        }
        return X;
    }

    friend ar operator*=(ar &x, const SquareMatrix &Y) {
        ar ans{};
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
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
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                H::add((*this)[i][j], B[i][j]);
            }
        }
        return (*this);
    }

    SquareMatrix &operator-= (const SquareMatrix &B){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                H::add((*this)[i][j], -B[i][j]);
            }
        }
        return (*this);
    }

    SquareMatrix &operator*=(const SquareMatrix &B) {
        SquareMatrix C{};
        for (int i = 0; i < SIZE; ++i) {
            for (int k = 0; k < SIZE; ++k) {
                for (int j = 0; j < SIZE; ++j) {
                    H::add(C[i][j],  H::mul((*this)[i][k], B[k][j]));
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }

    SquareMatrix pow(ll n) const {
        SquareMatrix a = (*this), res = I();
        while(n > 0){
            if(n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    SquareMatrix operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}
    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this) -= B;}
    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this) *= B;}
};

struct SemiRing {
    using T = double;
    static inline T mul(T x, T y){ return x * y; }
    static inline void add(T &x, T y){ x += y; }
    static inline T one(){ return 1.0; }
    static inline T zero(){ return 0.0; }
};

using ar = array<SemiRing::T, 64>;
using mat = SquareMatrix<SemiRing, 64>;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/squarematrix.cpp"
template<class H, size_t SIZE>
struct SquareMatrix {
    using T = typename H::T;
    using ar = array<T, SIZE>;
    using mat = array<ar, SIZE>;
    mat A;
    SquareMatrix() = default;
    static SquareMatrix I(){
        SquareMatrix X{};
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if(i == j) X[i][j] = H::one();
                else X[i][j] = H::zero();
            }
        }
        return X;
    }

    friend ar operator*=(ar &x, const SquareMatrix &Y) {
        ar ans{};
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
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
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                H::add((*this)[i][j], B[i][j]);
            }
        }
        return (*this);
    }

    SquareMatrix &operator-= (const SquareMatrix &B){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                H::add((*this)[i][j], -B[i][j]);
            }
        }
        return (*this);
    }

    SquareMatrix &operator*=(const SquareMatrix &B) {
        SquareMatrix C{};
        for (int i = 0; i < SIZE; ++i) {
            for (int k = 0; k < SIZE; ++k) {
                for (int j = 0; j < SIZE; ++j) {
                    H::add(C[i][j],  H::mul((*this)[i][k], B[k][j]));
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }

    SquareMatrix pow(ll n) const {
        SquareMatrix a = (*this), res = I();
        while(n > 0){
            if(n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    SquareMatrix operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}
    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this) -= B;}
    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this) *= B;}
};

struct SemiRing {
    using T = double;
    static inline T mul(T x, T y){ return x * y; }
    static inline void add(T &x, T y){ x += y; }
    static inline T one(){ return 1.0; }
    static inline T zero(){ return 0.0; }
};

using ar = array<SemiRing::T, 64>;
using mat = SquareMatrix<SemiRing, 64>;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

