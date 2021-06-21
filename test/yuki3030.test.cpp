#define PROBLEM "https://yukicoder.me/problems/no/3030"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <map>
#include <queue>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T>
constexpr T INF = ::numeric_limits<T>::max() / 2;
#include "../math/miller_rabin.cpp"

int main() {
    ll n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ull k; scanf("%lld", &k);
        printf("%lld %d\n", k, miller_rabin(k));
    }
    return 0;
}