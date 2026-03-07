#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <iostream>
#include <vector>

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include "../fps/linear_recurrence.cpp"

int main() {
    int d;
    ll n;
    cin >> d >> n;
    vector<mint> a(d), c(d);
    for (int i = 0; i < d; ++i) {
        int x;
        cin >> x;
        a[i] = x;
    }
    for (int i = 0; i < d; ++i) {
        int x;
        cin >> x;
        c[i] = x;
    }
    cout << linear_recurrence(a, c, n).val << '\n';
    return 0;
}
