template<class T>
struct XorBasis {
    static_assert(is_integral_v<T>, "XorBasis requires integral T");

    using U = make_unsigned_t<T>;
    static constexpr int B = numeric_limits<U>::digits;

    vector<U> basis;
    int rank = 0;

    XorBasis() : basis(B, 0) {}

    int size() const {
        return rank;
    }

    bool empty() const {
        return rank == 0;
    }

    bool add(T x) {
        U y = reduce_unsigned(static_cast<U>(x));
        if (y == 0) return false;

        int p = B - 1;
        while (((y >> p) & 1) == 0) --p;
        for (int i = 0; i < p; ++i) {
            if ((y >> i) & 1) y ^= basis[i];
        }
        basis[p] = y;
        ++rank;
        for (int i = p + 1; i < B; ++i) {
            if ((basis[i] >> p) & 1) basis[i] ^= y;
        }
        return true;
    }

    bool contains(T x) const {
        return reduce_unsigned(static_cast<U>(x)) == 0;
    }

    T get_min(T x = 0) const {
        return static_cast<T>(reduce_unsigned(static_cast<U>(x)));
    }

    T get_max(T x = 0) const {
        U y = static_cast<U>(x);
        for (int i = B - 1; i >= 0; --i) {
            if (basis[i] == 0) continue;
            U z = y ^ basis[i];
            if (z > y) y = z;
        }
        return static_cast<T>(y);
    }

    void merge(const XorBasis &other) {
        for (int i = 0; i < B; ++i) {
            if (other.basis[i] != 0) add(static_cast<T>(other.basis[i]));
        }
    }

private:
    U reduce_unsigned(U x) const {
        for (int i = B - 1; i >= 0; --i) {
            if (((x >> i) & 1) == 0 || basis[i] == 0) continue;
            x ^= basis[i];
        }
        return x;
    }
};

/**
 * @brief XOR基底(Linear Basis)
 */
