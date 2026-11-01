#define STANDALONE

#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <vector>
using namespace std;

#include "../math/convolution/min_plus_convolution_argmin.cpp"
#include "../math/convolution/min_plus_convolution.cpp"
using ll = long long;

bool convex(const vector<ll> &a) {
    for (int i = 2; i < (int)a.size(); ++i)
        if (a[i] - a[i - 1] < a[i - 1] - a[i - 2]) return false;
    return true;
}

void check(const vector<ll> &a, const vector<ll> &b) {
    auto original_a = a, original_b = b;
    vector<ll> expected;
    if (!a.empty() && !b.empty()) expected.assign(a.size() + b.size() - 1, numeric_limits<ll>::max());
    for (int i = 0; i < (int)a.size(); ++i) for (int j = 0; j < (int)b.size(); ++j)
        expected[i + j] = min(expected[i + j], a[i] + b[j]);
    auto check_result = [&](const MinPlusArgmin<ll> &res) {
        assert(res.value == expected && res.argmin.size() == expected.size());
        for (int k = 0; k < (int)expected.size(); ++k) {
            int i = res.argmin[k], j = k - i;
            assert(0 <= i && i < (int)a.size() && 0 <= j && j < (int)b.size());
            assert(a[i] + b[j] == expected[k]);
        }
    };
    if (convex(b)) {
        assert(min_plus_convolution_arbitrary_convex(a, b) == expected);
        check_result(min_plus_argmin_arbitrary_convex(a, b));
    }
    if (convex(a)) {
        assert(min_plus_convolution_convex_arbitrary(a, b) == expected);
        check_result(min_plus_argmin_convex_arbitrary(a, b));
    }
    if (convex(a) && convex(b)) {
        assert(min_plus_convolution_convex_convex(a, b) == expected);
        check_result(min_plus_argmin_convex_convex(a, b));
    }
    assert(a == original_a && b == original_b);
}

int main() {
    vector<vector<ll>> arrays;
    for (int n = 0, count = 1; n <= 4; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            vector<ll> a(n);
            int value = mask;
            for (auto &x : a) {
                x = value % 3 - 1;
                value /= 3;
            }
            arrays.push_back(a);
        }
    }
    for (const auto &a : arrays) for (const auto &b : arrays) check(a, b);
    mt19937 rng(350);
    for (int n = 0; n <= 25; ++n) for (int m = 0; m <= 25; ++m) for (int mode = 0; mode < 3; ++mode) {
        vector<ll> a(n), b(m);
        ll value = -30, diff = -20;
        for (auto &x : a) {
            x = value;
            diff += rng() % 4;
            value += diff;
        }
        value = -20;
        diff = -10;
        for (auto &x : b) {
            x = mode == 0 ? int(rng() % 101) - 50 : mode == 1 ? value : 0;
            diff += rng() % 4;
            value += diff;
        }
        check(a, b);
        check(b, a);
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        check(a, b);
    }
    check(vector<ll>(1, -3), vector<ll>(1000, 5));
    check(vector<ll>(1000, 5), vector<ll>(1, -3));
}
