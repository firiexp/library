#include "../extgcd.cpp"

pair<ll, ll> CRT(const vector<pair<ll, ll>> &a){
    ll R = 0, M = 1;
    for (auto &&i : a) {
        ll m = i.second;
        assert(m > 0);
        ll r = i.first % m;
        if(r < 0) r += m;
        if(m < M) swap(r, R), swap(m, M);
        if(M%m == 0){
            if(R % m != r) return {};
            continue;
        }
        ll p, q;
        ll g = extgcd(M, m, p, q);
        ll mm = m/g;
        if((r-R)%g) return {0, 0};
        ll x = (__int128(r) - R) / g * p % mm;
        if(x < 0) x += mm;
        __int128 modulus = __int128(M) * mm;
        assert(modulus <= numeric_limits<ll>::max());
        R = __int128(R) + __int128(x) * M;
        M = modulus;
    }
    return {R, M};
}

/**
 * @brief 中国剰余定理(Chinese Remainder Theorem)
 */
