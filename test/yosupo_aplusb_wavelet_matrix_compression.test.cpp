#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/wavelet_matrix.cpp"
#include "../datastructure/weighted_wavelet_matrix.cpp"

template<class T>
void check_compression() {
    mt19937_64 rng(256);
    WaveletMatrix<T> wm;
    WeightedWaveletMatrix<T, long long> weighted;
    for (int n : {0, 1, 2, 16, 63, 64, 65, 1023, 1024, 1025, 2048, 4096, 0}) {
        for (int mode = 0; mode < 5; ++mode) {
            vector<T> v(n);
            vector<long long> w(n);
            for (int i = 0; i < n; ++i) {
                if (mode == 0) v[i] = T(rng());
                if (mode == 1) v[i] = numeric_limits<T>::lowest();
                if (mode == 2) v[i] = T(rng() % 16);
                if (mode == 3) v[i] = T(n - i);
                if (mode == 4) v[i] = i + 1 == n ? numeric_limits<T>::max() : T(0);
                w[i] = int(rng() % 1001) - 500;
            }
            if (n >= 2 && mode == 0) {
                v[0] = numeric_limits<T>::lowest();
                v[1] = numeric_limits<T>::max();
            }
            auto original = v;
            auto original_weights = w;
            vector<T> vals = v;
            sort(vals.begin(), vals.end());
            vals.erase(unique(vals.begin(), vals.end()), vals.end());
            vector<int> index(n);
            for (int i = 0; i < n; ++i) index[i] = lower_bound(vals.begin(), vals.end(), v[i]) - vals.begin();
            wm.build(v);
            weighted.build(v, w);
            WaveletMatrix<T> reference;
            WeightedWaveletMatrix<T, long long> weighted_reference;
            reference.build_from_index(index, vals);
            weighted_reference.build_from_index(index, vals, w);
            assert(wm.vals == vals && weighted.vals == vals);
            assert(wm.mid == reference.mid && weighted.mid == weighted_reference.mid);
            assert(wm.bit == reference.bit && weighted.bit == weighted_reference.bit);
            assert(wm.pref == reference.pref && weighted.pref == weighted_reference.pref);
            assert(weighted.zero_sum == weighted_reference.zero_sum);
            assert(weighted.base_sum == weighted_reference.base_sum);
            for (int step = 0; step < 100; ++step) {
                int l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);
                T x = step % 3 == 0 ? numeric_limits<T>::lowest() : step % 3 == 1 ? numeric_limits<T>::max() : T(rng());
                int count = 0;
                long long sum = 0;
                for (int i = l; i < r; ++i) {
                    if (v[i] < x) ++count, sum += w[i];
                }
                auto result = weighted.count_sum_less(l, r, x);
                assert(result.count == count && result.sum == sum);
                assert(wm.count_less(l, r, x) == count);
                if (l < r) {
                    vector<T> sorted(v.begin() + l, v.begin() + r);
                    sort(sorted.begin(), sorted.end());
                    int k = rng() % (r - l);
                    assert(wm.kth_smallest(l, r, k) == sorted[k]);
                }
            }
            assert(v == original && w == original_weights);
        }
    }
}

struct Key {
    int value;
    bool operator<(const Key &other) const { return value < other.value; }
};

int main() {
    check_compression<int>();
    check_compression<unsigned>();
    check_compression<long long>();
    check_compression<unsigned long long>();
    vector<Key> keys{{2}, {1}, {2}, {0}};
    WaveletMatrix<Key> wm(keys);
    WeightedWaveletMatrix<Key, long long> weighted(keys, {10, -5, 7, 3});
    assert(wm.kth_smallest(0, 4, 2).value == 2);
    assert(wm.count_less(0, 4, Key{2}) == 2);
    assert(weighted.count_sum_less(0, 4, Key{2}).sum == -2);
}
