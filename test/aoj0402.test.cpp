#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0402"
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

#include "../math/fwht.cpp"

int main() {
    int n; ll k;
    cin >> n >> k;
    int S = 0;
    vector<ll> A(1<<20);
    A[0] = 1;
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        S ^= x;
        A[S]++;
    }
    fwht(A);
    for (int i = 0; i < 1<<20; ++i) A[i] *= A[i];
    ifwht(A);
    for (int i = (1<<20); i >= 0; --i) {
        k -= A[i]/2;
        if(k <= 0){
            cout << i << "\n";
            return 0;
        }
    }
    return 0;
}