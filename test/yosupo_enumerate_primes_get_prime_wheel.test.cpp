#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <algorithm>
#include <cmath>
#include <vector>
#include <array>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/prime/get_prime_wheel.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, a, b;
    sc.read(n, a, b);

    Prime prime(n, a, b);

    pr.print(prime.count);
    pr.print(' ');
    pr.println((prime.count <= b ? 0 : (prime.count - b + a - 1) / a));

    pr.println(prime.picked);
}
