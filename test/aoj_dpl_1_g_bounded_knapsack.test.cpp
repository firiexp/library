#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_G"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../math/bounded_knapsack.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, capacity;
    sc.read(n, capacity);
    vector<BoundedKnapsackItem> items(n);
    for (auto& item : items) sc.read(item.value, item.weight, item.count);
    auto dp = bounded_knapsack(items, capacity);
    pr.println(*max_element(dp.begin(), dp.end()));
}
