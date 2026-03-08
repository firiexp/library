#include <cmath>
#include <cstdint>
#include <vector>
using namespace std;

namespace counting_primes_internal {

using ll = long long;

constexpr int MAX = 5000000;
constexpr int PHI_N = 100000;
constexpr int PHI_S = 100;

bool initialized = false;
vector<int> primes;
vector<int> prime_pi;
int phi_dp[PHI_S + 1][PHI_N + 1];

ll isqrt(ll x) {
    ll r = sqrtl((long double)x);
    while ((r + 1) * (r + 1) <= x) ++r;
    while (r * r > x) --r;
    return r;
}

ll icbrt(ll x) {
    ll r = powl((long double)x, 1.0L / 3.0L);
    while ((__int128)(r + 1) * (r + 1) * (r + 1) <= x) ++r;
    while ((__int128)r * r * r > x) --r;
    return r;
}

ll iroot4(ll x) {
    return isqrt(isqrt(x));
}

void init() {
    if (initialized) return;
    initialized = true;

    vector<int> min_factor(MAX + 1);
    prime_pi.assign(MAX + 1, 0);
    for (int i = 2; i <= MAX; ++i) {
        if (min_factor[i] == 0) {
            min_factor[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            ll v = 1LL * i * p;
            if (v > MAX || p > min_factor[i]) break;
            min_factor[v] = p;
        }
        prime_pi[i] = prime_pi[i - 1] + (min_factor[i] == i);
    }

    for (int n = 0; n <= PHI_N; ++n) phi_dp[0][n] = n;
    for (int s = 1; s <= PHI_S; ++s) {
        int p = primes[s - 1];
        for (int n = 0; n <= PHI_N; ++n) {
            phi_dp[s][n] = phi_dp[s - 1][n] - phi_dp[s - 1][n / p];
        }
    }
}

ll phi(ll x, int s) {
    if (s == 0) return x;
    if (s <= PHI_S && x <= PHI_N) return phi_dp[s][x];
    if (s == 1) return x - x / 2;
    return phi(x, s - 1) - phi(x / primes[s - 1], s - 1);
}

ll lehmer_pi(ll x) {
    if (x <= MAX) return prime_pi[x];

    ll a = lehmer_pi(iroot4(x));
    ll b = lehmer_pi(isqrt(x));
    ll c = lehmer_pi(icbrt(x));

    ll sum = phi(x, (int)a) + (b + a - 2) * (b - a + 1) / 2;
    for (ll i = a + 1; i <= b; ++i) {
        ll w = x / primes[i - 1];
        sum -= lehmer_pi(w);
        if (i <= c) {
            ll lim = lehmer_pi(isqrt(w));
            for (ll j = i; j <= lim; ++j) {
                sum -= lehmer_pi(w / primes[j - 1]) - (j - 1);
            }
        }
    }
    return sum;
}

}  // namespace counting_primes_internal

long long counting_primes(long long n) {
    counting_primes_internal::init();
    return counting_primes_internal::lehmer_pi(n);
}
