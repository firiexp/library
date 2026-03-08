template<class G>
class TwoStackDeque {
    using T = typename G::T;
    vector<T> l, r, lsum, rsum;
    void rebuild_left_sum() {
        lsum.assign(1, G::e());
        for (int i = 0; i < (int)l.size(); ++i) {
            lsum.push_back(G::f(l[i], lsum.back()));
        }
    }

    void rebuild_right_sum() {
        rsum.assign(1, G::e());
        for (int i = 0; i < (int)r.size(); ++i) {
            rsum.push_back(G::f(rsum.back(), r[i]));
        }
    }

    void rebalance_from_right() {
        int lsize = ((int)r.size() + 1) / 2;
        int rsize = (int)r.size() - lsize;
        l.resize(lsize);
        for (int i = 0; i < lsize; ++i) l[i] = r[lsize - i - 1];
        for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize];
        r.resize(rsize);
        rebuild_left_sum();
        rebuild_right_sum();
    }

    void rebalance_from_left() {
        int rsize = ((int)l.size() + 1) / 2;
        int lsize = (int)l.size() - rsize;
        r.resize(rsize);
        for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1];
        for (int i = 0; i < lsize; ++i) l[i] = l[i + rsize];
        l.resize(lsize);
        rebuild_left_sum();
        rebuild_right_sum();
    }
public:
    TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}

    void push_front(const T& v){
        lsum.push_back(G::f(v, lsum.back()));
        l.push_back(v);
    }

    void push_back(const T& v){
        rsum.push_back(G::f(rsum.back(), v));
        r.push_back(v);
    }

    void pop_front(){
        if(l.empty()){
            if(r.empty()) return;
            rebalance_from_right();
        }
        l.pop_back(); lsum.pop_back();
    }

    void pop_back(){
        if(r.empty()){
            if(l.empty()) return;
            rebalance_from_left();
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

/**
 * @brief SWAG Deque
 */
