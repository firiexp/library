#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../math/linear_algebra/inverse_matrix_mod2.cpp"
#include "../math/linear_algebra/inverse_matrix_mod2.cpp"

bool invertible_by_enumeration(const vector<DynamicBitset> &a) {
    int n = a.size();
    for (int mask = 1; mask < (1 << n); ++mask) {
        bool nonzero = false;
        for (const auto &row : a) {
            bool value = false;
            for (int j = 0; j < n; ++j) value ^= row.test(j) && (mask >> j & 1);
            nonzero |= value;
        }
        if (!nonzero) return false;
    }
    return true;
}

void check_product(const vector<DynamicBitset> &a, const vector<DynamicBitset> &b) {
    int n = a.size();
    assert((int)b.size() == n);
    for (const auto &row : b) assert(row.size() == n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        bool value = false;
        for (int k = 0; k < n; ++k) value ^= a[i].test(k) && b[k].test(j);
        assert(value == (i == j));
    }
}

vector<int> apply_scalar(const vector<DynamicBitset> &a, const vector<int> &x) {
    int n = a.size();
    vector<int> result(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
        result[i] ^= a[i].test(j) && x[j];
    return result;
}

int main() {
    for (int n = 0; n <= 4; ++n) {
        for (int mask = 0; mask < (1 << (n * n)); ++mask) {
            vector<DynamicBitset> a(n, DynamicBitset(n));
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
                a[i].assign(j, mask >> (i * n + j) & 1);
            auto original = a;
            auto inverse = inverse_matrix_mod2(a);
            assert((n == 0 || !inverse.empty()) == invertible_by_enumeration(a));
            for (int i = 0; i < n; ++i) assert((a[i] ^ original[i]).none());
            if (n == 0 || !inverse.empty()) {
                check_product(a, inverse);
                check_product(inverse, a);
            }
        }
    }
    mt19937 rng(401);
    for (int n : {1, 2, 7, 63, 64, 65, 127, 128, 129, 511, 512, 513}) {
        for (int trial = 0; trial < 3; ++trial) {
            vector<DynamicBitset> a(n, DynamicBitset(n));
            for (int i = 0; i < n; ++i) a[i].set(n - 1 - i);
            if (n > 1) for (int step = 0; step < 20 * n; ++step) {
                int i = rng() % n, j = rng() % (n - 1);
                if (j >= i) ++j;
                a[i] ^= a[j];
                if (step % 3 == 0) swap(a[i], a[j]);
            }
            auto original = a;
            auto inverse = inverse_matrix_mod2(std::move(a));
            assert((int)inverse.size() == n);
            if (n <= 129) {
                check_product(original, inverse);
                check_product(inverse, original);
            } else {
                for (int sample = 0; sample < 10; ++sample) {
                    vector<int> x(n);
                    for (auto &value : x) value = rng() % 2;
                    assert(apply_scalar(original, apply_scalar(inverse, x)) == x);
                    assert(apply_scalar(inverse, apply_scalar(original, x)) == x);
                }
            }
            if (n > 1) original.back() = original.front();
            else original[0].reset(0);
            assert(inverse_matrix_mod2(original).empty());
        }
    }
}
