#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C"

#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/get_prime.cpp"

bool is_prime_number(int x, const vector<int> &primes) {
    if (x < 2) return false;
    for (int p : primes) {
        if (1LL * p * p > x) break;
        if (x % p == 0) return false;
    }
    return true;
}

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    auto primes = get_prime(100000);
    int ans = 0;
    while (n--) {
        int x;
        sc.read(x);
        ans += is_prime_number(x, primes);
    }
    pr.println(ans);
    return 0;
}
