#ifndef FIRIEXP_LIBRARY_MATH_MODULAR_DISCRETE_LOGARITHM_TABLE_CPP
#define FIRIEXP_LIBRARY_MATH_MODULAR_DISCRETE_LOGARITHM_TABLE_CPP

class DiscreteLogarithmTable {
    using i128 = __int128_t;
    ll mod_, width, inverse_step = 0;
    bool full_cycle = false;
    std::unordered_map<ll, ll> baby;

    ll multiply(ll a, ll b) const {
        return (ll)((i128)a * b % mod_);
    }

public:
    DiscreteLogarithmTable(ll x, ll mod) : mod_(mod) {
        assert(mod >= 1);
        x %= mod;
        if (x < 0) x += mod;
        assert(std::gcd(x, mod) == 1);
        if (mod == 1) {
            width = 1;
            return;
        }
        width = (ll)std::sqrt((long double)mod) + 1;
        baby.reserve((size_t)width * 2 + 1);
        ll cur = 1;
        for (ll q = 0; q < width; ++q) {
            baby.emplace(cur, q);
            cur = multiply(cur, x);
            if (cur == 1) {
                full_cycle = true;
                return;
            }
        }
        ll a = cur, b = mod;
        i128 u = 1, v = 0;
        while (b) {
            ll q = a / b;
            ll next = a % b;
            a = b;
            b = next;
            i128 coefficient = u - (i128)q * v;
            u = v;
            v = coefficient;
        }
        if (u < 0) u += mod;
        inverse_step = (ll)u;
    }

    ll log(ll y) const {
        if (mod_ == 1) return 0;
        y %= mod_;
        if (y < 0) y += mod_;
        if (y == 0) return -1;
        ll steps = full_cycle ? 0 : (mod_ - 1) / width;
        for (ll p = 0; p <= steps; ++p) {
            auto it = baby.find(y);
            if (it != baby.end() && it->second <= mod_ - 1 - p * width) {
                return p * width + it->second;
            }
            y = multiply(y, inverse_step);
        }
        return -1;
    }
};

#endif

/**
 * @brief modと底を固定した離散対数
 */
