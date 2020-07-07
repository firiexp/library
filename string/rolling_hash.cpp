#include "../util/xorshift.cpp"
xor_shift rd;

template<int M>
struct rolling_hash {

    static ll &B() {
        static ll B_ = rd.rand(2, M-1);
        return B_;
    }
    static vector<ll> &p() {
        static vector<ll> p_{1, B()};
        return p_;
    }

    vector<ll> hash;
    explicit rolling_hash(const string &s) {
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = (p()[i-1]*p()[1])%M;
            }
        }
        hash.resize(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            hash[i+1] = (hash[i]*B() + s[i]) % M;
        }
    };

    ll get(int l, int r){
        ll res = hash[r]+M-hash[l]*p()[r-l]%M;
        return res >= M ? res-M : res;
    }
};
