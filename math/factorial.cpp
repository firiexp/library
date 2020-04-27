#include "../util/modint.cpp"

class Factorial {
    vector<mint> facts, factinv;
public:
    explicit Factorial(int n) : facts(n+1), factinv(n+1) {
        facts[0] = 1;
        for (int i = 1; i < n+1; ++i) facts[i] = facts[i-1] * mint(i);
        factinv[n] = facts[n].inv();
        for (int i = n-1; i >= 0; --i) factinv[i] = factinv[i+1] * mint(i+1);
    }
    mint fact(int k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint operator[](const int &k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint C(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[q] * factinv[p-q];
    }
    mint P(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[p-q];
    }
    mint H(int p, int q) const {
        if(p < 0 || q < 0) return 0;
        return q == 0 ? 1 : C(p+q-1, q);
    }
};