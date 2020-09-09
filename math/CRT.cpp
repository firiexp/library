#include "extgcd.cpp"

pair<ll, ll> CRT(const vector<pair<ll, ll>> &a){
    ll R = 0, M = 1;
    for (auto &&i : a) {
        ll r = (i.first+i.second)%i.second, m = i.second;
        if(m < M) swap(r, R), swap(m, M);
        if(M%m == 0){
            if(R % m != r) return {};
            continue;
        }
        ll p, q;
        ll g = extgcd(M, m, p, q); // p = inv(M') mod m'
        ll mm = m/g;
        if((r-R)%g) return {0, 0};
        ll x = (r-R)/g % mm * p % mm;
        R += x*M;
        M *= mm;
        if(R < 0) R += M;
    }
    return {R, M};
}
