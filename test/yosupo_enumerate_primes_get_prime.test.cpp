#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/prime/get_prime_wheel.cpp"
#include "../math/prime/get_prime.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, a, b;
    sc.read(n, a, b);
    auto primes = get_prime(n);
    vector<int> picked;
    for (int i = b; i < (int)primes.size(); i += a) picked.push_back(primes[i]);
    pr.println(primes.size(), picked.size());
    pr.println(picked);
}
