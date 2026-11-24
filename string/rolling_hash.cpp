#include "../util/xorshift.cpp"
#include "rolling_hash_common.cpp"

namespace rolling_hash_detail {
inline xor_shift rd;
}

template<int M>
struct rolling_hash {
    static ll& B() {
        static ll base = rolling_hash_detail::rd.rand(2, M - 1);
        return base;
    }

    static vector<ll>& p() {
        static vector<ll> powers{1, B()};
        return powers;
    }

    vector<ll> hash;

    explicit rolling_hash(string_view s) { build(s); }

    template<class T>
    explicit rolling_hash(const vector<T>& s) { build(s); }

    ll get(int l, int r) const {
        ll res = hash[r] + M - hash[l] * p()[r - l] % M;
        return res >= M ? res - M : res;
    }

    static ll val(string_view s) { return value(s); }

    template<class T>
    static ll val(const vector<T>& s) { return value(s); }

    static ll concat(ll h1, ll h2, int len2) {
        ensure_powers(len2);
        return (h1 * p()[len2] + h2) % M;
    }

    int lcp(int l1, int r1, const rolling_hash& other, int l2, int r2) const {
        return rolling_hash_detail::lcp(*this, l1, r1, other, l2, r2);
    }

private:
    static void ensure_powers(size_t n) {
        auto& powers = p();
        size_t first = powers.size();
        if (first > n) return;
        ll base = B();
        powers.resize(n + 1);
        for (size_t i = first; i <= n; ++i) powers[i] = powers[i - 1] * base % M;
    }

    template<class Sequence>
    void build(const Sequence& s) {
        ensure_powers(s.size());
        hash.resize(s.size() + 1);
        uint64_t h = 0, base = B();
        for (size_t i = 0; i < s.size(); ++i) {
            h = (h * base + rolling_hash_detail::symbol<M>(s[i])) % M;
            hash[i + 1] = h;
        }
    }

    template<class Sequence>
    static ll value(const Sequence& s) {
        uint64_t h = 0, base = B();
        for (auto x : s) h = (h * base + rolling_hash_detail::symbol<M>(x)) % M;
        return h;
    }
};

/**
 * @brief Rolling Hash
 */
