#define STANDALONE

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../tree/diameter_weighted.cpp"

void zero_weight_check() {
    vector<vector<pair<int, ll>>> g(4);
    for (int v = 1; v < 4; ++v) {
        g[0].push_back({v, 0});
        g[v].push_back({0, 0});
    }
    auto [zero, ends] = tree_diameter_weighted(g);
    assert(zero == 0);
    assert(0 <= ends.first && ends.first < 4 && 0 <= ends.second && ends.second < 4);
    g[0][1].second = g[2][0].second = 7;
    auto [dist, mixed] = tree_diameter_weighted(g);
    assert(dist == 7);
    assert((mixed.first == 2) != (mixed.second == 2));
}

int main() {
    zero_weight_check();
}
