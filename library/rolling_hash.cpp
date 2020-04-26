class xor_shift {
    uint32_t x, y, z, w;
public:
    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1))),
    y(1068246329), z(321908594), w(1234567890) {};

    uint32_t urand(){
        uint32_t t;
        t = x ^ (x << 11);
        x = y; y = z; z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    };

    int rand(int n){
        if(n < 0) return -rand(-n);
        uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);
        uint32_t e = urand();
        while(e >= t) e = urand();
        return static_cast<int>(e%(n+1));
    }

    int rand(int a, int b){
        if(a > b) swap(a, b);
        return a+rand(b-a);
    }
};


xor_shift rd;

template<int M>
class rolling_hash {

    static ll &B() {
        static ll B_ = rd.rand(2, M-1);
        return B_;
    }
    static vector<ll> &p() {
        static vector<ll> p_{1, B()};
        return p_;
    }
public:
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
