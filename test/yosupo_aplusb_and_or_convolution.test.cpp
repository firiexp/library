#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/convolution/and_convolution.cpp"
#include "../math/convolution/or_convolution.cpp"

void check(const vector<ll> &a, const vector<ll> &b) {
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n *= 2;
    vector<ll> expected_and(n), expected_or(n);
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b.size(); ++j) {
            expected_and[i & j] += a[i] * b[j];
            expected_or[i | j] += a[i] * b[j];
        }
    }
    assert(and_convolution(a, b) == expected_and);
    assert(or_convolution(a, b) == expected_or);
}

void check_transforms(const vector<ll> &a) {
    int n = 1;
    while (n < (int)a.size()) n *= 2;
    vector<ll> subset(n), superset(n), padded = a;
    padded.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)a.size(); ++j) {
            if ((i & j) == j) subset[i] += a[j];
            if ((i & j) == i) superset[i] += a[j];
        }
    }
    auto actual_subset = a, actual_superset = a;
    subset_zeta_transform(actual_subset);
    superset_zeta_transform(actual_superset);
    assert(actual_subset == subset && actual_superset == superset);
    subset_mobius_transform(actual_subset);
    superset_mobius_transform(actual_superset);
    assert(actual_subset == padded && actual_superset == padded);
    actual_subset = a;
    actual_superset = a;
    subset_mobius_transform(actual_subset);
    superset_mobius_transform(actual_superset);
    subset_zeta_transform(actual_subset);
    superset_zeta_transform(actual_superset);
    assert(actual_subset == padded && actual_superset == padded);
}

int main() {
    mt19937 rng(180);
    for (int n = 0; n <= 40; ++n) {
        for (int m = 0; m <= 40; ++m) {
            vector<ll> a(n), b(m);
            check(a, b);
            for (auto &x : a) x = int(rng() % 21) - 10;
            for (auto &x : b) x = int(rng() % 21) - 10;
            check(a, b);
            check_transforms(a);
        }
    }
}
