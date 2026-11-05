#define STANDALONE

#include <algorithm>
#include <cassert>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <utility>
#include <vector>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/order_statistic_tree.cpp"

template<class Compare>
vector<int> sorted_values(vector<int> a, Compare comp) {
    sort(a.begin(), a.end(), comp);
    return a;
}

template<class Compare>
int brute_order_of_key(const vector<int>& a, int x, Compare comp) {
    int res = 0;
    for (int y : a) {
        if (comp(y, x)) ++res;
    }
    return res;
}

template<class Compare>
void verify_multiset_state(const OrderStatisticTree<int, Compare>& st, const vector<int>& cur, Compare comp) {
    vector<int> ord = sorted_values(cur, comp);
    assert(st.size() == (int)cur.size());
    assert(st.empty() == cur.empty());

    for (int x = -20; x <= 20; ++x) {
        int cnt = count(cur.begin(), cur.end(), x);
        assert(st.count(x) == cnt);
        assert(st.contains(x) == (cnt > 0));
        assert(st.order_of_key(x) == brute_order_of_key(cur, x, comp));
    }
    for (int k = 0; k < (int)ord.size(); ++k) {
        assert(st.find_by_order(k) == ord[k]);
    }
}

void self_check_multiset() {
    mt19937 rng(0);
    for (int tc = 0; tc < 300; ++tc) {
        vector<int> cur(tc % 70);
        for (int& x : cur) x = int(rng() % 31) - 15;
        if (tc % 4 == 0) sort(cur.begin(), cur.end());
        if (tc % 4 == 1) sort(cur.rbegin(), cur.rend());
        if (tc % 4 == 2) fill(cur.begin(), cur.end(), 7);
        OrderStatisticTree<int> asc(cur, rng());
        OrderStatisticTree<int, greater<int>> desc(cur, rng());
        asc.reserve(256);
        desc.reserve(256);
        verify_multiset_state(asc, cur, less<int>());
        verify_multiset_state(desc, cur, greater<int>());

        for (int step = 0; step < 200; ++step) {
            int op = rng() % 3;
            int x = (int)(rng() % 31) - 15;
            if (op <= 1) {
                asc.insert(x);
                desc.insert(x);
                cur.push_back(x);
            } else {
                bool ok1 = asc.erase_one(x);
                bool ok2 = desc.erase_one(x);
                auto it = find(cur.begin(), cur.end(), x);
                bool ok3 = it != cur.end();
                if (ok3) cur.erase(it);
                assert(ok1 == ok2);
                assert(ok2 == ok3);
            }

            verify_multiset_state(asc, cur, less<int>());
            verify_multiset_state(desc, cur, greater<int>());
        }
    }
}

void self_check_pbds_like_unique_keys() {
    mt19937 rng(1);
    using Key = pair<int, int>;
    using PbdsTree = tree<Key, null_type, less<Key>, rb_tree_tag, tree_order_statistics_node_update>;

    OrderStatisticTree<Key> st;
    PbdsTree pbds;
    st.reserve(1000);
    vector<Key> live;

    for (int step = 0; step < 1000; ++step) {
        int op = rng() % 4;
        if (op <= 1 || live.empty()) {
            Key key((int)(rng() % 101) - 50, step);
            st.insert(key);
            pbds.insert(key);
            live.push_back(key);
        } else {
            int idx = rng() % live.size();
            Key key = live[idx];
            assert(st.erase_one(key));
            assert(pbds.erase(key) == 1);
            live.erase(live.begin() + idx);
        }

        assert(st.size() == (int)pbds.size());
        for (int k = 0; k < st.size(); ++k) {
            assert(st.find_by_order(k) == *pbds.find_by_order(k));
        }
        for (int rep = 0; rep < 16; ++rep) {
            Key key((int)(rng() % 111) - 55, (int)(rng() % 1200));
            assert(st.order_of_key(key) == (int)pbds.order_of_key(key));
        }
    }
}

template<bool Reverse>
struct GroupCompare {
    map<pair<int, int>, int> *calls;
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        ++(*calls)[{a.first, b.first}];
        return Reverse ? a.first > b.first : a.first < b.first;
    }
};

template<bool Reverse>
void self_check_comparisons() {
    map<pair<int, int>, int> calls;
    OrderStatisticTree<pair<int, int>, GroupCompare<Reverse>> st(251, {&calls});
    vector<int> values;
    mt19937 rng(251);
    auto check_calls = [&] {
        for (auto [args, count] : calls) assert(count <= (args.first == args.second ? 2 : 1));
    };
    for (int step = 0; step < 2000; ++step) {
        int x = int(rng() % 61) - 30;
        calls.clear();
        if (rng() % 3) {
            st.insert({x, step});
            check_calls();
            values.push_back(x);
        } else {
            auto it = find(values.begin(), values.end(), x);
            bool exists = it != values.end();
            assert(st.erase_one({x, -step - 1}) == exists);
            if (exists) values.erase(it);
        }
        calls.clear();
        assert(st.count({x, -step - 1}) == count(values.begin(), values.end(), x));
        check_calls();
        assert(st.size() == int(values.size()));
        int rank = count_if(values.begin(), values.end(), [&](int y) { return Reverse ? y > x : y < x; });
        assert(st.order_of_key({x, -1}) == rank);
        if (step % 17 == 0) {
            auto sorted = values;
            sort(sorted.begin(), sorted.end());
            if (Reverse) reverse(sorted.begin(), sorted.end());
            for (int i = 0; i < int(sorted.size()); ++i) assert(st.find_by_order(i).first == sorted[i]);
        }
    }
}

template<bool Reverse>
void self_check_bulk_representatives() {
    using Key = pair<int, int>;
    map<Key, int> calls;
    GroupCompare<Reverse> comp{&calls};
    mt19937 rng(333);
    for (int tc = 0; tc < 60; ++tc) {
        vector<Key> values;
        for (int i = 0; i < tc; ++i) values.emplace_back(int(rng() % 9), i);
        if (tc % 3 == 0) stable_sort(values.begin(), values.end(), comp);
        OrderStatisticTree<Key, GroupCompare<Reverse>> bulk(values, tc, comp);
        OrderStatisticTree<Key, GroupCompare<Reverse>> incremental(tc, comp);
        for (const auto& x : values) incremental.insert(x);
        for (int step = 0; step < 150; ++step) {
            assert(bulk.size() == incremental.size());
            for (int i = 0; i < bulk.size(); ++i) {
                assert(bulk.find_by_order(i) == incremental.find_by_order(i));
            }
            Key key(int(rng() % 9), tc + step);
            assert(bulk.count(key) == incremental.count(key));
            assert(bulk.order_of_key(key) == incremental.order_of_key(key));
            if (rng() % 3 == 0) {
                bulk.insert(key);
                incremental.insert(key);
            } else {
                bool a = bulk.erase_one(key);
                bool b = incremental.erase_one(key);
                assert(a == b);
            }
        }
        while (!bulk.empty()) {
            Key key = bulk.find_by_order(0);
            bool a = bulk.erase_one(key);
            bool b = incremental.erase_one(key);
            assert(a && b);
        }
        assert(incremental.empty());
        bulk.insert({10, 20});
        assert(bulk.find_by_order(0) == Key(10, 20));
    }
}

int main() {
    self_check_multiset();
    self_check_pbds_like_unique_keys();
    self_check_comparisons<false>();
    self_check_comparisons<true>();
    self_check_bulk_representatives<false>();
    self_check_bulk_representatives<true>();
}
