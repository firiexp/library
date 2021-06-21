#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;


#include "../string/suffix_array.cpp"

int main() {
    string s;
    cin >> s;
    auto ans = suffix_array(s);
    for (int i = 0; i < ans.size(); ++i) {
        if(i) printf(" ");
        printf("%d", ans[i]);
    }
    puts("");
    return 0;
}