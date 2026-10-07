#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../util/modint_base.cpp"
#include "../datastructure/binaryindexedtree.cpp"

template<class T>
void check(const vector<T> &a) {
    auto before = a;
    BIT<T> bit(a), reference(a.size());
    for (int i = 0; i < (int)a.size(); ++i) reference.add(i, a[i]);
    T sum = 0;
    for (int i = 0; i <= (int)a.size(); ++i) {
        assert(bit.sum(i) == sum);
        assert(bit.sum(i) == reference.sum(i));
        if (i < (int)a.size()) sum += a[i];
    }
    assert(a == before);
}

int main() {
    for (int n = 0, count = 1; n <= 8; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            vector<long long> a(n);
            int x = mask;
            for (auto &v : a) v = x % 3 - 1, x /= 3;
            check(a);
            for (auto &v : a) ++v;
            BIT<long long> bit(a);
            for (long long target = -1; target <= 2 * n + 1; ++target) {
                int k = 0;
                long long sum = 0;
                while (k < n && sum < target) sum += a[k++];
                assert(bit.lower_bound(target) == k);
            }
        }
    }
    mt19937 rng(98);
    for (int tc = 0; tc < 200; ++tc) {
        int n = 1 + rng() % 100;
        vector<long long> a(n);
        for (auto &v : a) v = int(rng() % 201) - 100;
        check(a);
        vector<modint<998244353>> modular(a.begin(), a.end());
        check(modular);
        BIT<long long> bit(a);
        for (int q = 0; q < 100; ++q) {
            int i = rng() % n, delta = int(rng() % 201) - 100;
            a[i] += delta;
            bit.add(i, delta);
            long long sum = 0;
            for (int k = 0; k <= n; ++k) {
                assert(bit.sum(k) == sum);
                if (k < n) sum += a[k];
            }
        }
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
