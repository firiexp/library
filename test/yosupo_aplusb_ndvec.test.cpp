#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <random>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../util/ndvec.cpp"

template <size_t N>
long long brute_index(const array<int, N> &dim, const array<int, N> &idx) {
    long long p = 0;
    for (size_t i = 0; i < N; ++i) {
        p *= dim[i];
        p += idx[i];
    }
    return p;
}

void deterministic_check() {
    NdVec<int, 1> a({5}, -1);
    assert(a.size() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(a(i) == -1);
        a(i) = i * i;
        assert(a.index(i) == i);
    }
    for (int i = 0; i < 5; ++i) assert(a.data[i] == i * i);
    a.fill(7);
    for (int i = 0; i < 5; ++i) assert(a(i) == 7);

    NdVec<long long, 3> b({2, 3, 4}, -1);
    assert(b.size() == 24);
    assert((b.stride == array<long long, 3>{12, 4, 1}));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                long long value = 100 * i + 10 * j + k;
                b(i, j, k) = value;
                assert(b.index(i, j, k) == brute_index<3>({2, 3, 4}, {i, j, k}));
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                assert(b(i, j, k) == 100 * i + 10 * j + k);
            }
        }
    }

    const NdVec<long long, 3> c = b;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                assert(c(i, j, k) == 100 * i + 10 * j + k);
            }
        }
    }

    NdVec<int, 4> zero({0, 2, 3, 4}, 9);
    assert(zero.size() == 0);
    assert(zero.data.empty());

    NdVec<int, 0> scalar({}, 5);
    assert(scalar.size() == 1);
    assert(scalar.index() == 0);
    assert(scalar() == 5);
    scalar() = 8;
    assert(scalar() == 8);
}

void random_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 200; ++tc) {
        array<int, 4> dim;
        for (int i = 0; i < 4; ++i) dim[i] = rng() % 5 + 1;
        NdVec<long long, 4> a(dim, -1);
        vector<long long> brute((size_t)a.size(), -1);
        int q = 200;
        while (q--) {
            array<int, 4> idx;
            for (int i = 0; i < 4; ++i) idx[i] = rng() % dim[i];
            long long pos = brute_index(dim, idx);
            long long val = (long long)rng() * rng();
            a(idx[0], idx[1], idx[2], idx[3]) = val;
            brute[pos] = val;
            assert(a.index(idx[0], idx[1], idx[2], idx[3]) == pos);
            assert(a(idx[0], idx[1], idx[2], idx[3]) == brute[pos]);
        }
        assert(a.data == brute);
        a.fill(3);
        for (long long x : a.data) assert(x == 3);
    }

    array<int, 5> dim = {7, 6, 5, 4, 3};
    NdVec<int, 5> a(dim, 0);
    iota(a.data.begin(), a.data.end(), 0);
    for (int i = 0; i < dim[0]; ++i) {
        for (int j = 0; j < dim[1]; ++j) {
            for (int k = 0; k < dim[2]; ++k) {
                for (int l = 0; l < dim[3]; ++l) {
                    for (int m = 0; m < dim[4]; ++m) {
                        array<int, 5> idx = {i, j, k, l, m};
                        assert(a(i, j, k, l, m) == brute_index(dim, idx));
                    }
                }
            }
        }
    }
}

int main() {
    deterministic_check();
    random_check();

    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
