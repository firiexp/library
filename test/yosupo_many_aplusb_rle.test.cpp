#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <random>
#include <utility>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../util/rle.cpp"

template<class T>
vector<pair<T, int>> brute_rle(const vector<T> &a) {
    vector<pair<T, int>> res;
    for (const auto &x : a) {
        if (!res.empty() && res.back().first == x) {
            res.back().second++;
        } else {
            res.emplace_back(x, 1);
        }
    }
    return res;
}

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 0; n <= 80; ++n) {
            for (int trial = 0; trial < 200; ++trial) {
                vector<int> a(n);
                for (int i = 0; i < n; ++i) {
                    a[i] = uniform_int_distribution<int>(0, 6)(rng);
                }
                if (RLE(a) != brute_rle(a)) return 1;
            }
        }

        vector<int> empty;
        if (!RLE(empty).empty()) return 1;
        if (RLE(vector<int>{5, 5, 5}) != vector<pair<int, int>>{{5, 3}}) return 1;
        if (RLE(vector<int>{1, 2, 3, 4}) != vector<pair<int, int>>{{1, 1}, {2, 1}, {3, 1}, {4, 1}}) return 1;
        if (RLE(vector<int>{2, 2, 1, 1, 1, 3, 2, 2}) != vector<pair<int, int>>{{2, 2}, {1, 3}, {3, 1}, {2, 2}}) return 1;
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
