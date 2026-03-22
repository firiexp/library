#include "linear_sieve.cpp"

vector<int> mobius_all(int M) {
    if (M <= 0) return {};
    return LinearSieve(M - 1, false, false, true).mobius;
}
