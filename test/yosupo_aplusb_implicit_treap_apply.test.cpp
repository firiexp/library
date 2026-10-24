#define STANDALONE

#include <algorithm>
#include <array>
#include <cassert>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

#include "../datastructure/implicit_treap.cpp"

struct StringAffine {
    using T = string;
    using L = array<int, 2>;
    static T f(const T &a, const T &b) { return a + b; }
    static T g(T a, L x) {
        for (char &c : a) c = ((unsigned char)c * x[0] + x[1]) % 128;
        return a;
    }
    static L h(L a, L b) { return {a[0] * b[0] % 128, (a[1] * b[0] + b[1]) % 128}; }
    static T e() { return ""; }
    static L l() { return {1, 0}; }
};

void mixed_operations() {
    mt19937 rng(198);
    for (int initial = 0; initial <= 70; ++initial) {
        string expected(initial, '\0');
        for (char &c : expected) c = rng() % 128;
        vector<string> values;
        for (char c : expected) values.emplace_back(1, c);
        ImplicitTreap<StringAffine> tr(values);
        for (int step = 0; step < 1000; ++step) {
            int n = expected.size();
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            if (step % 11 == 0) l = 0, r = n;
            int op = rng() % 6;
            if (op == 0 && n < 100) {
                char c = rng() % 128;
                tr.insert(l, string(1, c));
                expected.insert(expected.begin() + l, c);
            } else if (op == 1 && n) {
                int k = rng() % n;
                assert(tr.erase(k) == expected.substr(k, 1));
                expected.erase(k, 1);
            } else if (op == 2 && n) {
                int k = rng() % n;
                char c = rng() % 128;
                tr.set(k, string(1, c));
                expected[k] = c;
            } else if (op == 3) {
                tr.reverse(l, r);
                reverse(expected.begin() + l, expected.begin() + r);
            } else {
                for (int repeat = 0; repeat < 2; ++repeat) {
                    StringAffine::L x{int(rng() % 128), int(rng() % 128)};
                    auto count = tr.nodes.size(), capacity = tr.nodes.capacity();
                    int root = tr.root;
                    tr.apply(l, r, x);
                    for (int i = l; i < r; ++i) expected[i] = ((unsigned char)expected[i] * x[0] + x[1]) % 128;
                    assert(tr.nodes.size() == count && tr.nodes.capacity() == capacity);
                    assert(tr.root == root);
                    assert(tr.all_fold() == expected);
                }
            }
            assert(tr.size() == (int)expected.size());
            assert(tr.all_fold() == expected);
            if (step % 7 == 0) {
                n = expected.size();
                l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);
                assert(tr.fold(l, r) == expected.substr(l, r - l));
            }
        }
        for (int i = 0; i <= tr.size(); ++i) {
            for (int j = i; j <= tr.size(); ++j) {
                assert(tr.fold(i, j) == expected.substr(i, j - i));
            }
        }
        while (!expected.empty()) {
            assert(tr.pop_front() == expected.substr(0, 1));
            expected.erase(expected.begin());
        }
        tr.apply(0, 0, {0, 42});
        assert(tr.all_fold().empty());
    }
}

struct CountedSum {
    using T = array<long long, 2>;
    using L = long long;
    static inline int calls = 0;
    static T f(T a, T b) { ++calls; return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L x) { ++calls; return {a[0] + a[1] * x, a[1]}; }
    static L h(L a, L b) { ++calls; return a + b; }
    static T e() { return {0, 0}; }
    static L l() { return 0; }
};

void whole_and_empty_ranges() {
    constexpr int n = 100000;
    ImplicitTreap<CountedSum> tr(vector<CountedSum::T>(n, {0, 1}));
    for (int i = 0; i < 1000; ++i) {
        CountedSum::calls = 0;
        tr.apply(0, n, 1);
        assert(CountedSum::calls <= 4);
        assert(tr.all_fold()[0] == 1LL * (i + 1) * n);
        for (int k : {0, n / 2, n}) {
            CountedSum::calls = 0;
            tr.apply(k, k, 7);
            assert(CountedSum::calls == 0);
        }
    }
}

void insertion_and_erasure() {
    mt19937 rng(254);
    for (bool equal_priority : {false, true}) {
        ImplicitTreap<StringAffine> tr;
        if (equal_priority) tr.rng_state = 0;
        string expected;
        for (int step = 0; step < 800; ++step) {
            int n = expected.size();
            if (n) {
                tr.reverse(0, n);
                reverse(expected.begin(), expected.end());
                StringAffine::L x{int(rng() % 128), int(rng() % 128)};
                tr.apply(0, n, x);
                expected = StringAffine::g(expected, x);
            }
            if (step < 256 || (step < 544 && step % 2 == 0)) {
                int k = step % 3 == 0 ? 0 : step % 3 == 1 ? n : rng() % (n + 1);
                char c = rng() % 128;
                auto allocated = tr.nodes.size();
                bool reuse = !tr.free_nodes.empty();
                tr.insert(k, string(1, c));
                expected.insert(expected.begin() + k, c);
                assert(tr.nodes.size() == allocated + !reuse);
            } else if (n) {
                int k = step % 3 == 0 ? 0 : step % 3 == 1 ? n - 1 : rng() % n;
                assert(tr.erase(k) == expected.substr(k, 1));
                expected.erase(k, 1);
            }
            assert(tr.all_fold() == expected);
            assert(tr.size() == (int)expected.size());
            vector<bool> seen(tr.nodes.size());
            vector<int> todo;
            if (!tr.empty()) todo.push_back(tr.root);
            for (int i = 0; i < (int)todo.size(); ++i) {
                int v = todo[i];
                assert(!seen[v]);
                seen[v] = true;
                for (int child : {tr.nodes[v].l, tr.nodes[v].r}) {
                    if (child == -1) continue;
                    assert(tr.nodes[v].pri <= tr.nodes[child].pri);
                    todo.push_back(child);
                }
            }
            assert(todo.size() == expected.size());
            for (int v : tr.free_nodes) {
                assert(!seen[v]);
                seen[v] = true;
            }
            assert(count(seen.begin(), seen.end(), true) == (int)tr.nodes.size());
        }
        assert(tr.empty());
        tr.push_back("a");
        tr.push_front("b");
        assert(tr.pop_back() == "a");
        assert(tr.pop_front() == "b");
    }
}

int main() {
    mixed_operations();
    whole_and_empty_ranges();
    insertion_and_erasure();
}
