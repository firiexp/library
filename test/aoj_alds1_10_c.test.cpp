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

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../string/lcs_bit.cpp"

int main() {
    int n;
    cin >> n;
    while(n--){
        string s, t;
        cin >> s >> t;
        cout << LCS_bit(s, t) << "\n";
    }
    return 0;
}
