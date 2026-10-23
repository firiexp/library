#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/minimum_rotation.cpp"
#include "../string/minimum_rotation.cpp"

template<class Sequence, class T>
void check(const Sequence& s, const vector<T>& values) {
    auto original = s;
    int n = (int)s.size(), expected = 0;
    auto smallest = values;
    for (int i = 1; i < n; ++i) {
        vector<T> rotated(values.begin() + i, values.end());
        rotated.insert(rotated.end(), values.begin(), values.begin() + i);
        if (rotated < smallest) {
            smallest = rotated;
            expected = i;
        }
    }
    assert(minimum_rotation_index(s) == expected);
    assert(!lexicographical_compare(s.begin(), s.end(), original.begin(), original.end()));
    assert(!lexicographical_compare(original.begin(), original.end(), s.begin(), s.end()));
}

struct Value {
    int x;
    inline static int comparisons = 0;
    bool operator<(const Value& other) const {
        ++comparisons;
        return x < other.x;
    }
};

int main() {
    for (int n = 0; n <= 11; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string s(n, '\0');
        vector<int> bytes(n);
        for (int i = 0; i < n; ++i) s[i] = char(bytes[i] = mask >> i & 1 ? 255 : 0);
        check(s, bytes);
        vector<char> chars(s.begin(), s.end());
        check(chars, chars);
    }
    assert(minimum_rotation_index(string("baba")) == 1);
    assert(minimum_rotation_index(string("bcabca")) == 2);
    assert(minimum_rotation_index(string("bbbbba")) == 5);
    check(vector<int>{INT_MIN, INT_MAX, -1, INT_MIN}, vector<int>{INT_MIN, INT_MAX, -1, INT_MIN});
    vector<Value> values{ {2}, {1}, {2}, {1}};
    check(values, values);
    mt19937 rng(281);
    for (int tc = 0; tc < 5000; ++tc) {
        vector<int> a(rng() % 100);
        for (int& x : a) x = (int)(rng() % 17) - 8;
        check(a, a);
        string s(a.size(), '\0');
        vector<int> bytes(a.size());
        for (int i = 0; i < (int)s.size(); ++i) s[i] = char(bytes[i] = rng() % 256);
        check(s, bytes);
        vector<char> chars(s.begin(), s.end());
        check(chars, chars);
    }
    const int n = 200000;
    for (int kind = 0; kind < 4; ++kind) {
        vector<Value> a(n, {1});
        if (kind == 1) a.back().x = 0;
        if (kind == 2) a.front().x = 2;
        if (kind == 3) for (int i = 0; i < n; ++i) a[i].x = 1 - i % 2;
        Value::comparisons = 0;
        int result = minimum_rotation_index(a);
        assert(Value::comparisons <= 6 * n);
        assert(result == (kind == 0 ? 0 : kind == 1 ? n - 1 : 1));
    }
}
