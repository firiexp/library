#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C"

#include <cstdint>
#include <vector>
using namespace std;
using uint = unsigned;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/get_prime2.cpp"

bool is_prime_number(uint x, const vector<ExactDiv<uint>> &primes) {
    if (x < 2) return false;
    for (auto &&p : primes) {
        if (1ULL * p.val * p.val > x) break;
        if (p.divide(x)) return false;
    }
    return true;
}

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    auto primes = get_prime_exact_div(100000);
    int ans = 0;
    while (n--) {
        uint x;
        sc.read(x);
        ans += is_prime_number(x, primes);
    }
    pr.println(ans);
    return 0;
}
