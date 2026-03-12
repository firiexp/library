#include "linear_sieve.cpp"

vector<int> get_prime(int n) {
    return LinearSieve(n).primes;
}
