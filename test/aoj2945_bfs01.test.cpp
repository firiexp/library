#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2945"

#include <cassert>
#include <array>
#include <bitset>
#include <cmath>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

template<class T>
constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../graph/bfs01.cpp"

int main() {
    Scanner in;
    Printer out;
    auto ok = [](int x) { return 0 <= x && x < 100; };
    auto id = [](int x, int y) { return x * 100 + y; };

    while (true) {
        int n;
        in.read(n);
        if (n == 0) break;
        int a, b, c, d;
        in.read(a, b, c, d);
        --a; --b; --c; --d;

        vector<vector<edge<int>>> g(10000);
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                int cost = (a <= i && i <= c && b <= j && j <= d) ? 0 : 1;
                static const int dx[4] = {1, 0, -1, 0};
                static const int dy[4] = {0, 1, 0, -1};
                for (int dir = 0; dir < 4; ++dir) {
                    int ni = i + dx[dir];
                    int nj = j + dy[dir];
                    if (!ok(ni) || !ok(nj)) continue;
                    g[id(ni, nj)].emplace_back(id(i, j), cost);
                }
            }
        }

        int sx, sy;
        in.read(sx, sy);
        --sx; --sy;
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            int tx, ty;
            in.read(tx, ty);
            --tx; --ty;
            vector<int> dist = bfs01(id(sx, sy), g);
            ans += dist[id(tx, ty)];
            sx = tx;
            sy = ty;
        }
        out.writeln(ans);
    }
    return 0;
}
