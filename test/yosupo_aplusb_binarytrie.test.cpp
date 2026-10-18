#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/binarytrie.cpp"

constexpr int B = 8;
constexpr unsigned MASK = (1u << B) - 1;

int total_size(const vector<int> &freq) {
    return accumulate(freq.begin(), freq.end(), 0);
}

vector<unsigned> expand(const vector<int> &freq) {
    vector<unsigned> res;
    res.reserve(total_size(freq));
    for (unsigned x = 0; x <= MASK; ++x) {
        for (int k = 0; k < freq[x]; ++k) res.push_back(x);
    }
    return res;
}

unsigned brute_xor_min(const vector<int> &freq, unsigned x) {
    unsigned best = MASK;
    bool found = false;
    for (unsigned a = 0; a <= MASK; ++a) {
        if (freq[a] == 0) continue;
        unsigned cur = a ^ x;
        if (!found || cur < best) {
            best = cur;
            found = true;
        }
    }
    return best;
}

unsigned brute_min_element(const vector<int> &freq, unsigned x) {
    unsigned best_xor = MASK;
    unsigned best_val = 0;
    bool found = false;
    for (unsigned a = 0; a <= MASK; ++a) {
        if (freq[a] == 0) continue;
        unsigned cur = a ^ x;
        if (!found || cur < best_xor) {
            best_xor = cur;
            best_val = a;
            found = true;
        }
    }
    return best_val;
}

unsigned brute_max_element(const vector<int> &freq, unsigned x) {
    unsigned best_xor = 0;
    unsigned best_val = 0;
    bool found = false;
    for (unsigned a = 0; a <= MASK; ++a) {
        if (freq[a] == 0) continue;
        unsigned cur = a ^ x;
        if (!found || cur > best_xor) {
            best_xor = cur;
            best_val = a;
            found = true;
        }
    }
    return best_val;
}

void verify_state(const Binarytrie<unsigned, B> &trie, const vector<int> &freq, mt19937 &rng) {
    int sz = total_size(freq);
    assert(trie.size() == sz);
    assert(trie.empty() == (sz == 0));

    for (unsigned x = 0; x <= MASK; ++x) {
        assert(trie.count(x) == freq[x]);
        assert(trie.contains(x) == (freq[x] > 0));
    }

    if (sz == 0) return;
    for (int rep = 0; rep < 64; ++rep) {
        unsigned x = rng() & MASK;
        assert(trie.xor_min(x) == brute_xor_min(freq, x));
        assert(trie.min_element(x) == brute_min_element(freq, x));
        assert(trie.max_element(x) == brute_max_element(freq, x));
    }
}

template<class T, size_t X>
void verify_order(const Binarytrie<T, X> &trie, vector<T> values, T mask, const vector<T> &bounds) {
    sort(values.begin(), values.end(), [mask](T a, T b) { return (a ^ mask) < (b ^ mask); });
    for (int k = 0; k < (int)values.size(); ++k) assert(trie.kth_element(k, mask) == values[k]);
    if (!values.empty()) {
        assert(trie.kth_element(0, mask) == trie.min_element(mask));
        assert(trie.kth_element(trie.size() - 1, mask) == trie.max_element(mask));
    }
    for (T bound : bounds) {
        int expected = count_if(values.begin(), values.end(), [=](T x) { return (x ^ mask) < bound; });
        assert(trie.count_less(bound, mask) == expected);
        if (mask == 0) assert(trie.count_less(bound) == expected);
    }
    if (mask == 0) {
        for (int k = 0; k < (int)values.size(); ++k) assert(trie.kth_element(k) == values[k]);
    }
}

