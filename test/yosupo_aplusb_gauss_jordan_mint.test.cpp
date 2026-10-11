#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 3;
#include "../util/fastio.cpp"
#include "../math/gauss_jordan_mint.cpp"

set<vector<mint>, bool (*)(const vector<mint>&, const vector<mint>&)> row_space(
        const vector<vector<mint>>& a, int width) {
    auto less = [](const vector<mint>& x, const vector<mint>& y) {
        for (int i = 0; i < (int)x.size(); ++i) {
            if (x[i] != y[i]) return x[i].val < y[i].val;
        }
        return false;
    };
    set<vector<mint>, bool (*)(const vector<mint>&, const vector<mint>&)> span(less);
    span.insert(vector<mint>(width));
    for (const auto& row : a) {
        vector<vector<mint>> previous(span.begin(), span.end());
        for (auto v : previous) {
            for (int c = 1; c < MOD; ++c) {
                for (int j = 0; j < width; ++j) v[j] += row[j];
                span.insert(v);
            }
        }
    }
    return span;
}

void check(vector<vector<mint>> a, bool extended) {
    auto original = a;
    int h = a.size(), w = a[0].size(), coefficients = w - (extended && w > 0);
    int rank = gauss_jordan(a, extended), previous = -1;
    assert(row_space(original, w) == row_space(a, w));
    int cardinality = 1;
    for (int i = 0; i < rank; ++i) cardinality *= MOD;
    assert((int)row_space(original, coefficients).size() == cardinality);
    for (int i = 0; i < h; ++i) {
        int pivot = 0;
        while (pivot < coefficients && a[i][pivot] == mint(0)) ++pivot;
        if (i >= rank) {
            assert(pivot == coefficients);
            continue;
        }
        assert(previous < pivot && pivot < coefficients);
        assert(a[i][pivot] == mint(1));
        for (int j = 0; j < h; ++j) if (j != i) assert(a[j][pivot] == mint(0));
        previous = pivot;
    }
    auto reduced = a;
    assert(gauss_jordan(a, extended) == rank && a == reduced);
}

void self_check() {
    check({{}, {}}, false);
    check({{0, 0, 1}, {0, 0, 2}}, true);
    check({{0, 0, 0}, {0, 1, 2}, {0, 2, 1}}, false);
    mt19937 rng(163);
    for (int tc = 0; tc < 400; ++tc) {
        int h = 1 + rng() % 6, w = rng() % 8;
        vector<vector<mint>> a(h, vector<mint>(w));
        for (auto& row : a) for (auto& x : row) x = rng() % MOD;
        if (w && tc % 3 == 0) for (auto& row : a) row[0] = 0;
        check(a, false);
        check(a, true);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
