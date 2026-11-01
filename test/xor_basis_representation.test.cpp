#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../math/linear_algebra/xor_basis_with_ids.cpp"

template<class T>
void check_result(const XorBasisWithIds<T> &basis, const map<int, make_unsigned_t<T>> &input, T value, bool expected) {
    using U = make_unsigned_t<T>;
    auto result = basis.representation(value);
    assert(result.has_value() == expected);
    if (!result) return;
    U actual = 0;
    set<int> used;
    for (int id : *result) {
        assert(input.count(id) && used.insert(id).second);
        actual ^= input.at(id);
    }
    assert(actual == static_cast<U>(value));
    if (value == 0) assert(result->empty());
}

void check(const vector<unsigned> &values) {
    XorBasisWithIds<unsigned> basis;
    map<int, unsigned> input;
    set<unsigned> reachable = {0};
    assert(basis.empty() && basis.size() == 0);
    check_result(basis, input, 0U, true);
    check_result(basis, input, 1U, false);
    int rank = 0;
    for (int i = 0; i < (int)values.size(); ++i) {
        unsigned x = values[i];
        int id = 3 * i - 7;
        input[id] = x;
        bool independent = !reachable.count(x);
        assert(basis.add(x, id) == independent);
        rank += independent;
        auto before = reachable;
        for (unsigned value : before) reachable.insert(value ^ x);
        assert(basis.size() == rank && basis.empty() == (rank == 0));
        for (unsigned value = 0; value < 32; ++value)
            check_result(basis, input, value, reachable.count(value));
    }
}

template<class T>
void check_full_rank() {
    using U = make_unsigned_t<T>;
    constexpr int bits = numeric_limits<U>::digits;
    XorBasisWithIds<T> basis;
    map<int, U> input;
    vector<int> order(bits);
    iota(order.begin(), order.end(), 0);
    mt19937_64 rng(351);
    shuffle(order.begin(), order.end(), rng);
    for (int i : order) {
        U value = (U(1) << i) | ((U(1) << i) - 1);
        input[i - 20] = value;
        assert(basis.add(static_cast<T>(value), i - 20));
    }
    assert(basis.size() == bits);
    assert(!basis.add(T(0), 1000));
    assert(!basis.add(T(-1), 1001));
    for (int i = 0; i < 1000; ++i) check_result(basis, input, static_cast<T>(rng()), true);
    check_result(basis, input, numeric_limits<T>::min(), true);
    check_result(basis, input, numeric_limits<T>::max(), true);
    check_result(basis, input, T(0), true);
}

int main() {
    for (int n = 0, count = 1; n <= 5; ++n, count *= 4) {
        for (int mask = 0; mask < count; ++mask) {
            int x = mask;
            vector<unsigned> values(n);
            for (auto &value : values) {
                value = x % 4;
                x /= 4;
            }
            check(values);
        }
    }
    mt19937 rng(351);
    for (int tc = 0; tc < 400; ++tc) {
        vector<unsigned> values(rng() % 13);
        for (auto &x : values) x = rng() % 32;
        check(values);
    }
    check_full_rank<unsigned long long>();
    check_full_rank<long long>();
    check_full_rank<unsigned>();
    check_full_rank<unsigned char>();
    check_full_rank<signed char>();
}
