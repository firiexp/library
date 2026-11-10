#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/segmenttree/static_range_mex.cpp"

template<class T>
int brute(const vector<T>& a, int l, int r) {
    set<T> values(a.begin() + l, a.begin() + r);
    int mex = 0;
    while (values.count(mex)) ++mex;
    return mex;
}

template<class T>
void check(const vector<T>& a, mt19937& rng) {
    vector<pair<int, int>> queries;
    int n = (int)a.size();
    for (int l = 0; l <= n; ++l) {
        for (int r = l; r <= n; ++r) queries.emplace_back(l, r);
    }
    queries.emplace_back(0, n);
    queries.emplace_back(n, n);
    shuffle(queries.begin(), queries.end(), rng);
    auto original = queries;
    auto saved = a;
    auto result = static_range_mex(a, queries);
    assert(result.size() == queries.size());
    assert(a == saved && queries == original);
    for (int i = 0; i < (int)queries.size(); ++i) {
        assert(result[i] == brute(a, queries[i].first, queries[i].second));
    }
    assert(static_range_mex(a, {}).empty());
}

int main() {
    mt19937 rng(407);
    vector<int> a{0, 1, 0, 2};
    vector<pair<int, int>> queries{ {0, 4}, {0, 0}, {1, 3}, {0, 1}, {0, 4}, {3, 4}, {1, 2}};
    assert(static_range_mex(a, queries) == vector<int>({3, 0, 2, 1, 3, 0, 0}));
    check(vector<int>{}, rng);
    check(vector<int>{0, 1, 2, 3, 4, 5}, rng);
    check(vector<int>{5, 4, 3, 2, 1, 0}, rng);
    check(vector<int>{0, 0, 0, 0}, rng);
    check(vector<long long>{LLONG_MIN, 0, LLONG_MAX, 1, -1}, rng);
    vector<int> alphabet{-1, 0, 1, 2, 100};
    for (int n = 0, count = 1; n <= 6; ++n, count *= (int)alphabet.size()) {
        for (int mask = 0; mask < count; ++mask) {
            vector<int> values(n);
            int x = mask;
            for (auto& value : values) {
                value = alphabet[x % alphabet.size()];
                x /= alphabet.size();
            }
            check(values, rng);
        }
    }
    for (int tc = 0; tc < 200; ++tc) {
        int n = rng() % 70;
        vector<long long> values(n);
        for (auto& x : values) x = (int)(rng() % (n + 10)) - 4;
        if (tc % 3 == 0) for (int i = 0; i < n; ++i) values[i] = i;
        check(values, rng);
    }
}
