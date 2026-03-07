#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../string/kmp.cpp"

int main() {
    string text, pattern;
    cin >> text >> pattern;
    auto res = kmp_search(text, pattern);
    for (auto &&i : res) {
        cout << i << "\n";
    }
    return 0;
}
