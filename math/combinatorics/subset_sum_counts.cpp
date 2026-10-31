#ifndef FIRIEXP_LIBRARY_MATH_SUBSET_SUM_COUNTS_CPP
#define FIRIEXP_LIBRARY_MATH_SUBSET_SUM_COUNTS_CPP

#include "../../fps/ntt.cpp"

vector<mint> subset_sum_counts(const vector<int>& weights, int max_sum) {
    assert(0 <= max_sum && max_sum < ntt_mod);
    vector<int> count(max_sum + 1);
    mint zero_factor = 1;
    for (int weight : weights) {
        assert(weight >= 0);
        if (weight == 0) zero_factor += zero_factor;
        else if (weight <= max_sum) ++count[weight];
    }
    poly derivative(max_sum);
    for (int weight = 1; weight <= max_sum; ++weight) {
        if (count[weight] == 0) continue;
        mint coefficient = mint(weight) * mint(count[weight]);
        for (int sum = weight; sum <= max_sum; sum += weight) {
            derivative[sum - 1] += coefficient;
            coefficient = -coefficient;
        }
    }
    auto result = derivative.integral().exp(max_sum + 1).v;
    for (auto& x : result) x *= zero_factor;
    return result;
}

#endif

/**
 * @brief 和ごとの部分集合数
 */
