#include "linear_sieve.cpp"

vector<int> eulerphi_all(int M) {
    if (M <= 0) return {};
    return LinearSieve(M - 1, false, true).phi;
}

/**
 * @brief オイラーのφ関数テーブル(Euler Phi Table)
 */
