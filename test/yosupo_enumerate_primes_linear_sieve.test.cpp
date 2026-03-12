#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <limits>
#include <vector>
using namespace std;

using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/linear_sieve.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, a, b;
    sc.read(n, a, b);
    LinearSieve sieve(n);
    auto &prime = sieve.primes;
    int m = prime.size();
    pr.writeln(m, (m + a - 1 - b) / a);
    bool first = true;
    for (int i = b; i < m; i += a) {
        if (!first) pr.write(' ');
        first = false;
        pr.write(prime[i]);
    }
    pr.writeln();
    return 0;
}
