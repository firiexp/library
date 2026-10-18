#define STANDALONE

#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/min_plus_convolution.cpp"

void self_check() {
    mt19937 rng(181);
    for (int n = 0; n <= 25; ++n) {
        for (int m = 0; m <= 25; ++m) {
            for (int mode = 0; mode < 3; ++mode) {
                vector<long long> a(n), b(m);
                long long value = -30, diff = -20;
                for (auto &x : a) {
                    x = value;
                    if (mode == 0) diff += rng() % 4;
                    value += mode == 2 ? 0 : diff;
                }
                for (auto &x : b) x = mode == 2 ? 0 : (int)(rng() % 101) - 50;
                auto original_a = a, original_b = b;
                vector<long long> expected;
                if (n && m) expected.assign(n + m - 1, numeric_limits<long long>::max());
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) expected[i + j] = min(expected[i + j], a[i] + b[j]);
                }
                assert(min_plus_convolution_convex_arbitrary(a, b) == expected);
                assert(a == original_a && b == original_b);
                reverse(a.begin(), a.end());
                reverse(b.begin(), b.end());
                reverse(expected.begin(), expected.end());
                assert(min_plus_convolution_convex_arbitrary(a, b) == expected);
            }
        }
    }
}

int main() {
    self_check();
}
