#include <optional>

template<class G>
class SWAG {
    using T = typename G::T;
    vector<T> in, outsum;
    optional<T> in_total;
public:
    SWAG() : outsum(1, G::e()), in_total(G::e()) {}

    void push(const T& v){
        in_total.emplace(G::f(*in_total, v));
        in.push_back(v);
    }

    void pop(){
        if(outsum.size() == 1){
            do {
                outsum.emplace_back(G::f(in.back(), outsum.back()));
                in.pop_back();
            }while(!in.empty());
            in_total.emplace(G::e());
        }
        outsum.pop_back();
    }

    T fold(){
        return G::f(outsum.back(), *in_total);
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
 * @brief SWAG
 */
