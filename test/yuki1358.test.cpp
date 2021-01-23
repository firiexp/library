#define PROBLEM "https://yukicoder.me/problems/no/1358"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../math/extgcd.cpp"
#include "../util/ifloor.cpp"

void solve(){
    ll a, b, c, y;
    cin >> a >> b >> c >> y;
    if(a > c) swap(a, c);
    if(b > c) swap(b, c);
    ll ans = 0, g = gcd(a, b);
    a /= g; b /= g;
    ll p, q;
    extgcd(a, b, p, q);
    for (ll x2 = y; x2 >= 0; x2 -= c) {
        if(x2 % g) continue;
        ll x = x2/g;
        ans += max(0LL, ifloor(q*x, a)-iceil(-p*x, b)+1);
    }
    cout << ans%MOD << "\n";
}

int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}