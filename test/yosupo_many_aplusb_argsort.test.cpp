#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <array>
#include <random>
#include <vector>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../geometry/argsort.cpp"

int pos(const Ar2 &x) {
    if (x[1] != 0) return x[1] < 0 ? -1 : 1;
    return x[0] < 0;
}

ll cross(const Ar2 &a, const Ar2 &b) {
    return (ll)a[0] * b[1] - (ll)a[1] * b[0];
}

bool same_dir(const Ar2 &a, const Ar2 &b) {
    return cross(a, b) == 0 && pos(a) == pos(b);
}

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 0; n <= 80; ++n) {
            for (int trial = 0; trial < 200; ++trial) {
                vector<Ar2> v;
                while ((int)v.size() < n) {
                    int x = uniform_int_distribution<int>(-6, 6)(rng);
                    int y = uniform_int_distribution<int>(-6, 6)(rng);
                    if (x == 0 && y == 0) continue;
                    v.push_back({x, y});
                }
                argsort(v);
                for (int i = 0; i + 1 < n; ++i) {
                    if (pos(v[i]) > pos(v[i + 1])) return 1;
                    if (pos(v[i]) == pos(v[i + 1]) && cross(v[i], v[i + 1]) < 0) return 1;
                }
            }
        }

        vector<Ar2> v = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        argsort(v);
        if (v != vector<Ar2>{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}) return 1;

        v = {{2, 2}, {1, 1}, {-3, -3}, {-1, -1}, {0, 2}, {0, -5}};
        argsort(v);
        for (int i = 0; i + 1 < (int)v.size(); ++i) {
            if (same_dir(v[i], v[i + 1])) continue;
            if (pos(v[i]) > pos(v[i + 1])) return 1;
            if (pos(v[i]) == pos(v[i + 1]) && cross(v[i], v[i + 1]) < 0) return 1;
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
