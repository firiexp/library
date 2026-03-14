#include <bits/stdc++.h>

static const int MOD = 998244353;
using namespace std;
template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
template <typename T> using PQ = priority_queue<T, vector<T>, greater<T>>;
template <typename T> using GPQ = priority_queue<T, vector<T>, greater<T>>;
constexpr int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},dx8[8]={1,1,0,-1,-1,-1,0,1},dy8[8]={0,1,1,1,0,-1,-1,-1};
template<class T> T ifloor(T x, T y) { return x/y - (x%y?(x<0)^(y<0):0); }
template<class T> T iceil(T x, T y) { return x/y + (x%y?(x>=0)^(y<0):0); }
template<class T> bool chmax(T& a, T b) { return a < b ? a = b, true : false; }
template<class T> bool chmin(T& a, T b) { return a > b ? a = b, true : false; }
template<class T> int lowerb(const vector<T>& a, const T& x) { return lower_bound(a.begin(), a.end(), x) - a.begin(); }
template<class T> int upperb(const vector<T>& a, const T& x) { return upper_bound(a.begin(), a.end(), x) - a.begin(); }
template<class T> void uniq(vector<T>& a) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }

template<class T>
vector<pair<T, int>> RLE(const vector<T>& a){
    if(a.empty()) return {};
    vector<pair<T, int>> p = {{a[0], 1}};
    for (int j = 1; j < (int)a.size(); ++j) {
        if(p.back().first == a[j]) p.back().second++;
        else p.emplace_back(a[j], 1);
    }
    return p;
}

int main() {
    return 0;
}
