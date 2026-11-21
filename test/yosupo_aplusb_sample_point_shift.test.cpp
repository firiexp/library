#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../fps/sample_point_shift.cpp"

int main() {
    mt19937 rng(392);
    for (int n : {0, 1, 16, 17, 48, 49, 64, 65, 129}) {
        poly f(n);
        for (auto& coeff : f.v) coeff = rng() % ntt_mod;
        vector<mint> ys(n);
        for (int i = 0; i < n; ++i) ys[i] = f.eval(i);
        for (int c : {0, max(0, n - 1), n, n + 7, ntt_mod - 40, ntt_mod - 1}) {
            for (int m : {0, 1, 63, 64, 65, 127, 128, 129, 257}) {
                auto values = sample_point_shift(ys, c, m);
                assert((int)values.size() == m);
                for (int i = 0; i < m; ++i) assert(values[i] == f.eval(c + i));
            }
        }
    }
}
