#ifndef FIRIEXP_LIBRARY_MATH_GET_PRIME_CPP
#define FIRIEXP_LIBRARY_MATH_GET_PRIME_CPP

#include "get_prime_wheel.cpp"

vector<int> get_prime(int n) {
    return Prime(n).primes;
}

#endif
