#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include <utility>
#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../datastructure/swag_deque.cpp"

struct Monoid {
    using T = pair<mint, mint>;
    static T f(T a, T b) {
        return {a.first * b.first, a.second * b.first + b.second};
    }
    static T e() { return {1, 0}; }
};

int main() {
    Scanner sc;
    Printer pr;

    int q;
    sc.read(q);
    TwoStackDeque<Monoid> deq;
    while (q--) {
        int t;
        sc.read(t);
        if (t == 0) {
            int a, b;
            sc.read(a, b);
            deq.push_front({a, b});
        } else if (t == 1) {
            int a, b;
            sc.read(a, b);
            deq.push_back({a, b});
        } else if (t == 2) {
            deq.pop_front();
        } else if (t == 3) {
            deq.pop_back();
        } else {
            int x;
            sc.read(x);
            auto [a, b] = deq.fold();
            pr.writeln((a * x + b).val);
        }
    }
    return 0;
}
