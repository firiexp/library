#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

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

void self_check() {
    mt19937 rng(0);
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
            int k = rng() % 3 + 1;

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
    self_check();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
