#include "../math/ntt.cpp"
mint nth_term(poly p, poly q, ll n){
    if(!n) return p[0]/q[0];
    int sz = 1, h = 0;
    int k = max(p.size(), q.size());
    while(sz < 2*k-1) sz <<= 1, h++;
    p.v.resize(sz); q.v.resize(sz);
    mint x = mint(sz>>1).inv();
    vector<mint> y(sz>>1, 0);
    for (int j = sz>>2, i = h; j; j >>= 1, i--) y[j] = ntt.ies[i];
    y[0] = 1;
    for (int i = 2; i < sz>>1; i <<= 1) {
        for (int j = i+1; j < 2*i; ++j) {
            y[j] = y[j-i]*y[i];
        }
    }
    ntt.transform(p.v, 0);
    ntt.transform(q.v, 0);
    poly tmp(sz>>1);
    auto up = [&](poly &A){
        for (int i = 0; i < sz>>1; ++i) tmp[i] = A[i];
        ntt.transform(tmp.v, 1);
        mint now = x;
        for (int i = 0; i < sz>>1; ++i) tmp[i] *= now, now *= ntt.es[h];
        ntt.transform(tmp.v, 0);
        for (int i = 0; i < sz>>1; ++i) A[i|(sz>>1)] = tmp[i];
    };
    int ika = h;
    while(n){
        for (int i = 0; i < sz; ++i) p[i] *= q[i^1];
        if(n&1) for (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];
        else for (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);
        ika++;
        if(n == 1) break;
        up(p);
        for (int i = 0; i < sz>>1; ++i) q[i] = q[i<<1]*q[(i<<1)|1];
        up(q);
        n >>= 1;
    }
    for (int i = 0; i < sz>>1; ++i) tmp[i] = p[i];
    ntt.transform(tmp.v, 1);
    return mint(2).pow(ntt_mod-ika)*tmp[0];
}