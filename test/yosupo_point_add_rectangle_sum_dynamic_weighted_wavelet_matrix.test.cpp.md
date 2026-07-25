---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/dynamic_weighted_wavelet_matrix.cpp
    title: "\u52D5\u7684\u91CD\u307F\u4ED8\u304DWavelet Matrix(Dynamic Weighted Wavelet\
      \ Matrix)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\
    \n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#line 1 \"datastructure/dynamic_weighted_wavelet_matrix.cpp\"\
    \ntemplate <class T, class U>\nstruct DynamicWeightedWaveletMatrix {\n    struct\
    \ CountSum {\n        int count;\n        U sum;\n    };\n\n    int n, lg, blocks,\
    \ slot_count;\n    bool initialized, built;\n    vector<int> mid;\n    vector<int>\
    \ row_offset;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n  \
    \  vector<int> zero_count_fenwick;\n    vector<U> zero_sum_fenwick;\n    vector<int>\
    \ leaf_count_fenwick;\n    vector<U> leaf_sum_fenwick;\n    vector<U> base_sum_fenwick;\n\
    \    vector<int> offset;\n    vector<int> current_slot;\n    vector<int> slot_value_index;\n\
    \    vector<U> weights;\n    vector<T> vals;\n    vector<T> slot_values;\n   \
    \ vector<pair<int, T>> value_candidates;\n\n    DynamicWeightedWaveletMatrix()\n\
    \        : n(0), lg(0), blocks(0), slot_count(0), initialized(false), built(false)\
    \ {}\n\n    explicit DynamicWeightedWaveletMatrix(int n) : DynamicWeightedWaveletMatrix()\
    \ {\n        init(n);\n    }\n\n    DynamicWeightedWaveletMatrix(const vector<T>\
    \ &v, const vector<U> &w)\n        : DynamicWeightedWaveletMatrix((int)v.size())\
    \ {\n        build(v, w);\n    }\n\n    DynamicWeightedWaveletMatrix(const vector<T>\
    \ &v, const vector<U> &w,\n                                 const vector<pair<int,\
    \ T>> &candidates)\n        : DynamicWeightedWaveletMatrix((int)v.size()) {\n\
    \        reserve_candidates((int)candidates.size());\n        for (const auto\
    \ &[k, x] : candidates) add_value_candidate(k, x);\n        build(v, w);\n   \
    \ }\n\n    void init(int size) {\n        assert(size >= 0);\n        n = size;\n\
    \        lg = blocks = slot_count = 0;\n        initialized = true;\n        built\
    \ = false;\n        mid.clear();\n        row_offset.clear();\n        bit.clear();\n\
    \        pref.clear();\n        zero_count_fenwick.clear();\n        zero_sum_fenwick.clear();\n\
    \        leaf_count_fenwick.clear();\n        leaf_sum_fenwick.clear();\n    \
    \    base_sum_fenwick.clear();\n        offset.clear();\n        current_slot.clear();\n\
    \        slot_value_index.clear();\n        weights.clear();\n        vals.clear();\n\
    \        slot_values.clear();\n        value_candidates.clear();\n    }\n\n  \
    \  void reserve_candidates(int capacity) {\n        assert(initialized && !built\
    \ && capacity >= 0);\n        value_candidates.reserve(capacity);\n    }\n\n \
    \   void add_value_candidate(int k, const T &x) {\n        assert(initialized\
    \ && !built);\n        assert(0 <= k && k < n);\n        value_candidates.push_back({k,\
    \ x});\n    }\n\n    static bool equivalent(const T &a, const T &b) {\n      \
    \  return !(a < b) && !(b < a);\n    }\n\n    static inline void rank1_pair(const\
    \ unsigned long long *row, const int *row_pref,\n                            \
    \      int l, int r, int &l1, int &r1) {\n        int l_block = l >> 6;\n    \
    \    l1 = row_pref[l_block];\n        int l_rem = l & 63;\n        if (l_rem)\
    \ l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) - 1));\n\n      \
    \  int r_block = r >> 6;\n        r1 = row_pref[r_block];\n        int r_rem =\
    \ r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block] & ((1ULL\
    \ << r_rem) - 1));\n    }\n\n    int rank1(int d, int k) const {\n        const\
    \ auto *row = bit.data() + d * blocks;\n        const int *row_pref = pref.data()\
    \ + d * (blocks + 1);\n        int block = k >> 6;\n        int res = row_pref[block];\n\
    \        int rem = k & 63;\n        if (rem) res += __builtin_popcountll(row[block]\
    \ & ((1ULL << rem) - 1));\n        return res;\n    }\n\n    template <class V>\n\
    \    static void fenwick_build(vector<V> &fw, int start, int length) {\n     \
    \   for (int i = 1; i <= length; ++i) {\n            int j = i + (i & -i);\n \
    \           if (j <= length) fw[start + j] += fw[start + i];\n        }\n    }\n\
    \n    template <class V>\n    static void fenwick_add(vector<V> &fw, int start,\
    \ int length, int k, const V &x) {\n        for (++k; k <= length; k += k & -k)\
    \ fw[start + k] += x;\n    }\n\n    template <class V>\n    static V fenwick_prefix(const\
    \ vector<V> &fw, int start, int k) {\n        V res = V();\n        for (; k >\
    \ 0; k -= k & -k) res += fw[start + k];\n        return res;\n    }\n\n    template\
    \ <class V>\n    static V fenwick_range(const vector<V> &fw, int start, int l,\
    \ int r) {\n        return fenwick_prefix(fw, start, r) - fenwick_prefix(fw, start,\
    \ l);\n    }\n\n    int find_slot(int k, const T &x) const {\n        auto first\
    \ = slot_values.begin() + offset[k];\n        auto last = slot_values.begin()\
    \ + offset[k + 1];\n        auto it = lower_bound(first, last, x);\n        if\
    \ (it == last || !equivalent(*it, x)) return -1;\n        return (int)(it - slot_values.begin());\n\
    \    }\n\n    void build(const vector<T> &v, const vector<U> &w) {\n        if\
    \ (!initialized) init((int)v.size());\n        assert(!built);\n        assert((int)v.size()\
    \ == n && (int)w.size() == n);\n\n        vector<pair<int, T>> candidates = value_candidates;\n\
    \        candidates.reserve(candidates.size() + n);\n        for (int i = 0; i\
    \ < n; ++i) candidates.push_back({i, v[i]});\n        sort(candidates.begin(),\
    \ candidates.end(), [](const pair<int, T> &a, const pair<int, T> &b) {\n     \
    \       if (a.first != b.first) return a.first < b.first;\n            return\
    \ a.second < b.second;\n        });\n\n        int unique_size = 0;\n        for\
    \ (int i = 0; i < (int)candidates.size(); ++i) {\n            if (unique_size\
    \ == 0 || candidates[unique_size - 1].first != candidates[i].first ||\n      \
    \          !equivalent(candidates[unique_size - 1].second, candidates[i].second))\
    \ {\n                if (unique_size != i) candidates[unique_size] = move(candidates[i]);\n\
    \                ++unique_size;\n            }\n        }\n        candidates.resize(unique_size);\n\
    \n        offset.assign(n + 1, 0);\n        for (const auto &[k, x] : candidates)\
    \ {\n            (void)x;\n            ++offset[k + 1];\n        }\n        for\
    \ (int i = 0; i < n; ++i) offset[i + 1] += offset[i];\n\n        slot_count =\
    \ (int)candidates.size();\n        slot_values.resize(slot_count);\n        for\
    \ (int i = 0; i < slot_count; ++i) slot_values[i] = move(candidates[i].second);\n\
    \n        vals = slot_values;\n        sort(vals.begin(), vals.end());\n     \
    \   int value_count = 0;\n        for (int i = 0; i < (int)vals.size(); ++i) {\n\
    \            if (value_count == 0 || !equivalent(vals[value_count - 1], vals[i]))\
    \ {\n                if (value_count != i) vals[value_count] = move(vals[i]);\n\
    \                ++value_count;\n            }\n        }\n        vals.resize(value_count);\n\
    \n        current_slot.resize(n);\n        weights = w;\n        for (int i =\
    \ 0; i < n; ++i) {\n            current_slot[i] = find_slot(i, v[i]);\n      \
    \      assert(current_slot[i] != -1);\n        }\n\n        if (slot_count ==\
    \ 0) {\n            lg = blocks = 0;\n            mid.clear();\n            row_offset.clear();\n\
    \            bit.clear();\n            pref.clear();\n            zero_count_fenwick.clear();\n\
    \            zero_sum_fenwick.clear();\n            leaf_count_fenwick.assign(1,\
    \ 0);\n            leaf_sum_fenwick.assign(1, U());\n            base_sum_fenwick.assign(1,\
    \ U());\n            slot_value_index.clear();\n            value_candidates.clear();\n\
    \            value_candidates.shrink_to_fit();\n            built = true;\n  \
    \          return;\n        }\n\n        lg = 0;\n        while ((1LL << lg) <\
    \ (int)vals.size()) ++lg;\n        if (lg == 0) lg = 1;\n        blocks = (slot_count\
    \ + 63) >> 6;\n\n        slot_value_index.resize(slot_count);\n        for (int\
    \ i = 0; i < slot_count; ++i) {\n            slot_value_index[i] = (int)(lower_bound(vals.begin(),\
    \ vals.end(), slot_values[i]) - vals.begin());\n        }\n\n        vector<unsigned\
    \ char> active(slot_count, 0);\n        vector<U> active_weight(slot_count, U());\n\
    \        for (int i = 0; i < n; ++i) {\n            active[current_slot[i]] =\
    \ 1;\n            active_weight[current_slot[i]] = w[i];\n        }\n\n      \
    \  mid.assign(lg, 0);\n        bit.assign(lg * blocks, 0);\n        pref.assign(lg\
    \ * (blocks + 1), 0);\n        vector<int> cur(slot_count), nxt(slot_count);\n\
    \        for (int i = 0; i < slot_count; ++i) cur[i] = i;\n\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            auto *row = bit.data()\
    \ + d * blocks;\n            auto *row_pref = pref.data() + d * (blocks + 1);\n\
    \            int zero_count = 0;\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                int b = (slot_value_index[cur[i]] >> shift) & 1;\n \
    \               if (b) row[i >> 6] |= 1ULL << (i & 63);\n                else\
    \ ++zero_count;\n            }\n            mid[d] = zero_count;\n           \
    \ for (int i = 0; i < blocks; ++i) {\n                row_pref[i + 1] = row_pref[i]\
    \ + __builtin_popcountll(row[i]);\n            }\n\n            int zi = 0, oi\
    \ = zero_count;\n            for (int i = 0; i < slot_count; ++i) {\n        \
    \        int id = cur[i];\n                if ((slot_value_index[id] >> shift)\
    \ & 1) nxt[oi++] = id;\n                else nxt[zi++] = id;\n            }\n\
    \            cur.swap(nxt);\n        }\n\n        row_offset.resize(lg);\n   \
    \     size_t fenwick_size = 0;\n        for (int d = 0; d < lg; ++d) {\n     \
    \       row_offset[d] = (int)fenwick_size;\n            fenwick_size += (size_t)mid[d]\
    \ + 1;\n        }\n        zero_count_fenwick.assign(fenwick_size, 0);\n     \
    \   zero_sum_fenwick.assign(fenwick_size, U());\n\n        for (int i = 0; i <\
    \ slot_count; ++i) cur[i] = i;\n        for (int d = 0, shift = lg - 1; d < lg;\
    \ ++d, --shift) {\n            int start = row_offset[d];\n            int zi\
    \ = 0, oi = mid[d];\n            for (int i = 0; i < slot_count; ++i) {\n    \
    \            int id = cur[i];\n                if ((slot_value_index[id] >> shift)\
    \ & 1) {\n                    nxt[oi++] = id;\n                }\n           \
    \     else {\n                    nxt[zi] = id;\n                    if (active[id])\
    \ {\n                        zero_count_fenwick[start + zi + 1] = 1;\n       \
    \                 zero_sum_fenwick[start + zi + 1] = active_weight[id];\n    \
    \                }\n                    ++zi;\n                }\n           \
    \ }\n            fenwick_build(zero_count_fenwick, start, mid[d]);\n         \
    \   fenwick_build(zero_sum_fenwick, start, mid[d]);\n            cur.swap(nxt);\n\
    \        }\n\n        leaf_count_fenwick.assign(slot_count + 1, 0);\n        leaf_sum_fenwick.assign(slot_count\
    \ + 1, U());\n        for (int i = 0; i < slot_count; ++i) {\n            int\
    \ id = cur[i];\n            if (active[id]) {\n                leaf_count_fenwick[i\
    \ + 1] = 1;\n                leaf_sum_fenwick[i + 1] = active_weight[id];\n  \
    \          }\n        }\n        fenwick_build(leaf_count_fenwick, 0, slot_count);\n\
    \        fenwick_build(leaf_sum_fenwick, 0, slot_count);\n\n        base_sum_fenwick.assign(slot_count\
    \ + 1, U());\n        for (int i = 0; i < n; ++i) base_sum_fenwick[current_slot[i]\
    \ + 1] = w[i];\n        fenwick_build(base_sum_fenwick, 0, slot_count);\n\n  \
    \      value_candidates.clear();\n        value_candidates.shrink_to_fit();\n\
    \        built = true;\n    }\n\n    void add_slot(int slot, int count_delta,\
    \ const U &sum_delta) {\n        fenwick_add(base_sum_fenwick, 0, slot_count,\
    \ slot, sum_delta);\n        int p = slot;\n        int xi = slot_value_index[slot];\n\
    \        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n           \
    \ int p1 = rank1(d, p);\n            if ((xi >> shift) & 1) {\n              \
    \  p = mid[d] + p1;\n            }\n            else {\n                p -= p1;\n\
    \                if (count_delta != 0) {\n                    fenwick_add(zero_count_fenwick,\
    \ row_offset[d], mid[d], p, count_delta);\n                }\n               \
    \ fenwick_add(zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);\n      \
    \      }\n        }\n        if (count_delta != 0) {\n            fenwick_add(leaf_count_fenwick,\
    \ 0, slot_count, p, count_delta);\n        }\n        fenwick_add(leaf_sum_fenwick,\
    \ 0, slot_count, p, sum_delta);\n    }\n\n    bool set_value(int k, const T &x)\
    \ {\n        assert(built && 0 <= k && k < n);\n        int next_slot = find_slot(k,\
    \ x);\n        if (next_slot == -1) return false;\n        int old_slot = current_slot[k];\n\
    \        if (old_slot == next_slot) return true;\n        add_slot(old_slot, -1,\
    \ U() - weights[k]);\n        add_slot(next_slot, 1, weights[k]);\n        current_slot[k]\
    \ = next_slot;\n        return true;\n    }\n\n    void set_weight(int k, const\
    \ U &w) {\n        assert(built && 0 <= k && k < n);\n        U delta = w - weights[k];\n\
    \        add_slot(current_slot[k], 0, delta);\n        weights[k] = w;\n    }\n\
    \n    void add_weight(int k, const U &delta) {\n        assert(built && 0 <= k\
    \ && k < n);\n        add_slot(current_slot[k], 0, delta);\n        weights[k]\
    \ += delta;\n    }\n\n    bool set(int k, const T &x, const U &w) {\n        assert(built\
    \ && 0 <= k && k < n);\n        int next_slot = find_slot(k, x);\n        if (next_slot\
    \ == -1) return false;\n        int old_slot = current_slot[k];\n        if (old_slot\
    \ == next_slot) {\n            set_weight(k, w);\n            return true;\n \
    \       }\n        add_slot(old_slot, -1, U() - weights[k]);\n        add_slot(next_slot,\
    \ 1, w);\n        current_slot[k] = next_slot;\n        weights[k] = w;\n    \
    \    return true;\n    }\n\n    const T &get_value(int k) const {\n        assert(built\
    \ && 0 <= k && k < n);\n        return slot_values[current_slot[k]];\n    }\n\n\
    \    const U &get_weight(int k) const {\n        assert(built && 0 <= k && k <\
    \ n);\n        return weights[k];\n    }\n\n    template <bool need_count, bool\
    \ need_sum>\n    CountSum count_sum_less_index_internal(int l, int r, int xi)\
    \ const {\n        assert(built && 0 <= l && l <= r && r <= n);\n        if (xi\
    \ <= 0 || l >= r || n == 0) return {0, U()};\n        if (xi >= (int)vals.size())\
    \ {\n            U sum = U();\n            if constexpr (need_sum) {\n       \
    \         sum = fenwick_range(base_sum_fenwick, 0, offset[l], offset[r]);\n  \
    \          }\n            return {need_count ? r - l : 0, sum};\n        }\n\n\
    \        l = offset[l];\n        r = offset[r];\n        CountSum res{0, U()};\n\
    \        const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n           \
    \ int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n  \
    \          int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n\
    \                if constexpr (need_count) {\n                    res.count +=\
    \ fenwick_range(zero_count_fenwick, row_offset[d], l0, r0);\n                }\n\
    \                if constexpr (need_sum) {\n                    res.sum += fenwick_range(zero_sum_fenwick,\
    \ row_offset[d], l0, r0);\n                }\n                l = mid[d] + l1;\n\
    \                r = mid[d] + r1;\n            }\n            else {\n       \
    \         l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ res;\n    }\n\n    CountSum count_sum_less_index(int l, int r, int xi) const\
    \ {\n        return count_sum_less_index_internal<true, true>(l, r, xi);\n   \
    \ }\n\n    CountSum count_sum_less(int l, int r, const T &x) const {\n       \
    \ int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n \
    \       return count_sum_less_index(l, r, xi);\n    }\n\n    CountSum count_sum_less_equal(int\
    \ l, int r, const T &x) const {\n        int xi = (int)(upper_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_sum_less_index(l, r, xi);\n\
    \    }\n\n    int count_less(int l, int r, const T &x) const {\n        int xi\
    \ = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n        return\
    \ count_sum_less_index_internal<true, false>(l, r, xi).count;\n    }\n\n    int\
    \ count_less_equal(int l, int r, const T &x) const {\n        int xi = (int)(upper_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_sum_less_index_internal<true,\
    \ false>(l, r, xi).count;\n    }\n\n    U sum_less(int l, int r, const T &x) const\
    \ {\n        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_sum_less_index_internal<false, true>(l, r, xi).sum;\n  \
    \  }\n\n    U sum_less_equal(int l, int r, const T &x) const {\n        int xi\
    \ = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n        return\
    \ count_sum_less_index_internal<false, true>(l, r, xi).sum;\n    }\n\n    template\
    \ <bool need_count, bool need_sum>\n    CountSum count_sum_equal_internal(int\
    \ l, int r, int xi) const {\n        assert(built && 0 <= l && l <= r && r <=\
    \ n);\n        if (l >= r || xi < 0 || xi >= (int)vals.size()) return {0, U()};\n\
    \        l = offset[l];\n        r = offset[r];\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n  \
    \          rank1_pair(bit_data, pref_data, l, r, l1, r1);\n            if ((xi\
    \ >> shift) & 1) {\n                l = mid[d] + l1;\n                r = mid[d]\
    \ + r1;\n            }\n            else {\n                l -= l1;\n       \
    \         r -= r1;\n            }\n            bit_data += blocks;\n         \
    \   pref_data += blocks + 1;\n        }\n        int count = 0;\n        U sum\
    \ = U();\n        if constexpr (need_count) count = fenwick_range(leaf_count_fenwick,\
    \ 0, l, r);\n        if constexpr (need_sum) sum = fenwick_range(leaf_sum_fenwick,\
    \ 0, l, r);\n        return {count, sum};\n    }\n\n    CountSum count_sum_equal(int\
    \ l, int r, const T &x) const {\n        assert(built);\n        auto it = lower_bound(vals.begin(),\
    \ vals.end(), x);\n        if (it == vals.end() || !equivalent(*it, x)) return\
    \ {0, U()};\n        return count_sum_equal_internal<true, true>(l, r, (int)(it\
    \ - vals.begin()));\n    }\n\n    int freq(int l, int r, const T &x) const {\n\
    \        assert(built);\n        auto it = lower_bound(vals.begin(), vals.end(),\
    \ x);\n        if (it == vals.end() || !equivalent(*it, x)) return 0;\n      \
    \  return count_sum_equal_internal<true, false>(l, r, (int)(it - vals.begin())).count;\n\
    \    }\n\n    U sum_equal(int l, int r, const T &x) const {\n        assert(built);\n\
    \        auto it = lower_bound(vals.begin(), vals.end(), x);\n        if (it ==\
    \ vals.end() || !equivalent(*it, x)) return U();\n        return count_sum_equal_internal<false,\
    \ true>(l, r, (int)(it - vals.begin())).sum;\n    }\n\n    CountSum range_count_sum(int\
    \ l, int r, const T &lower, const T &upper) const {\n        CountSum hi = count_sum_less(l,\
    \ r, upper);\n        CountSum lo = count_sum_less(l, r, lower);\n        return\
    \ {hi.count - lo.count, hi.sum - lo.sum};\n    }\n\n    int range_freq(int l,\
    \ int r, const T &lower, const T &upper) const {\n        return count_less(l,\
    \ r, upper) - count_less(l, r, lower);\n    }\n\n    U range_sum(int l, int r,\
    \ const T &lower, const T &upper) const {\n        return sum_less(l, r, upper)\
    \ - sum_less(l, r, lower);\n    }\n};\n\n/**\n * @brief \u52D5\u7684\u91CD\u307F\
    \u4ED8\u304DWavelet Matrix(Dynamic Weighted Wavelet Matrix)\n */\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\ntemplate<class T, class = void>\nstruct has_fastio_assign_string : false_type\
    \ {};\n\ntemplate<class T>\nstruct has_fastio_assign_string<T, void_t<decltype(declval<T\
    \ &>().assign(declval<const string &>()))>> : true_type {};\n\ntemplate<class\
    \ T, class = void>\nstruct has_fastio_to_string : false_type {};\n\ntemplate<class\
    \ T>\nstruct has_fastio_to_string<T, void_t<decltype(declval<const T &>().to_string())>>\
    \ : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr\
    \ FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000; ++i) {\n  \
    \          int x = i;\n            for (int j = 3; j >= 0; --j) {\n          \
    \      num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n      \
    \      }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE\
    \ = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n\
    \    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0),\
    \ interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n        int\
    \ len = size - idx;\n        memmove(buf, buf + idx, len);\n        if (interactive)\
    \ {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin)) size = len +\
    \ (int)strlen(buf + len);\n            else size = len;\n        } else {\n  \
    \          size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n    \
    \    }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure()\
    \ {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
    \ {\n        if (idx == size) load();\n    }\n\n    inline char skip() {\n   \
    \     if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            return buf[idx++];\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        if (interactive) {\n            char c = skip();\n          \
    \  bool neg = false;\n            if constexpr (is_signed<T>::value) {\n     \
    \           if (c == '-') {\n                    neg = true;\n               \
    \     ensure_interactive();\n                    c = buf[idx++];\n           \
    \     }\n            }\n            x = 0;\n            while (c >= '0') {\n \
    \               x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class T, typename\
    \ enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>\n\
    \    void read(T &x) {\n        long long v;\n        read(v);\n        x = T(v);\n\
    \    }\n\n    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value\
    \ && has_fastio_assign_string<T>::value, int>::type = 0>\n    void read(T &x)\
    \ {\n        string s;\n        read(s);\n        bool ok = x.assign(s);\n   \
    \     if (!ok) __builtin_trap();\n    }\n\n    template<class Head, class Next,\
    \ class... Tail>\n    void read(Head &head, Next &next, Tail &...tail) {\n   \
    \     read(head);\n        read(next, tail...);\n    }\n\n    template<class T,\
    \ class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void print(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value,\
    \ int>::type = 0>\n    void print(const T &x) {\n        print(x.value());\n \
    \   }\n\n    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value\
    \ && has_fastio_to_string<T>::value, int>::type = 0>\n    void print(const T &x)\
    \ {\n        print(x.to_string());\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ print(const T &a) {\n        bool first = true;\n        for (auto &&x : a)\
    \ {\n            if (!first) pc(' ');\n            first = false;\n          \
    \  print(x);\n        }\n    }\n\n    template<class T>\n    void println(const\
    \ T &x) {\n        print(x);\n        pc('\\n');\n    }\n\n    template<class\
    \ Head, class... Tail>\n    void println(const Head &head, const Tail &...tail)\
    \ {\n        print(head);\n        ((pc(' '), print(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void println() {\n        pc('\\n');\n    }\n};\n\ntemplate<class\
    \ T>\nScanner &operator>>(Scanner &in, T &x) {\n    in.read(x);\n    return in;\n\
    }\n\ntemplate<class T>\nPrinter &operator<<(Printer &out, const T &x) {\n    out.print(x);\n\
    \    return out;\n}\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n\
    \ */\n#line 17 \"test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    struct Point {\n        int x, y;\n        long long weight;\n  \
    \      bool initially_active;\n    };\n    struct Query {\n        int type;\n\
    \        int a, b, c, d;\n        long long weight;\n    };\n\n    vector<Point>\
    \ points;\n    points.reserve(n + q);\n    for (int i = 0; i < n; ++i) {\n   \
    \     int x, y;\n        long long weight;\n        sc.read(x, y, weight);\n \
    \       points.push_back({x, y, weight, true});\n    }\n\n    vector<Query> queries;\n\
    \    queries.reserve(q);\n    for (int i = 0; i < q; ++i) {\n        int type;\n\
    \        sc.read(type);\n        if (type == 0) {\n            int x, y;\n   \
    \         long long weight;\n            sc.read(x, y, weight);\n            int\
    \ id = (int)points.size();\n            points.push_back({x, y, weight, false});\n\
    \            queries.push_back({type, id, 0, 0, 0, weight});\n        }\n    \
    \    else {\n            int l, d, r, u;\n            sc.read(l, d, r, u);\n \
    \           queries.push_back({type, l, d, r, u, 0});\n        }\n    }\n\n  \
    \  int m = (int)points.size();\n    vector<int> ord(m);\n    iota(ord.begin(),\
    \ ord.end(), 0);\n    sort(ord.begin(), ord.end(), [&](int a, int b) {\n     \
    \   if (points[a].x != points[b].x) return points[a].x < points[b].x;\n      \
    \  return a < b;\n    });\n\n    vector<int> position(m), xs(m), values(m);\n\
    \    vector<long long> weights(m, 0);\n    for (int i = 0; i < m; ++i) {\n   \
    \     int id = ord[i];\n        position[id] = i;\n        xs[i] = points[id].x;\n\
    \        values[i] = points[id].y;\n        if (points[id].initially_active) weights[i]\
    \ = points[id].weight;\n    }\n\n    DynamicWeightedWaveletMatrix<int, long long>\
    \ wm(values, weights);\n    for (const Query &query : queries) {\n        if (query.type\
    \ == 0) {\n            wm.add_weight(position[query.a], query.weight);\n     \
    \   }\n        else {\n            int l = (int)(lower_bound(xs.begin(), xs.end(),\
    \ query.a) - xs.begin());\n            int r = (int)(lower_bound(xs.begin(), xs.end(),\
    \ query.c) - xs.begin());\n            pr.println(wm.range_sum(l, r, query.b,\
    \ query.d));\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../datastructure/dynamic_weighted_wavelet_matrix.cpp\"\
    \n#include \"../util/fastio.cpp\"\n\nint main() {\n    Scanner sc;\n    Printer\
    \ pr;\n    int n, q;\n    sc.read(n, q);\n\n    struct Point {\n        int x,\
    \ y;\n        long long weight;\n        bool initially_active;\n    };\n    struct\
    \ Query {\n        int type;\n        int a, b, c, d;\n        long long weight;\n\
    \    };\n\n    vector<Point> points;\n    points.reserve(n + q);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int x, y;\n        long long weight;\n       \
    \ sc.read(x, y, weight);\n        points.push_back({x, y, weight, true});\n  \
    \  }\n\n    vector<Query> queries;\n    queries.reserve(q);\n    for (int i =\
    \ 0; i < q; ++i) {\n        int type;\n        sc.read(type);\n        if (type\
    \ == 0) {\n            int x, y;\n            long long weight;\n            sc.read(x,\
    \ y, weight);\n            int id = (int)points.size();\n            points.push_back({x,\
    \ y, weight, false});\n            queries.push_back({type, id, 0, 0, 0, weight});\n\
    \        }\n        else {\n            int l, d, r, u;\n            sc.read(l,\
    \ d, r, u);\n            queries.push_back({type, l, d, r, u, 0});\n        }\n\
    \    }\n\n    int m = (int)points.size();\n    vector<int> ord(m);\n    iota(ord.begin(),\
    \ ord.end(), 0);\n    sort(ord.begin(), ord.end(), [&](int a, int b) {\n     \
    \   if (points[a].x != points[b].x) return points[a].x < points[b].x;\n      \
    \  return a < b;\n    });\n\n    vector<int> position(m), xs(m), values(m);\n\
    \    vector<long long> weights(m, 0);\n    for (int i = 0; i < m; ++i) {\n   \
    \     int id = ord[i];\n        position[id] = i;\n        xs[i] = points[id].x;\n\
    \        values[i] = points[id].y;\n        if (points[id].initially_active) weights[i]\
    \ = points[id].weight;\n    }\n\n    DynamicWeightedWaveletMatrix<int, long long>\
    \ wm(values, weights);\n    for (const Query &query : queries) {\n        if (query.type\
    \ == 0) {\n            wm.add_weight(position[query.a], query.weight);\n     \
    \   }\n        else {\n            int l = (int)(lower_bound(xs.begin(), xs.end(),\
    \ query.a) - xs.begin());\n            int r = (int)(lower_bound(xs.begin(), xs.end(),\
    \ query.c) - xs.begin());\n            pr.println(wm.range_sum(l, r, query.b,\
    \ query.d));\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/dynamic_weighted_wavelet_matrix.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
  requiredBy: []
  timestamp: '2026-07-25 14:33:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
- /verify/test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp.html
title: test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
---
