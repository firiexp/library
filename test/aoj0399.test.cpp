#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0399"
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

#include "../util/modint.cpp"

#include "../math/squarematrix.cpp"

struct SemiRing {
    using T = mint;
    static inline T mul(T x, T y){ return x * y; }
    static inline void add(T &x, T y){ x += y; }
    static inline T one(){ return 1; }
    static inline T zero(){ return 0; }
};

using ar = array<SemiRing::T, 101>;
using mat = SquareMatrix<SemiRing, 101>;

ar x;
mat A;
int main() {
    int n, m; ll d;
    cin >> n >> m >> d;
    vector<int> s(n), t(n), f(m);
    for (auto &&i : s) scanf("%d", &i);
    for (auto &&i : t) scanf("%d", &i);
    for (auto &&i : f) scanf("%d", &i);
    A[0][0] = 1;
    for (int i = 0; i < n; ++i) x[i+1] = s[i], A[i+1][0] = t[i], A[i+1][(i+n-1)%n+1] = 1;
    for (int i = 0; i < m; ++i) x[n+i+1] = f[i],  A[n+i+1][(i+m-1)%m+n+1] = 1;
    A[n+1][n] = 1;
    A = A.pow(d);
    cout << (x*A)[0].val << "\n";
    return 0;
}