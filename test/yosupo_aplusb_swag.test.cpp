#define STANDALONE

#include <cassert>
#include <deque>
#include <random>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <type_traits>
#include <charconv>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/swag.cpp"
#include "../datastructure/swag_deque.cpp"

struct Affine {
    using T = pair<long long, long long>;
    static T f(T a, T b) {
        return {a.first * b.first % 998244353,
                (a.second * b.first + b.second) % 998244353};
    }
    static T e() { return {1, 0}; }
};

struct Concat {
    using T = string;
    static T f(const T &a, const T &b) { return a + b; }
    static T e() { return ""; }
};

struct CopyOnly {
    string value;
    explicit CopyOnly(string s) : value(s) {}
    CopyOnly(const CopyOnly &) = default;
    CopyOnly &operator=(const CopyOnly &) = delete;
    bool operator==(const CopyOnly &other) const { return value == other.value; }
};

struct CopyOnlyConcat {
    using T = CopyOnly;
    static T f(const T &a, const T &b) { return T(a.value + b.value); }
    static T e() { return T(""); }
};

template<class G, class Generator>
void check(Generator generate) {
    mt19937 rng(122);
    for (int tc = 0; tc < 1000; ++tc) {
        SWAG<G> q;
        deque<typename G::T> values;
        auto verify = [&]() {
            const auto &view = q;
            assert(view.size() == values.size());
            assert(view.empty() == values.empty());
            auto expected = G::e();
            for (const auto &v : values) expected = G::f(expected, v);
            assert(q.fold() == expected);
        };
        verify();
        q.push(G::e());
        values.push_back(G::e());
        verify();
        assert(!q.empty() && q.fold() == G::e());
        for (int i = 0; i < 1000; ++i) {
            if (values.empty() || rng() % 2 == 0) {
                auto v = generate(rng);
                q.push(v);
                values.push_back(v);
            } else {
                q.pop();
                values.pop_front();
            }
            verify();
        }
        while (!values.empty()) {
            q.pop();
            values.pop_front();
            verify();
        }
        auto v = generate(rng);
        q.push(v);
        values.push_back(v);
        verify();
        q.pop();
        values.pop_front();
        verify();
        assert(q.fold() == G::e());
    }
}

template<class G, class Generator>
void check_deque(Generator generate) {
    mt19937 rng(330);
    TwoStackDeque<G> q;
    deque<typename G::T> values;
    auto verify = [&]() {
        const auto &view = q;
        assert(view.size() == values.size());
        assert(view.empty() == values.empty());
        auto expected = G::e();
        for (const auto &v : values) expected = G::f(expected, v);
        assert(q.fold() == expected);
    };
    verify();
    for (int tc = 0; tc < 100; ++tc) {
        q.push_back(G::e());
        values.push_back(G::e());
        verify();
        assert(!q.empty() && q.fold() == G::e());
        for (int i = 0; i < 1000; ++i) {
            int op = i < 64 ? tc % 2 : i < 128 ? 3 - tc % 2 : rng() % 4;
            if (op == 0) {
                auto v = generate(rng);
                q.push_front(v);
                values.push_front(v);
            } else if (op == 1) {
                auto v = generate(rng);
                q.push_back(v);
                values.push_back(v);
            } else if (op == 2) {
                q.pop_front();
                if (!values.empty()) values.pop_front();
            } else {
                q.pop_back();
                if (!values.empty()) values.pop_back();
            }
            verify();
        }
        while (!values.empty()) {
            if (rng() % 2) q.pop_front(), values.pop_front();
            else q.pop_back(), values.pop_back();
            verify();
        }
        q.pop_front();
        q.pop_back();
        verify();
    }
}

int main() {
    check<Affine>([](mt19937 &rng) { return Affine::T{rng() % 17, rng() % 19}; });
    check<Concat>([](mt19937 &rng) { return string(1, 'a' + rng() % 26); });
    check_deque<Affine>([](mt19937 &rng) { return Affine::T{rng() % 17, rng() % 19}; });
    check_deque<Concat>([](mt19937 &rng) { return string(1, 'a' + rng() % 26); });
    SWAG<CopyOnlyConcat> q;
    q.push(CopyOnly("a"));
    q.push(CopyOnly("b"));
    q.pop();
    q.push(CopyOnly("c"));
    assert(q.fold().value == "bc");
    q.pop();
    q.pop();
    assert(q.fold().value.empty());
    q.push(CopyOnly("d"));
    assert(q.fold().value == "d");
    q.pop();
}
