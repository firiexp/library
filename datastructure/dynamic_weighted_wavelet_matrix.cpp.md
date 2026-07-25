---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dynamic_weighted_wavelet_matrix.test.cpp
    title: test/yosupo_aplusb_dynamic_weighted_wavelet_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
    title: test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_set_range_frequency.test.cpp
    title: test/yosupo_point_set_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u52D5\u7684\u91CD\u307F\u4ED8\u304DWavelet Matrix(Dynamic Weighted\
      \ Wavelet Matrix)"
    links: []
  bundledCode: "#line 1 \"datastructure/dynamic_weighted_wavelet_matrix.cpp\"\ntemplate\
    \ <class T, class U>\nstruct DynamicWeightedWaveletMatrix {\n    struct CountSum\
    \ {\n        int count;\n        U sum;\n    };\n\n    int n, lg, blocks, slot_count;\n\
    \    bool initialized, built;\n    vector<int> mid;\n    vector<int> row_offset;\n\
    \    vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<int> zero_count_fenwick;\n\
    \    vector<U> zero_sum_fenwick;\n    vector<int> leaf_count_fenwick;\n    vector<U>\
    \ leaf_sum_fenwick;\n    vector<U> base_sum_fenwick;\n    vector<int> offset;\n\
    \    vector<int> current_slot;\n    vector<int> slot_value_index;\n    vector<U>\
    \ weights;\n    vector<T> vals;\n    vector<T> slot_values;\n    vector<pair<int,\
    \ T>> value_candidates;\n\n    DynamicWeightedWaveletMatrix()\n        : n(0),\
    \ lg(0), blocks(0), slot_count(0), initialized(false), built(false) {}\n\n   \
    \ explicit DynamicWeightedWaveletMatrix(int n) : DynamicWeightedWaveletMatrix()\
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
    \u4ED8\u304DWavelet Matrix(Dynamic Weighted Wavelet Matrix)\n */\n"
  code: "template <class T, class U>\nstruct DynamicWeightedWaveletMatrix {\n    struct\
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
    \u4ED8\u304DWavelet Matrix(Dynamic Weighted Wavelet Matrix)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dynamic_weighted_wavelet_matrix.cpp
  requiredBy: []
  timestamp: '2026-07-25 14:33:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_set_range_frequency.test.cpp
  - test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
  - test/yosupo_aplusb_dynamic_weighted_wavelet_matrix.test.cpp
date: 2026-07-25
documentation_of: datastructure/dynamic_weighted_wavelet_matrix.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u52D5\u7684\u91CD\u307F\u4ED8\u304DWavelet Matrix(Dynamic Weighted Wavelet\
  \ Matrix)"
---

## 説明
固定長配列に対して、点ごとの値・重みの変更と、位置区間・値区間に含まれる要素数と重み和を扱う。
値の更新候補を構築前に登録し、候補ごとの有効状態を動的に管理する。

## できること
- `DynamicWeightedWaveletMatrix<T, U> wm(n)`
  長さ `n` の構築前オブジェクトを作る
- `add_value_candidate(k, x)`
  位置 `k` に代入する可能性がある値 `x` を登録する。構築後には呼べない
- `build(v, w)`
  初期値 `v` と初期重み `w` から構築する。初期値は候補へ自動で追加される
- `bool set_value(k, x)`
  位置 `k` の値を `x` に変更する。`x` が位置 `k` の登録候補になければ変更せず `false`
- `set_weight(k, w)` / `add_weight(k, delta)`
  位置 `k` の重みを変更、または加算する
- `bool set(k, x, w)`
  位置 `k` の値と重みを同時に変更する。`x` が登録候補になければ変更せず `false`
- `get_value(k)` / `get_weight(k)`
  位置 `k` の現在の値または重みを返す
- `count_sum_less(l, r, x)` / `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満または以下の要素数と重み和を返す
- `count_less(l, r, x)` / `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数または重み和を返す
- `freq(l, r, x)` / `sum_equal(l, r, x)`
  区間 $[l, r)$ にある値 `x` の個数または重み和を返す
- `range_count_sum(l, r, lower, upper)`
  区間 $[l, r)$ かつ $lower \leq a_i < upper$ にある要素数と重み和を返す
- `range_freq(l, r, lower, upper)` / `range_sum(l, r, lower, upper)`
  同じ範囲にある要素数または重み和を返す

## 使い方
入力を先読みし、値変更で現れる `(位置, 値)` を `add_value_candidate` で登録してから `build` する。
クエリにだけ現れる境界値は登録不要。

```cpp
DynamicWeightedWaveletMatrix<int, long long> wm(n);
for (auto [k, x] : updates) wm.add_value_candidate(k, x);
wm.build(values, weights);
```

## 実装上の補足
- 各位置の候補を連続したスロットへ展開し、各位置につき一つのスロットだけを有効にする
- 値変更は旧スロットの無効化と新スロットの有効化で処理する
- $M$ を登録後の候補スロット数、$\sigma$ を候補値の種類数とする
- 構築は $O(M \log M + M \log \sigma)$
- 更新と `less`・値区間クエリは $O(\log \sigma \log M)$
- `freq` と `sum_equal` は $O(\log \sigma + \log M)$
- メモリ使用量は $O(M \log \sigma)$
- `U` は `U()` を零元として加算と減算ができる型を使う
