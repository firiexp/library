#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <cassert>
#include <random>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../string/lcs_bit.cpp"

void self_check() {
    mt19937 rng(54);
    const vector<int> sizes{0, 1, 63, 64, 65, 127, 128, 129};
    for (int tc = 0; tc < 400; ++tc) {
        string a(sizes[tc % sizes.size()], '\0');
        string b(sizes[(tc / sizes.size()) % sizes.size()], '\0');
        for (char &c : a) c = char(rng() % (tc % 2 ? 256 : 3));
        for (char &c : b) c = char(rng() % (tc % 2 ? 256 : 3));
        vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
        for (int i = 0; i < (int)a.size(); ++i) for (int j = 0; j < (int)b.size(); ++j)
            dp[i + 1][j + 1] = a[i] == b[j] ? dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);
        auto original_a = a, original_b = b;
        assert(LCS_bit(a, b) == dp.back().back());
        assert(LCS_bit(b, a) == dp.back().back());
        assert(a == original_a && b == original_b);
    }
}

int main() {
    self_check();
    int n;
    cin >> n;
    while(n--){
        string s, t;
        cin >> s >> t;
        cout << LCS_bit(s, t) << "\n";
    }
    return 0;
}
