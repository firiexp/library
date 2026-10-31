#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../math/combinatorics/partition_numbers.cpp"

int main() {
    const int limit = 2048;
    vector<mint> expected(limit + 1);
    expected[0] = 1;
    for (int weight = 1; weight <= limit; ++weight) {
        for (int sum = weight; sum <= limit; ++sum) expected[sum] += expected[sum - weight];
    }
    set<int> sizes;
    for (int n = 0; n <= 400; ++n) sizes.insert(n);
    for (int power = 1; power <= limit; power *= 2) {
        for (int n = power - 1; n <= min(limit, power + 1); ++n) sizes.insert(n);
    }
    for (int k = 1; k * (3 * k - 1) / 2 <= limit; ++k) {
        for (int sign : {-1, 1}) {
            int degree = k * (3 * k + sign) / 2;
            for (int n = degree - 1; n <= min(limit, degree + 1); ++n) sizes.insert(n);
        }
    }
    for (int n : sizes) {
        auto actual = partition_numbers(n);
        assert(actual == vector<mint>(expected.begin(), expected.begin() + n + 1));
    }
    assert(partition_numbers(5) == vector<mint>({1, 1, 2, 3, 5, 7}));
}
