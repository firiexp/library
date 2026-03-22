#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include <cmath>
#include <cstdint>
#include <vector>
using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/counting_primes.cpp"

int main() {
    Scanner sc;
    Printer pr;
    long long n;
    sc.read(n);
    pr.println(counting_primes(n));
    return 0;
}
