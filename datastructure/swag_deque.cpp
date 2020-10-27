template<class G>
class TwoStackDeque {
    using T = typename G::T;
    vector<T> l, r, lsum, rsum;
public:
    TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}

    void push_front(const T& v){
        lsum.push_back(G::f(lsum.back(), v));
        l.push_back(v);
    }

    void push_back(const T& v){
        rsum.push_back(G::f(v, rsum.back()));
        r.push_back(v);
    }

    void pop_front(){
        if(l.empty()){
            if(r.empty()) r.pop_back();
            int lsize = (r.size() + 1) / 2, rsize = r.size() - lsize;
            l.resize(lsize); lsum.resize(lsize + 1);
            for (int i = 0; i < lsize; ++i) l[i] = r[lsize - i - 1], lsum[i+1] = G::f(l[i], lsum[i]);
            for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize], rsum[i+1] = G::f(rsum[i], r[i]);
            r.resize(rsize); rsum.resize(rsize + 1);
        }
        l.pop_back(); lsum.pop_back();
    }

    void pop_back(){
        if(r.empty()){
            if(l.empty()) l.pop_back();
            int rsize = (l.size() + 1) / 2, lsize = l.size() - rsize;
            r.resize(rsize); rsum.resize(rsize + 1);
            for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1], rsum[i+1] = G::f(rsum[i], r[i]);
            for (int i = 0; i < lsize; ++i) l[i] = l[i + rsize], lsum[i+1] = G::f(l[i], lsum[i]);
            l.resize(lsize); lsum.resize(lsize + 1);
        }
        r.pop_back(); rsum.pop_back();
    }

    T fold(){
        return G::f(lsum.back(), rsum.back());
    }
};
/*
struct Monoid {
    using T = int;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};
*/