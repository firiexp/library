#ifndef FIRIEXP_LIBRARY_MATH_MODULAR_DISCRETE_LOGARITHM_TABLE_CPP
#define FIRIEXP_LIBRARY_MATH_MODULAR_DISCRETE_LOGARITHM_TABLE_CPP

class DiscreteLogarithmTable {
    using Integer = long long;
    using i128 = __int128_t;
    Integer mod_, width_, inverse_step_ = 0;
    bool full_cycle_ = false;
    std::unordered_map<Integer, Integer> baby_;

    Integer multiply(Integer a, Integer b) const {
        return (Integer)((i128)a * b % mod_);
    }

public:
    DiscreteLogarithmTable(Integer x, Integer mod) : mod_(mod) {
        assert(mod >= 1);
        x %= mod;
        if (x < 0) x += mod;
        assert(std::gcd(x, mod) == 1);
        if (mod == 1) {
            width_ = 1;
            return;
        }
        width_ = (Integer)std::sqrt((long double)mod) + 1;
        baby_.reserve((size_t)width_ * 2 + 1);
        Integer cur = 1;
        for (Integer q = 0; q < width_; ++q) {
            baby_.emplace(cur, q);
            cur = multiply(cur, x);
            if (cur == 1) {
                full_cycle_ = true;
                return;
            }
        }
        Integer a = cur, b = mod;
        i128 u = 1, v = 0;
        while (b) {
            Integer q = a / b;
            Integer next = a % b;
            a = b;
            b = next;
            i128 coefficient = u - (i128)q * v;
            u = v;
            v = coefficient;
        }
        if (u < 0) u += mod;
        inverse_step_ = (Integer)u;
    }

    Integer log(Integer y) const {
        if (mod_ == 1) return 0;
        y %= mod_;
        if (y < 0) y += mod_;
        if (y == 0) return -1;
        Integer steps = full_cycle_ ? 0 : (mod_ - 1) / width_;
        for (Integer p = 0; p <= steps; ++p) {
            auto it = baby_.find(y);
            if (it != baby_.end() && it->second <= mod_ - 1 - p * width_) {
                return p * width_ + it->second;
            }
            y = multiply(y, inverse_step_);
        }
        return -1;
    }
};

#endif

/**
 * @brief modと底を固定した離散対数
 */
