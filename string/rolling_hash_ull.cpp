#include "rolling_hash_common.cpp"

class rolling_hash_ull {
    static constexpr ull M = (1ULL << 61) - 1;
    static constexpr ull MASK30 = (1ULL << 30) - 1;
    static constexpr ull MASK31 = (1ULL << 31) - 1;

    static ull get_base(){
        ull z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1)))+0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z;
    }

    static inline ull calc_mod(ull val){
        val = (val & M) + (val >> 61);
        if(val >= M) val -= M;
        return val;
    }

    static inline ull mul128(ull x, ull y) {
        __uint128_t z = (__uint128_t)x * y;
        return (ull(z) & M) + ull(z >> 61);
    }
public:
    vector<ull> hash;

    static ull &B() {
        static ull B_ = (get_base())%(M-2)+2;
        return B_;
    }

    static vector<ull> &p() {
        static vector<ull> p_{1, B()};
        return p_;
    }

    static inline ull mul(ull x, ull y){
        ull a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e = b*c+a*d;
        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);
    }

    template<class S, enable_if_t<is_convertible_v<const S&, string_view>, int> = 0>
    rolling_hash_ull(const S& s) { build(string_view(s)); }

    template<class T>
    explicit rolling_hash_ull(const vector<T>& s) { build(s); }

    rolling_hash_ull(int n) {
        if (n >= 0) ensure_powers(n);
    }

    ull get(int l, int r) const {
        return calc_mod(hash[r] + 2 * M - mul128(hash[l], p()[r - l]));
    }

    static ull val(string_view s) { return value(s); }

    template<class T>
    static ull val(const vector<T>& s) { return value(s); }

    static ull concat(ull h1, ull h2, int len2) {
        ensure_powers(len2);
        return calc_mod(mul128(h1, p()[len2]) + h2);
    }

    int lcp(int l1, int r1, const rolling_hash_ull& other, int l2, int r2) const {
        return rolling_hash_detail::lcp(*this, l1, r1, other, l2, r2);
    }

private:
    static void ensure_powers(size_t n) {
        auto& powers = p();
        size_t first = powers.size();
        if (first > n) return;
        ull base = B();
        powers.resize(n + 1);
        for (size_t i = first; i <= n; ++i) powers[i] = calc_mod(mul(powers[i - 1], base));
    }

    template<class Sequence>
    void build(const Sequence& s) {
        ensure_powers(s.size());
        hash.resize(s.size() + 1);
        ull h = 0, base = B();
        for (size_t i = 0; i < s.size(); ++i) {
            h = calc_mod(mul(h, base) + rolling_hash_detail::symbol<M>(s[i]));
            hash[i + 1] = h;
        }
    }

    template<class Sequence>
    static ull value(const Sequence& s) {
        ull h = 0, base = B();
        for (auto x : s) h = calc_mod(mul128(h, base) + rolling_hash_detail::symbol<M>(x));
        return h;
    }
};

/**
 * @brief Rolling Hash(mod 2^61-1)
 */
