template<class G>
class SWAG {
    using T = typename G::T;
    vector<T> in, out, insum, outsum;
public:
    SWAG() : in(0), out(0), insum(1, G::e()), outsum(1, G::e()) {}

    void push(const T& v){
        insum.push_back(G::f(insum.back(), v));
        in.push_back(v);
    }

    void pop(){
        if(out.empty()){
            do {
                out.emplace_back(in.back());
                outsum.emplace_back(G::f(in.back(), outsum.back()));
                in.pop_back(); insum.pop_back();
            }while(!in.empty());
        }
        out.pop_back(); outsum.pop_back();
    }

    T fold(){
        return G::f(outsum.back(), insum.back());
    }
};
/*
struct Monoid {
    using T = int;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};
*/