void order_check() {
    mt19937 rng(208);
    Binarytrie<unsigned, B> trie;
    vector<int> freq(1 << B);
    vector<unsigned> bounds(1 << B);
    iota(bounds.begin(), bounds.end(), 0);
    for (int step = 0; step < 2000; ++step) {
        if (step % 100 == 0) {
            for (unsigned x : bounds) assert(trie.erase(x, freq[x]));
            fill(freq.begin(), freq.end(), 0);
        } else {
            unsigned x = rng() & MASK;
            int k = rng() % 4;
            if (rng() % 2) {
                trie.add(x, k);
                freq[x] += k;
            } else {
                bool ok = trie.erase(x, k);
                assert(ok == (freq[x] >= k));
                if (ok) freq[x] -= k;
            }
        }
        auto values = expand(freq);
        for (unsigned mask : {0u, MASK, unsigned(rng()) & MASK}) verify_order(trie, values, mask, bounds);
    }
    using U = uint64_t;
    U high = U(1) << 63;
    vector<U> values = {0, 0, 1, high - 1, high, high, high + 1, ~U(0)};
    vector<U> wide_bounds = values;
    wide_bounds.push_back(2);
    Binarytrie<U, 64> wide(values);
    for (U mask : {U(0), U(1), high, ~U(0)}) verify_order(wide, values, mask, wide_bounds);
    assert(wide.count_less(~U(0)) == (int)values.size() - 1);
    Binarytrie<int, 31> signed_trie({0, 1, INT_MAX, INT_MAX});
    verify_order(signed_trie, vector<int>{0, 1, INT_MAX, INT_MAX}, INT_MAX, vector<int>{0, 1, INT_MAX});
}

void self_check() {
    mt19937 rng(0);
    Binarytrie<unsigned, 30> churn;
    churn.add(123, 0);
    assert(churn.erase(456, 0));
    assert(churn.nodes.size() == 1 && churn.empty());
    for (int i = 0; i < 500000; ++i) {
        unsigned x = rng() & ((1u << 30) - 1);
        churn.add(x, 3);
        assert(churn.xor_min(x ^ 123) == 123);
        assert(!churn.erase(x, 4));
        assert(churn.count(x) == 3);
        assert(churn.erase(x, 2));
        assert(churn.count(x) == 1);
        assert(churn.erase(x));
        assert(churn.empty() && churn.count(x) == 0);
        assert(churn.nodes.size() == 31);
    }
    Binarytrie<unsigned, 30> window;
    multiset<unsigned> values;
    deque<unsigned> order;
    for (int i = 0; i < 10000; ++i) {
        unsigned x = rng() & ((1u << 30) - 1);
        if (i % 3 == 0 && !order.empty()) x = order.back();
        window.add(x);
        order.push_back(x);
        values.insert(x);
        if (order.size() > 32) {
            unsigned y = order.front();
            order.pop_front();
            assert(window.erase(y));
            values.erase(values.find(y));
        }
        unsigned q = rng() & ((1u << 30) - 1), expected = ~0u;
        for (unsigned y : values) expected = min(expected, y ^ q);
        assert(window.xor_min(q) == expected);
        assert(window.nodes.size() <= 1 + 30 * 33);
        assert(window.size() == int(values.size()));
    }
    auto copied = window;
    while (!order.empty()) {
        assert(copied.erase(order.front()));
        order.pop_front();
    }
    assert(copied.empty() && !window.empty());
    for (int tc = 0; tc < 200; ++tc) {
        int n = rng() % 40;
        vector<unsigned> init(n);
        vector<int> freq(1 << B, 0);
        for (unsigned &x : init) {
            x = rng() & MASK;
            ++freq[x];
        }

        Binarytrie<unsigned, B> trie(init);
        verify_state(trie, freq, rng);

        Binarytrie<unsigned, B> reserved;
        reserved.reserve(n + 200);
        for (unsigned x : init) reserved.add(x);
        verify_state(reserved, freq, rng);

        for (int step = 0; step < 200; ++step) {
            int op = rng() % 5;
            unsigned x = rng() & MASK;
            int k = rng() % 4;

            if (op <= 1) {
                trie.add(x, k);
                freq[x] += k;
            } else if (op == 2) {
                bool ok = trie.erase(x, k);
                bool can = freq[x] >= k;
                assert(ok == can);
                if (can) freq[x] -= k;
            } else if (op == 3) {
                auto cur = expand(freq);
                Binarytrie<unsigned, B> rebuilt(cur);
                verify_state(rebuilt, freq, rng);
            } else {
                assert(trie.count(x) == freq[x]);
                assert(trie.contains(x) == (freq[x] > 0));
            }

            verify_state(trie, freq, rng);
        }
    }
}

int main() {
    order_check();
    self_check();

}
