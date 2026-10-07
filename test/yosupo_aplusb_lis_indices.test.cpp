#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/lis.cpp"

template<class T>
void check(const vector<T> &a) {
    int n = a.size();
    for (bool strict : {false, true}) {
        int best = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            int previous = -1, length = 0;
            bool ok = true;
            for (int i = 0; i < n; ++i) if (mask >> i & 1) {
                if (previous >= 0)
                    ok &= strict ? a[previous] < a[i] : !(a[i] < a[previous]);
                previous = i;
                ++length;
            }
            if (ok) best = max(best, length);
        }
        auto indices = lis_indices(a, strict);
        assert((int)indices.size() == best);
        for (int i = 0; i < best; ++i) {
            assert(0 <= indices[i] && indices[i] < n);
            if (!i) continue;
            assert(indices[i - 1] < indices[i]);
            assert(strict ? a[indices[i - 1]] < a[indices[i]] : !(a[indices[i]] < a[indices[i - 1]]));
        }
    }
}

struct Value {
    int x;
    explicit Value(int x): x(x) {}
    bool operator<(const Value &other) const { return x < other.x; }
};

int main() {
    for (int n = 0, count = 1; n <= 8; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            vector<int> a(n);
            int x = mask;
            for (auto &v : a) v = x % 3 - 1, x /= 3;
            check(a);
        }
    }
    check(vector<long long>{LLONG_MIN, LLONG_MAX, LLONG_MIN, 0, LLONG_MAX, LLONG_MAX});
    check(vector<string>{"b", "a", "a", "c", "b", "d"});
    check(vector<Value>{Value(2), Value(1), Value(1), Value(3)});
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
