#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/xor_basis.cpp"

void exhaustive_check() {
    vector<uint32_t> spaces{1};
    set<uint32_t> seen{1};
    for (int i = 0; i < (int)spaces.size(); ++i) {
        uint32_t mask = spaces[i];
        for (int x = 1; x < 32; ++x) {
            if ((mask >> x) & 1) continue;
            uint32_t next = mask;
            for (int y = 0; y < 32; ++y) {
                if ((mask >> y) & 1) next |= uint32_t(1) << (x ^ y);
            }
            if (seen.insert(next).second) spaces.push_back(next);
        }
    }
    assert(spaces.size() == 374);
    vector<XorBasis<unsigned>> bases(spaces.size());
    for (int i = 0; i < (int)spaces.size(); ++i) {
        for (int x = 0; x < 32; ++x) {
            if ((spaces[i] >> x) & 1) bases[i].add(x);
        }
    }
    const auto original = bases;
    for (int i = 0; i < (int)spaces.size(); ++i) {
        for (int j = 0; j < (int)spaces.size(); ++j) {
            auto common = bases[i].intersection(bases[j]);
            uint32_t mask = spaces[i] & spaces[j];
            assert((1 << common.size()) == __builtin_popcount(mask));
            for (int x = 0; x < 32; ++x) assert(common.contains(x) == bool((mask >> x) & 1));
            assert(common.get_min() == 0);
            assert(common.get_max() == unsigned(31 - __builtin_clz(mask)));
            auto merged = common;
            merged.merge(bases[i]);
            assert(merged.size() == bases[i].size());
        }
        assert(bases[i].basis == original[i].basis && bases[i].size() == original[i].size());
    }
}

template<class T>
void wide_check() {
    mt19937_64 rng(131);
    for (int rep = 0; rep < 3000; ++rep) {
        XorBasis<T> a, b, empty;
        int n = rng() % 65, m = rng() % 65;
        for (int i = 0; i < n; ++i) a.add(static_cast<T>(rng()));
        for (int i = 0; i < m; ++i) b.add(static_cast<T>(rng()));
        a.add(0);
        b.add(0);
        auto common = a.intersection(b), reversed = b.intersection(a);
        auto merged = a;
        merged.merge(b);
        assert(common.size() == a.size() + b.size() - merged.size());
        assert(common.size() == reversed.size());
        for (auto x : common.basis) {
            assert(a.contains(static_cast<T>(x)) && b.contains(static_cast<T>(x)));
            assert(reversed.contains(static_cast<T>(x)));
        }
        auto self = a.intersection(a);
        assert(self.size() == a.size());
        for (auto x : a.basis) assert(self.contains(static_cast<T>(x)));
        assert(a.intersection(empty).empty() && empty.intersection(a).empty());
    }
    XorBasis<T> full, high;
    for (int i = 0; i < 64; ++i) assert(full.add(static_cast<T>(1ULL << i)));
    high.add(static_cast<T>(1ULL << 63));
    auto common = full.intersection(high);
    assert(common.size() == 1 && common.contains(static_cast<T>(1ULL << 63)));
    assert(full.intersection(full).size() == 64);
    assert(!high.add(static_cast<T>(1ULL << 63)));
}

int main() {
    exhaustive_check();
    wide_check<unsigned long long>();
    wide_check<long long>();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
