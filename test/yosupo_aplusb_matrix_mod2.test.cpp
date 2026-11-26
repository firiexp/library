#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../math/linear_algebra/matrix_mod2.cpp"

vector<DynamicBitset> random_matrix(int n, int m, mt19937 &rng) {
    vector<DynamicBitset> a(n, DynamicBitset(m));
    for (auto &row : a)
        for (int j = 0; j < m; ++j) if (rng() & 1) row.set(j);
    return a;
}

void check_product(int n, int m, int k, mt19937 &rng) {
    auto a = random_matrix(n, m, rng);
    auto b = random_matrix(m, k, rng);
    auto c = matrix_product_mod2(a, b, k);
    assert((int)c.size() == n);
    for (int i = 0; i < n; ++i) {
        assert(c[i].size() == k);
        for (int j = 0; j < k; ++j) {
            int sum = 0;
            for (int p = 0; p < m; ++p) sum += a[i].test(p) && b[p].test(j);
            assert(c[i].test(j) == (sum % 2));
        }
    }
    auto inferred = matrix_product_mod2(a, b);
    assert((int)inferred.size() == n);
    for (int i = 0; i < n; ++i) {
        if (m == 0) assert(inferred[i].empty());
        else assert(inferred[i].size() == k && inferred[i].count_xor(c[i]) == 0);
    }
}

void check_small_matrix(const vector<DynamicBitset> &a, int m) {
    int n = (int)a.size();
    set<int> span{0};
    for (const auto &row : a) {
        int mask = 0;
        for (int j = 0; j < m; ++j) if (row.test(j)) mask |= 1 << j;
        auto expanded = span;
        for (int x : span) expanded.insert(x ^ mask);
        span.swap(expanded);
    }
    assert((1U << matrix_rank_mod2(a)) == span.size());
    if (n != m) return;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    int det = 0;
    do {
        bool nonzero = true;
        for (int i = 0; i < n; ++i) nonzero &= a[i].test(perm[i]);
        det ^= nonzero;
    } while (next_permutation(perm.begin(), perm.end()));
    assert(matrix_determinant_mod2(a) == det);
}

int main() {
    mt19937 rng(567);
    for (int n = 0; n <= 3; ++n) {
        for (int m = 0; m <= 3; ++m) {
            for (int mask = 0; mask < (1 << (n * m)); ++mask) {
                vector<DynamicBitset> a(n, DynamicBitset(m));
                for (int i = 0; i < n; ++i)
                    for (int j = 0; j < m; ++j) a[i].assign(j, mask >> (i * m + j) & 1);
                check_small_matrix(a, m);
            }
            for (int k = 0; k <= 3; ++k) check_product(n, m, k, rng);
        }
    }
    for (int trial = 0; trial < 500; ++trial) {
        int n = rng() % 8, m = rng() % 8;
        check_small_matrix(random_matrix(n, m, rng), m);
        check_product(n, m, rng() % 8, rng);
    }
    for (int w : {63, 64, 65, 127, 128, 129}) {
        check_product(7, w, w, rng);
        vector<DynamicBitset> a(w, DynamicBitset(w));
        for (int i = 0; i < w; ++i) a[i].set(i);
        for (int i = 0; i < 4 * w; ++i) {
            int u = rng() % w, v = (u + 1 + rng() % (w - 1)) % w;
            a[u] ^= a[v];
        }
        shuffle(a.begin(), a.end(), rng);
        assert(matrix_determinant_mod2(a) == 1);
        a.back() = a[0];
        assert(matrix_determinant_mod2(a) == 0 && matrix_rank_mod2(a) == w - 1);
        a.pop_back();
        assert(matrix_rank_mod2(a) == w - 1);
        a.push_back(a[0]);
        a.push_back(a[0]);
        assert(matrix_rank_mod2(a) == w - 1);
    }
}
