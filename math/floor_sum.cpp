ll floor_sum(ll n, ll m, ll a, ll b){
    ll ans = 0;
    if(a >= m) {
        ans += (n-1)*n/2*(a/m);
        a %= m;
    }
    if (b >= m){
        ans += n*(b/m);
        b %= m;
    }
    ll y = (a*n+b)/m, x = (y*m - b);
    if(!y) return ans;
    ans += (n-(x+a-1)/a)*y;
    ans += floor_sum(y, a, m, (a - x%a)%a);
    return ans;
}