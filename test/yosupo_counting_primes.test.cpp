#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../util/fastio.cpp"
#include "../math/counting_primes.cpp"

int main() {
    Scanner sc;
    Printer pr;
    long long n;
    sc.read(n);
    pr.writeln(counting_primes(n));
    return 0;
}
