#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/modint_base.cpp"
#include "../util/fastio.cpp"
#include "../math/digit_dp.cpp"
#include "../math/digit_dfa.cpp"
#include "../string/avoid_patterns.cpp"
#include "../string/dfa_minimize.cpp"

struct AddOnly {
    long long value;
    explicit AddOnly(long long x) : value(x) {}
    AddOnly& operator+=(AddOnly x) { value += x.value; return *this; }
    bool operator==(AddOnly x) const { return value == x.value; }
};

bool accepts(const DFA<10>& a, int x) {
    int v = a.initial;
    for (char c : to_string(x)) if (v != -1) v = a.next[v][c - '0'];
    return v != -1 && a.accept[v];
}

void check(const DFA<10>& a, mt19937& rng) {
    vector<long long> counts(2002), sums(2002);
    for (int x = 0; x <= 2000; ++x) {
        bool ok = accepts(a, x);
        counts[x + 1] = counts[x] + ok;
        sums[x + 1] = sums[x] + (ok ? x : 0);
    }
    vector<pair<int, int>> intervals{
        {0, 0}, {0, 9}, {0, 99}, {0, 999}, {0, 2000}, {1, 2000},
        {9, 10}, {99, 100}, {999, 1000}, {1000, 999}, {2000, 2000}
    };
    for (int tc = 0; tc < 50; ++tc) intervals.emplace_back(rng() % 2001, rng() % 2001);
    for (auto [l, r] : intervals) {
        long long count = l <= r ? counts[r + 1] - counts[l] : 0;
        long long sum = l <= r ? sums[r + 1] - sums[l] : 0;
        string lower = string(rng() % 4, '0') + to_string(l);
        string upper = string(rng() % 4, '0') + to_string(r);
        auto answer = digit_count_sum<long long>(lower, upper, a);
        assert(answer == make_pair(count, sum));
        assert(digit_count<long long>(lower, upper, a) == count);
        auto modular = digit_count_sum<modint<7>>(lower, upper, a);
        assert(modular.first == modint<7>(count) && modular.second == modint<7>(sum));
        assert(digit_count<modint<7>>(lower, upper, a) == modint<7>(count));
    }
}

void self_check() {
    mt19937 rng(148);
    check(DFA<10>{}, rng);
    check(no_equal_adjacent(), rng);
    check(minimize(digit_value_mod(100)), rng);
    check(minimize(intersect(digit_sum_exact(12), digit_value_mod(12))), rng);
    for (int mask : {0, 1, 2, 3, 6, 17, 513, 1023}) check(required_digits(mask), rng);
    for (int m = 1; m <= 12; ++m) {
        check(digit_value_mod(m, m - 1), rng);
        check(digit_sum_mod(m, m - 1), rng);
    }
    for (int k = 0; k <= 30; ++k) {
        check(digit_sum_exact(k), rng);
        if (k) check(intersect(digit_sum_exact(k), digit_value_mod(k)), rng);
    }
    for (const vector<string>& patterns : vector<vector<string>>{
        {}, {""}, {"0"}, {"00"}, {"01"}, {"4", "9"}, {"404"}, {"10", "101"}
    }) check(avoid_patterns<10, '0'>(patterns), rng);
    for (int tc = 0; tc < 100; ++tc) {
        int n = 1 + rng() % 8;
        DFA<10> a{vector<array<int, 10>>(n), vector<char>(n), int(rng() % n)};
        for (int v = 0; v < n; ++v) {
            a.accept[v] = rng() % 2;
            for (int& to : a.next[v]) to = int(rng() % (n + 1)) - 1;
        }
        check(a, rng);
    }
    DFA<10> empty_only{vector<array<int, 10>>(1), {true}, 0};
    empty_only.next[0].fill(-1);
    assert(digit_count<int>("0", "0", empty_only) == 0);
    assert(digit_count<int>("0", "0", required_digits(1)) == 1);
    assert(digit_count<int>("1", "9", required_digits(1)) == 0);
    assert(digit_count<int>("0", "100", required_digits(1)) == 11);
    auto all = required_digits(0);
    assert(digit_count<AddOnly>("0", "1000", all).value == 1001);
    string limit = to_string(numeric_limits<long long>::max());
    assert(digit_count<long long>("1", limit, all) == numeric_limits<long long>::max());
    assert(digit_count_sum<long long>(limit, limit, all).second == numeric_limits<long long>::max());
    for (int x : {0, 1, 9, 10, 99, 100, 1000}) {
        string bound = string(500, '0') + to_string(x);
        assert(digit_count<AddOnly>(bound, bound, all).value == 1);
        assert(digit_count_sum<long long>(bound, bound, all) == make_pair(1LL, (long long)x));
    }
    auto rejecting = all;
    rejecting.accept[0] = false;
    assert(digit_count_sum<long long>("0", string(1000, '9'), rejecting) == make_pair(0LL, 0LL));
    using Mint = modint<998244353>;
    string upper(1000, '9');
    auto answer = digit_count_sum<Mint>("0", upper, all);
    Mint power = Mint(10).pow(1000);
    assert(answer.first == power && answer.second == power * (power - 1) / 2);
    auto forbidden = avoid_patterns<10, '0'>({"404"});
    assert(digit_count<Mint>("1", "1000", forbidden) == Mint(999));
    assert(digit_count<Mint>("1", "98765432109876543210", forbidden) == Mint(848152577));
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
