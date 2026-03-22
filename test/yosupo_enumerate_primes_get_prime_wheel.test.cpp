#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/get_prime_wheel.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, a, b;
    sc.read(n, a, b);
    Prime prime(n);
    int m = prime.primes.size();
    pr.println(m, (m + a - 1 - b) / a);
    bool first = true;
    for (int i = b; i < m; i += a) {
        if (!first) pr.print(' ');
        first = false;
        pr.print(prime.primes[i]);
    }
    pr.println();
    return 0;
}
