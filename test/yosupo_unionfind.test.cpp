#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <cstdint>

static const int MOD = 1000000007;
using ll = long long;
using uint = uint32_t;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../datastructure/unionfind.cpp"
#include "../util/fastio.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n);
    in.read(q);
    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        in.read(t);
        in.read(u);
        in.read(v);
        if(t) out.writeln(uf.same(u, v));
        else uf.unite(u, v);
    }
    return 0;
}
