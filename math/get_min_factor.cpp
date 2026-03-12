#include "linear_sieve.cpp"

vector<int> get_min_factor(int n) {
    return LinearSieve(n, true).min_factor;
}

/**
 * @brief 最小素因数テーブル(Min Factor Table)
 */
