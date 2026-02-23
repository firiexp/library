#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <limits>
#include <array>
#include <unordered_map>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

template<class T>T ifloor(T x, T y){
    return x/y-(x%y ? (x < 0)^(y < 0) : 0);
}

template<class T>inline T iceil(T x, T y){
    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template <typename T>
using GPQ = priority_queue<T, vector<T>, greater<T>>;

template<class T>
vector<pair<T, int>> RLE(vector<T> &a){
    vector<pair<int, int>> p;
    p.emplace_back(a[0], 1);
    for (int j = 1; j < a.size(); ++j) {
        if(p.back().first == a[j]) p.back().second++;
        else p.emplace_back(a[j], 1);
    }
    return p;
}

int main() {
    
    return 0;
}
