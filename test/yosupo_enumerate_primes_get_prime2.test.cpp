#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <cstdint>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/get_prime2.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, a, b;
    sc.read(n, a, b);
    auto prime = get_prime(n);
    int m = prime.size();
    pr.writeln(m, (m + a - 1 - b) / a);
    bool first = true;
    for (int i = b; i < m; i += a) {
        if (!first) pr.write(' ');
        first = false;
        pr.write(prime[i].val);
    }
    pr.writeln();
    return 0;
}
