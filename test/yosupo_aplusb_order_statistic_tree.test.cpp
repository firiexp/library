#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
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
        OrderStatisticTree<int> asc(rng());
        OrderStatisticTree<int, greater<int>> desc(rng());
        asc.reserve(256);
        desc.reserve(256);
        vector<int> cur;

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

int main() {
    self_check_multiset();
    self_check_pbds_like_unique_keys();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
