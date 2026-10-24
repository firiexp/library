#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/active_pattern_matcher.cpp"
#include "../string/active_pattern_matcher.cpp"

long long oracle(const vector<string> &patterns, const vector<long long> &weight, const string &text) {
    __int128 answer = 0;
    for (int id = 0; id < (int)patterns.size(); ++id) {
        for (int i = 0; i + patterns[id].size() <= text.size(); ++i) {
            if (text.compare(i, patterns[id].size(), patterns[id]) == 0) answer += weight[id];
        }
    }
    return (long long)answer;
}

int main() {
    ActivePatternMatcher<3, 'a'> empty({});
    assert(empty.query("") == 0 && empty.query("abc") == 0);
    ActivePatternMatcher<3, 'a'> roots({"", ""});
    roots.set_weight(0, 3);
    roots.set_weight(1, -2);
    assert(roots.query("") == 1 && roots.query("abc") == 4);
    roots.set_weight(0, 0);
    assert(roots.query("a") == -4);
    ActivePatternMatcher<3, 'a'> limits({"a", "b", "a"});
    for (long long weight : {LLONG_MIN, LLONG_MAX, 0LL}) {
        limits.set_weight(0, weight);
        assert(limits.query("a") == weight && limits.query("") == 0);
    }
    limits.set_weight(0, LLONG_MAX);
    limits.set_weight(1, -LLONG_MAX);
    assert(limits.query("aabb") == 0);
    limits.set_weight(2, LLONG_MIN);
    assert(limits.query("aa") == -2);
    mt19937 rng(285);
    auto random_string = [&](int maximum) {
        string s(rng() % (maximum + 1), 'a');
        for (char &c : s) c += rng() % 3;
        return s;
    };
    for (int trial = 0; trial < 1000; ++trial) {
        vector<string> patterns(rng() % 16);
        for (auto &s : patterns) s = random_string(8);
        vector<long long> weight(patterns.size());
        ActivePatternMatcher<3, 'a'> matcher(patterns);
        for (int step = 0; step < 50; ++step) {
            if (!patterns.empty()) {
                int id = rng() % patterns.size();
                weight[id] = int(rng() % 21) - 10;
                matcher.set_weight(id, weight[id]);
            }
            string text = random_string(30);
            assert(matcher.query(text) == oracle(patterns, weight, text));
            assert(matcher.query("") == oracle(patterns, weight, ""));
        }
    }
    ActivePatternMatcher<1, 'a'> deep({"", "a", string(200000, 'a')});
    deep.set_weight(0, -1);
    deep.set_weight(1, 2);
    deep.set_weight(2, 5);
    assert(deep.query(string(200001, 'a')) == 200010);
    vector<string> nested;
    for (int i = 0; i <= 1000; ++i) nested.emplace_back(i, 'a');
    ActivePatternMatcher<1, 'a'> many(nested);
    for (int i = 0; i <= 1000; ++i) many.set_weight(i, 1);
    assert(many.query(string(100000, 'a')) == 1001LL * 100001 - 1000LL * 1001 / 2);
}
