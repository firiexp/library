#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
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
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../string/suffix_array.cpp"

int main() {
    string s;
    cin >> s;
    auto sa = suffix_array(s);
    auto v = lcp(s, sa);
    ll n = s.size();
    ll ans = n*(n+1)/2-accumulate(v.begin(),v.end(), 0LL);
    cout << ans << "\n";
    return 0;
}