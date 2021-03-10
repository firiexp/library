vector<ll> sqrt_fraction(ll n){
    set<tuple<ll, ll, ll>> s;
    vector<ll> ret;
    ll sq = Isqrt(n);
    if(sq*sq == n) return {sq};
    tuple<ll, ll, ll> a = {sq, -sq, 1};

    while(!s.count(a)){
        s.insert(a);
        ret.emplace_back(get<0>(a));
        auto [p, q, r] = a;
        ll c = floor(r/(q+sqrt(n)));
        ll x = (n-q*q)/r;
        a = {c, -q-c*x, x};
    }
    return ret;
}

pair<ll, ll> pell_equation(ll d){ // solve x^2 - dy^2 = 1
    auto li = sqrt_fraction(d);
    if(li.size() <= 1) return {0, 0};
    li.pop_back();
    ll p = li.back(), q = 1;
    for (int i = (int)li.size()-2; i >= 0; --i) {
        swap(p, q);
        p += q*li[i];
    }
    if(p*p - d*q*q == -1) return {p*p+d*q*q, 2*p*q}; // p' + q'√d  = (p + q√d)^2
    return {p, q};
}