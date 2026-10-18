#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_array.cpp"
#include "../string/suffix_array_query.cpp"
#include "../string/suffix_array.cpp"
#include "../string/suffix_array_query.cpp"

template<class Sequence>
void check(const Sequence& s, const vector<int>& values) {
    auto original = s;
    const SuffixArrayQuery q(s);
    assert(s == original);
    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        int rank = 0;
        for (int j = 0; j < n; ++j)
            rank += lexicographical_compare(values.begin() + j, values.end(), values.begin() + i, values.end());
        assert(q.suffix_rank(i) == rank);
    }
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) {
        int common = 0;
        while (i + common < n && j + common < n && values[i + common] == values[j + common]) ++common;
        assert(q.lce(i, j) == common);
    }
    for (int l1 = 0; l1 <= n; ++l1) for (int r1 = l1; r1 <= n; ++r1)
        for (int l2 = 0; l2 <= n; ++l2) for (int r2 = l2; r2 <= n; ++r2) {
            vector<int> a(values.begin() + l1, values.begin() + r1);
            vector<int> b(values.begin() + l2, values.begin() + r2);
            assert(q.compare(l1, r1, l2, r2) == (a > b) - (a < b));
        }
}

int main() {
    for (int n = 0, total = 1; n <= 6; ++n, total *= 3) {
        for (int mask = 0; mask < total; ++mask) {
            string s;
            vector<int> values;
            int code = mask;
            for (int i = 0; i < n; ++i) {
                int value = vector<int>{0, 128, 255}[code % 3];
                code /= 3;
                s.push_back((char)value);
                values.push_back(value);
            }
            check(s, values);
        }
    }
    mt19937 rng(146);
    for (int tc = 0; tc < 250; ++tc) {
        vector<int> values(rng() % 13);
        for (int& x : values) x = (int)(rng() % 9) - 4;
        check(values, values);
    }
    check(vector<int>{INT_MIN, 0, INT_MAX, INT_MIN}, {INT_MIN, 0, INT_MAX, INT_MIN});
}
