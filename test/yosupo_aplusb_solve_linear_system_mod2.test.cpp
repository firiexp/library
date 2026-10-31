#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/bitset/dynamic_bitset.cpp"
#include "../math/linear_algebra/solve_linear_system_mod2.cpp"
#include "../datastructure/bitset/dynamic_bitset.cpp"
#include "../math/linear_algebra/solve_linear_system_mod2.cpp"

int scalar_rank(const vector<DynamicBitset>& a, int m) {
    int n = (int)a.size(), rank = 0;
    vector<vector<int>> rows(n, vector<int>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) rows[i][j] = a[i].test(j);
    for (int col = 0; col < m && rank < n; ++col) {
        int pivot = rank;
        while (pivot < n && !rows[pivot][col]) ++pivot;
        if (pivot == n) continue;
        swap(rows[pivot], rows[rank]);
        for (int i = rank + 1; i < n; ++i) if (rows[i][col])
            for (int j = col; j < m; ++j) rows[i][j] ^= rows[rank][j];
        ++rank;
    }
    return rank;
}

bool satisfies(const vector<DynamicBitset>& a, const DynamicBitset& b, const DynamicBitset& x) {
    for (int i = 0; i < (int)a.size(); ++i) {
        bool value = false;
        for (int j = 0; j < x.size(); ++j) value ^= a[i].test(j) && x.test(j);
        if (value != b.test(i)) return false;
    }
    return true;
}

void check(const vector<DynamicBitset>& a, const DynamicBitset& b, int m) {
    auto original_a = a;
    auto original_b = b;
    auto solution = a.empty() ? solve_linear_system_mod2(a, b, m) : solve_linear_system_mod2(a, b);
    for (int i = 0; i < (int)a.size(); ++i) assert((a[i] ^ original_a[i]).none());
    assert((b ^ original_b).none());
    int rank = scalar_rank(a, m);
    vector<DynamicBitset> augmented(a.size(), DynamicBitset(m + 1));
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < m; ++j) augmented[i].assign(j, a[i].test(j));
        augmented[i].assign(m, b.test(i));
    }
    assert(bool(solution) == (rank == scalar_rank(augmented, m + 1)));
    if (solution) {
        assert(solution->rank == rank && solution->particular.size() == m);
        assert((int)solution->basis.size() == m - rank);
        assert(satisfies(a, b, solution->particular));
        for (const auto& v : solution->basis) {
            assert(v.size() == m);
            assert(satisfies(a, DynamicBitset((int)a.size()), v));
        }
        assert(scalar_rank(solution->basis, m) == m - rank);
    }
    if (m > 8) return;
    vector<bool> generated(1 << m);
    if (solution) {
        for (int mask = 0; mask < (1 << (m - rank)); ++mask) {
            auto x = solution->particular;
            for (int j = 0; j < m - rank; ++j) if (mask >> j & 1) x ^= solution->basis[j];
            int code = 0;
            for (int j = 0; j < m; ++j) if (x.test(j)) code |= 1 << j;
            assert(!generated[code]);
            generated[code] = true;
        }
    }
    for (int mask = 0; mask < (1 << m); ++mask) {
        DynamicBitset x(m);
        for (int j = 0; j < m; ++j) x.assign(j, mask >> j & 1);
        assert(generated[mask] == satisfies(a, b, x));
    }
}

int main() {
    auto empty = solve_linear_system_mod2({}, {});
    assert(empty && empty->rank == 0 && empty->particular.empty() && empty->basis.empty());
    for (int n = 0; n <= 3; ++n) for (int m = 0; m <= 3; ++m) {
        for (int mask = 0; mask < (1 << (n * (m + 1))); ++mask) {
            int bits = mask;
            vector<DynamicBitset> a(n, DynamicBitset(m));
            DynamicBitset b(n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j, bits >>= 1) a[i].assign(j, bits & 1);
                b.assign(i, bits & 1);
                bits >>= 1;
            }
            check(a, b, m);
        }
    }
    mt19937 rng(132);
    for (int m : {0, 1, 7, 8, 63, 64, 65, 127, 128, 129}) {
        check({}, {}, m);
        for (int tc = 0; tc < 30; ++tc) {
            int n = rng() % 20;
            vector<DynamicBitset> a(n, DynamicBitset(m));
            DynamicBitset b(n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) a[i].assign(j, rng() % 2);
                b.assign(i, rng() % 2);
            }
            check(a, b, m);
        }
    }
    vector<DynamicBitset> a(65, DynamicBitset(129));
    DynamicBitset b(65);
    for (int i = 0; i < 64; ++i) {
        a[i].set(128 - i);
        b.assign(i, i % 2);
    }
    a[64] = a[0];
    check(a, b, 129);
    b.flip(64);
    check(a, b, 129);
    auto moved = solve_linear_system_mod2(std::move(a), std::move(b));
    assert(!moved);
}
