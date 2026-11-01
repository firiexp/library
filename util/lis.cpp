#include "../datastructure/segmenttree/binaryindexedtree.cpp"

template<class T>
int lis_length(const vector<T>& a, bool strict = true) {
    vector<T> tails;
    for (const T& value : a) {
        auto it = strict ? lower_bound(tails.begin(), tails.end(), value)
                         : upper_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return (int)tails.size();
}

template<class T>
vector<int> lis_indices(const vector<T> &a, bool strict = true) {
    vector<int> tails, previous(a.size(), -1);
    for (int i = 0; i < (int)a.size(); ++i) {
        int l = 0, r = tails.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (strict ? a[tails[m]] < a[i] : !(a[i] < a[tails[m]])) l = m + 1;
            else r = m;
        }
        if (l) previous[i] = tails[l - 1];
        if (l == (int)tails.size()) tails.push_back(i);
        else tails[l] = i;
    }
    vector<int> result(tails.size());
    int v = tails.empty() ? -1 : tails.back();
    for (int i = (int)result.size() - 1; i >= 0; --i) {
        result[i] = v;
        v = previous[v];
    }
    return result;
}

template<class Count, class T>
pair<int, Count> lis_count(const vector<T> &a, bool strict = true) {
    struct State {
        int length;
        Count count;
        State(int length = 0, Count count = Count(0)): length(length), count(count) {}
        void operator+=(const State &other) {
            if (length < other.length) *this = other;
            else if (length == other.length) count += other.count;
        }
    };
    int n = a.size();
    if (n == 0) return {0, Count(1)};
    vector<int> order(n), rank(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return a[i] < a[j]; });
    int kinds = 1;
    for (int i = 0; i < n; ++i) {
        if (i && a[order[i - 1]] < a[order[i]]) ++kinds;
        rank[order[i]] = kinds - 1;
    }
    BIT<State> bit(kinds);
    for (int k : rank) {
        auto best = bit.sum(k + !strict);
        if (best.length == 0) best.count = Count(1);
        ++best.length;
        bit.add(k, best);
    }
    auto best = bit.sum(kinds);
    return {best.length, best.count};
}

/**
 * @brief 最長増加部分列
 */
