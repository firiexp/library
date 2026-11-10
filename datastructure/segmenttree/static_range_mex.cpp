#include "segtree.cpp"

template<class Value>
vector<int> static_range_mex(const vector<Value>& a, const vector<pair<int, int>>& queries) {
    struct MinLastOccurrence {
        using T = int;
        static T f(T a, T b) { return min(a, b); }
        static T e() { return numeric_limits<int>::max(); }
    };
    int n = (int)a.size(), q = (int)queries.size();
    if (q == 0) return {};
    vector<int> order(q), result(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
        return queries[i].second < queries[j].second;
    });
    SegmentTree<MinLastOccurrence> last(n + 1);
    for (int v = 0; v <= n; ++v) last.set(v, -1);
    last.build();
    int right = 0;
    for (int id : order) {
        auto [l, r] = queries[id];
        assert(0 <= l && l <= r && r <= n);
        while (right < r) {
            if (0 <= a[right] && a[right] <= n) last.update((int)a[right], right);
            ++right;
        }
        result[id] = last.search_right(0, [&](int position) { return position >= l; });
    }
    return result;
}

/**
 * @brief 静的区間mex
 */
