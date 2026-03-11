#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED
#include "../util/modint.cpp"
#endif

template <class Mint = mint>
class Factorial {
    inline static vector<Mint> facts, factinv, invs;

    static void init() {
        if (!facts.empty()) return;
        facts.push_back(Mint(1));
        factinv.push_back(Mint(1));
        invs.push_back(Mint(0));
        invs.push_back(Mint(1));
    }

    static void expand(int n) {
        init();
        if (n < (int)facts.size()) return;
        int old = facts.size();
        int mod = Mint::get_mod();
        facts.resize(n + 1);
        factinv.resize(n + 1);
        invs.resize(n + 1);
        for (int i = max(2, old); i <= n; ++i) {
            invs[i] = -Mint(mod / i) * invs[mod % i];
        }
        for (int i = old; i <= n; ++i) {
            facts[i] = facts[i - 1] * Mint(i);
            factinv[i] = factinv[i - 1] * invs[i];
        }
    }
public:
    explicit Factorial(int n = 0) {
        expand(n);
    }
    void ensure(int n) const {
        if (n >= 0) expand(n);
    }
    int max_n() const {
        init();
        return (int)facts.size() - 1;
    }
    Mint fact(int k) const {
        if (k < 0) return inv_fact(-k);
        expand(k);
        return facts[k];
    }
    Mint inv_fact(int k) const {
        if (k < 0) return 0;
        expand(k);
        return factinv[k];
    }
    Mint inv(int k) const {
        if (k < 0) return 0;
        expand(k);
        return invs[k];
    }
    Mint operator[](int k) const {
        return k >= 0 ? fact(k) : inv_fact(-k);
    }
    Mint C(int n, int k) const {
        if (n < 0 || k < 0 || n < k) return 0;
        expand(n);
        return facts[n] * factinv[k] * factinv[n - k];
    }
    Mint P(int n, int k) const {
        if (n < 0 || k < 0 || n < k) return 0;
        expand(n);
        return facts[n] * factinv[n - k];
    }
    Mint H(int n, int k) const {
        if (n < 0 || k < 0) return 0;
        if (k == 0) return 1;
        if (n == 0) return 0;
        return C(n + k - 1, k);
    }
};

/**
 * @brief 階乗・二項係数(Factorial)
 */
