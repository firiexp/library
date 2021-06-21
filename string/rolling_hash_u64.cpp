#include <chrono>
constexpr ull M = (1UL << 61) - 1;
constexpr ull POSITIVISER = M * 3;
constexpr ull MASK30 = (1UL << 30) - 1;
constexpr ull MASK31 = (1UL << 31) - 1;

class rolling_hash_ull {
    static ull get_base(){
        ull z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1)))+0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z;
    }

    static inline ull calc_mod(ull val){
        val = (val & M) + (val >> 61);
        if(val > M) val -= M;
        return val;
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

    rolling_hash_ull(const string &s) {
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = calc_mod(mul(p()[i-1], p()[1]));
            }
        }
        hash.resize(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            hash[i+1] = calc_mod(mul(hash[i],B()) + s[i]);
        }
    };

    rolling_hash_ull(const int& n){
        int l = p().size();
        p().resize(n+1);
        for (int i = l; i < p().size(); ++i) {
            p()[i] = calc_mod(mul(p()[i-1], p()[1]));
        }
    }

    ull get(int l, int r){
        return calc_mod(hash[r] + POSITIVISER - mul(hash[l], p()[r-l]));
    }

    static ull val(string &s){
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = calc_mod(mul(p()[i-1], p()[1]));
            }
        }
        ull ret = 0;
        for (int i = 0; i < s.size(); ++i) {
            ret = calc_mod(mul(ret, B()) + s[i]);
        }
        return ret;
    }
};