#include <chrono>
constexpr u64 M = (1UL << 61) - 1;
constexpr u64 POSITIVISER = M * 3;
constexpr u64 MASK30 = (1UL << 30) - 1;
constexpr u64 MASK31 = (1UL << 31) - 1;

class rolling_hash_u64 {
    static u64 get_base(){
        u64 z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1)))+0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z;
    }

    static u64 &B() {
        static u64 B_ = (get_base())%(M-2)+2;
        return B_;
    }
    static vector<u64> &p() {
        static vector<u64> p_{1, B()};
        return p_;
    }

    static inline u64 mul(u64 x, u64 y){
        u64 a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e = b*c+a*d;
        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);
    }

    static inline u64 calc_mod(u64 val){
        val = (val & M) + (val >> 61);
        if(val > M) val -= M;
        return val;
    }
public:
    vector<u64> hash;
    explicit rolling_hash_u64(const string &s) {
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

    u64 get(int l, int r){
        return calc_mod(hash[r] + POSITIVISER - mul(hash[l], p()[r-l]));
    }
};

