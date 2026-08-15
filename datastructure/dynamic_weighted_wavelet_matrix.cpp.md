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
    \ {\n        int count;\n        U sum;\n    };\n\n    static constexpr bool use_fast_value_search\
    \ =\n            is_integral<T>::value && !is_same<T, bool>::value &&\n      \
    \      sizeof(T) <= 8;\n\n    class Cursor {\n        friend struct DynamicWeightedWaveletMatrix;\n\
    \n        const DynamicWeightedWaveletMatrix *owner_;\n        int depth_, l_,\
    \ r_, value_index_;\n        CountSum all_;\n\n        Cursor(const DynamicWeightedWaveletMatrix\
    \ *owner, int depth,\n               int l, int r, int value_index, CountSum all)\n\
    \            : owner_(owner), depth_(depth), l_(l), r_(r),\n              value_index_(value_index),\
    \ all_(all) {}\n\n    public:\n        bool is_leaf() const {\n            return\
    \ depth_ == owner_->lg;\n        }\n\n        bool empty() const {\n         \
    \   return all_.count == 0;\n        }\n\n        int count() const {\n      \
    \      return all_.count;\n        }\n\n        const U &sum() const {\n     \
    \       return all_.sum;\n        }\n\n        const CountSum &info() const {\n\
    \            return all_;\n        }\n\n        const T &value() const {\n   \
    \         assert(is_leaf() && !empty());\n            assert(0 <= value_index_\
    \ && value_index_ < (int)owner_->vals.size());\n            return owner_->vals[value_index_];\n\
    \        }\n    };\n\n    struct Children {\n        Cursor low;\n        Cursor\
    \ high;\n    };\n\n    int n, lg, blocks, slot_count;\n    bool initialized, built;\n\
    \    bool fixed_values;\n    vector<int> mid;\n    vector<int> row_offset;\n \
    \   vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<int> zero_count_fenwick;\n\
    \    vector<U> zero_sum_fenwick;\n    vector<int> leaf_count_fenwick;\n    vector<U>\
    \ leaf_sum_fenwick;\n    vector<U> base_sum_fenwick;\n    vector<int> offset;\n\
    \    vector<int> current_slot;\n    vector<int> slot_value_index;\n    vector<int>\
    \ update_offset;\n    vector<int> update_position;\n    vector<int> leaf_position;\n\
    \    vector<U> weights;\n    vector<T> vals;\n    vector<T> value_search_tree;\n\
    \    vector<int> value_search_rank;\n    vector<T> slot_values;\n    vector<pair<int,\
    \ T>> value_candidates;\n\n    DynamicWeightedWaveletMatrix()\n        : n(0),\
    \ lg(0), blocks(0), slot_count(0), initialized(false), built(false),\n       \
    \   fixed_values(false) {}\n\n    explicit DynamicWeightedWaveletMatrix(int n)\
    \ : DynamicWeightedWaveletMatrix() {\n        init(n);\n    }\n\n    DynamicWeightedWaveletMatrix(const\
    \ vector<T> &v, const vector<U> &w)\n        : DynamicWeightedWaveletMatrix((int)v.size())\
    \ {\n        build(v, w);\n    }\n\n    DynamicWeightedWaveletMatrix(const vector<T>\
    \ &v, const vector<U> &w,\n                                 const vector<pair<int,\
    \ T>> &candidates)\n        : DynamicWeightedWaveletMatrix((int)v.size()) {\n\
    \        reserve_candidates((int)candidates.size());\n        for (const auto\
    \ &[k, x] : candidates) add_value_candidate(k, x);\n        build(v, w);\n   \
    \ }\n\n    void init(int size) {\n        assert(size >= 0);\n        n = size;\n\
    \        lg = blocks = slot_count = 0;\n        initialized = true;\n        built\
    \ = false;\n        fixed_values = false;\n        mid.clear();\n        row_offset.clear();\n\
    \        bit.clear();\n        pref.clear();\n        zero_count_fenwick.clear();\n\
    \        zero_sum_fenwick.clear();\n        leaf_count_fenwick.clear();\n    \
    \    leaf_sum_fenwick.clear();\n        base_sum_fenwick.clear();\n        offset.clear();\n\
    \        current_slot.clear();\n        slot_value_index.clear();\n        update_offset.clear();\n\
    \        update_position.clear();\n        leaf_position.clear();\n        weights.clear();\n\
    \        vals.clear();\n        value_search_tree.clear();\n        value_search_rank.clear();\n\
    \        slot_values.clear();\n        value_candidates.clear();\n    }\n\n  \
    \  void reserve_candidates(int capacity) {\n        assert(initialized && !built\
    \ && capacity >= 0);\n        value_candidates.reserve(capacity);\n    }\n\n \
    \   void add_value_candidate(int k, const T &x) {\n        assert(initialized\
    \ && !built);\n        assert(0 <= k && k < n);\n        value_candidates.push_back({k,\
    \ x});\n    }\n\n    static bool equivalent(const T &a, const T &b) {\n      \
    \  return !(a < b) && !(b < a);\n    }\n\n    int lower_bound_value(const T &x)\
    \ const {\n        if constexpr (use_fast_value_search) {\n            unsigned\
    \ k = 1;\n            unsigned size = (unsigned)vals.size();\n            constexpr\
    \ unsigned prefetch_scale = sizeof(T) <= 4 ? 16 : 8;\n            while (k <=\
    \ size) {\n                if (k <= size / prefetch_scale) {\n               \
    \     __builtin_prefetch(\n                            value_search_tree.data()\
    \ + k * prefetch_scale);\n                }\n                k = (k << 1) + (value_search_tree[k]\
    \ < x);\n            }\n            unsigned inverted = ~k;\n            if (inverted\
    \ == 0) return (int)size;\n            k >>= __builtin_ctz(inverted) + 1;\n  \
    \          return k == 0 ? (int)size : value_search_rank[k];\n        }\n    \
    \    return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \    }\n\n    int upper_bound_value(const T &x) const {\n        if constexpr\
    \ (use_fast_value_search) {\n            unsigned k = 1;\n            unsigned\
    \ size = (unsigned)vals.size();\n            constexpr unsigned prefetch_scale\
    \ = sizeof(T) <= 4 ? 16 : 8;\n            while (k <= size) {\n              \
    \  if (k <= size / prefetch_scale) {\n                    __builtin_prefetch(\n\
    \                            value_search_tree.data() + k * prefetch_scale);\n\
    \                }\n                k = (k << 1) + !(x < value_search_tree[k]);\n\
    \            }\n            unsigned inverted = ~k;\n            if (inverted\
    \ == 0) return (int)size;\n            k >>= __builtin_ctz(inverted) + 1;\n  \
    \          return k == 0 ? (int)size : value_search_rank[k];\n        }\n    \
    \    return (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \    }\n\n    void build_value_search_tree() {\n        if constexpr (use_fast_value_search)\
    \ {\n            int size = (int)vals.size();\n            value_search_tree.resize(size\
    \ + 1);\n            value_search_rank.resize(size + 1);\n            int rank\
    \ = 0;\n            auto visit = [&](auto &&self, unsigned k) -> void {\n    \
    \            if (k > (unsigned)size) return;\n                self(self, k <<\
    \ 1);\n                value_search_tree[k] = vals[rank];\n                value_search_rank[k]\
    \ = rank++;\n                self(self, k << 1 | 1);\n            };\n       \
    \     visit(visit, 1);\n        }\n    }\n\n    template <class X>\n    static\
    \ auto encode_key(X x) -> typename make_unsigned<X>::type {\n        using Key\
    \ = typename make_unsigned<X>::type;\n        Key key = static_cast<Key>(x);\n\
    \        if constexpr (is_signed<X>::value) {\n            key ^= Key(1) << (sizeof(X)\
    \ * 8 - 1);\n        }\n        return key;\n    }\n\n    static inline int popcount(unsigned\
    \ long long x) {\n#if defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\")) {\n            unsigned long long result;\n            __asm__(\"popcnt{q\
    \ %1, %0| %0, %1}\"\n                    : \"=r\"(result) : \"r\"(x) : \"cc\"\
    );\n            return (int)result;\n        }\n#endif\n        return __builtin_popcountll(x);\n\
    \    }\n\n    static inline void popcount_pair(unsigned long long x,\n       \
    \                              unsigned long long y,\n                       \
    \              int &x_count, int &y_count) {\n#if defined(__x86_64__)\n      \
    \  if (__builtin_cpu_supports(\"popcnt\")) {\n            unsigned long long x_result,\
    \ y_result;\n            __asm__(\"popcnt{q %1, %0| %0, %1}\"\n              \
    \      : \"=r\"(x_result) : \"r\"(x) : \"cc\");\n            __asm__(\"popcnt{q\
    \ %1, %0| %0, %1}\"\n                    : \"=r\"(y_result) : \"r\"(y) : \"cc\"\
    );\n            x_count = (int)x_result;\n            y_count = (int)y_result;\n\
    \            return;\n        }\n#endif\n        x_count = __builtin_popcountll(x);\n\
    \        y_count = __builtin_popcountll(y);\n    }\n\n    static inline void rank1_pair(const\
    \ unsigned long long *row,\n                                  const int *row_pref,\n\
    \                                  int l, int r, int &l1, int &r1) {\n       \
    \ int l_block = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem =\
    \ l & 63;\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n  \
    \      int r_rem = r & 63;\n        if (l_rem && r_rem) {\n            int l_count,\
    \ r_count;\n            popcount_pair(\n                    row[l_block] & ((1ULL\
    \ << l_rem) - 1),\n                    row[r_block] & ((1ULL << r_rem) - 1),\n\
    \                    l_count, r_count);\n            l1 += l_count;\n        \
    \    r1 += r_count;\n            return;\n        }\n        if (l_rem) l1 +=\
    \ popcount(row[l_block] & ((1ULL << l_rem) - 1));\n        if (r_rem) r1 += popcount(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class V>\n    static void\
    \ fenwick_build(vector<V> &fw, int start, int length) {\n        for (int i =\
    \ 1; i <= length; ++i) {\n            int j = i + (i & -i);\n            if (j\
    \ <= length) fw[start + j] += fw[start + i];\n        }\n    }\n\n    template\
    \ <class V>\n    static void fenwick_add(vector<V> &fw, int start, int length,\
    \ int k, const V &x) {\n        for (++k; k <= length; k += k & -k) fw[start +\
    \ k] += x;\n    }\n\n    template <class V>\n    static V fenwick_prefix(const\
    \ vector<V> &fw, int start, int k) {\n        V res = V();\n        for (; k >\
    \ 0; k -= k & -k) res += fw[start + k];\n        return res;\n    }\n\n    template\
    \ <class V>\n    static V fenwick_range(const vector<V> &fw, int start, int l,\
    \ int r) {\n        return fenwick_prefix(fw, start, r) - fenwick_prefix(fw, start,\
    \ l);\n    }\n\n    static CountSum fenwick_range_count_sum(\n            const\
    \ vector<int> &count_fw, const vector<U> &sum_fw,\n            int start, int\
    \ l, int r) {\n        CountSum res{0, U()};\n        for (; r > 0; r -= r & -r)\
    \ {\n            res.count += count_fw[start + r];\n            res.sum += sum_fw[start\
    \ + r];\n        }\n        for (; l > 0; l -= l & -l) {\n            res.count\
    \ -= count_fw[start + l];\n            res.sum -= sum_fw[start + l];\n       \
    \ }\n        return res;\n    }\n\n    static void fenwick_add_count_sum(\n  \
    \          vector<int> &count_fw, vector<U> &sum_fw,\n            int start, int\
    \ length, int k, int count_delta, const U &sum_delta) {\n        for (++k; k <=\
    \ length; k += k & -k) {\n            count_fw[start + k] += count_delta;\n  \
    \          sum_fw[start + k] += sum_delta;\n        }\n    }\n\n    static int\
    \ fenwick_lower_bound(const vector<int> &fw, int start, int length, int target)\
    \ {\n        assert(target > 0);\n        int k = 0;\n        int step = 1;\n\
    \        while ((step << 1) <= length) step <<= 1;\n        for (; step > 0; step\
    \ >>= 1) {\n            int next = k + step;\n            if (next <= length &&\
    \ fw[start + next] < target) {\n                k = next;\n                target\
    \ -= fw[start + next];\n            }\n        }\n        return k + 1;\n    }\n\
    \n    int find_slot(int k, const T &x) const {\n        auto first = slot_values.begin()\
    \ + offset[k];\n        auto last = slot_values.begin() + offset[k + 1];\n   \
    \     auto it = lower_bound(first, last, x);\n        if (it == last || !equivalent(*it,\
    \ x)) return -1;\n        return (int)(it - slot_values.begin());\n    }\n\n \
    \   void build(const vector<T> &v, const vector<U> &w) {\n        if (!initialized)\
    \ init((int)v.size());\n        assert(!built);\n        assert((int)v.size()\
    \ == n && (int)w.size() == n);\n\n        vector<int> raw_offset(n + 1, 0);\n\
    \        for (const auto &[k, x] : value_candidates) {\n            (void)x;\n\
    \            ++raw_offset[k + 1];\n        }\n        for (int i = 0; i < n; ++i)\
    \ ++raw_offset[i + 1];\n        for (int i = 0; i < n; ++i) raw_offset[i + 1]\
    \ += raw_offset[i];\n\n        vector<T> raw_values(raw_offset[n]);\n        vector<int>\
    \ write_position = raw_offset;\n        for (const auto &[k, x] : value_candidates)\
    \ {\n            raw_values[write_position[k]++] = x;\n        }\n        for\
    \ (int i = 0; i < n; ++i) {\n            raw_values[write_position[i]++] = v[i];\n\
    \        }\n\n        offset.assign(n + 1, 0);\n        slot_values.clear();\n\
    \        slot_values.reserve(raw_values.size());\n        for (int k = 0; k <\
    \ n; ++k) {\n            auto first = raw_values.begin() + raw_offset[k];\n  \
    \          auto last = raw_values.begin() + raw_offset[k + 1];\n            sort(first,\
    \ last);\n            for (auto it = first; it != last; ++it) {\n            \
    \    if ((int)slot_values.size() == offset[k] ||\n                    !equivalent(slot_values.back(),\
    \ *it)) {\n                    slot_values.push_back(move(*it));\n           \
    \     }\n            }\n            offset[k + 1] = (int)slot_values.size();\n\
    \        }\n        slot_count = (int)slot_values.size();\n\n        slot_value_index.resize(slot_count);\n\
    \        if constexpr (is_integral<T>::value && !is_same<T, bool>::value &&\n\
    \                      sizeof(T) <= 8) {\n            using Key = typename make_unsigned<T>::type;\n\
    \            vector<Key> keys(slot_count);\n            vector<int> ord(slot_count),\
    \ buf(slot_count);\n            for (int i = 0; i < slot_count; ++i) {\n     \
    \           keys[i] = encode_key(slot_values[i]);\n                ord[i] = i;\n\
    \            }\n\n            constexpr int radix_bits = 16;\n            constexpr\
    \ int bucket_count = 1 << radix_bits;\n            constexpr int mask = bucket_count\
    \ - 1;\n            int passes = (int)(sizeof(Key) * 8 + radix_bits - 1) / radix_bits;\n\
    \            vector<int> count(bucket_count), position(bucket_count);\n      \
    \      for (int pass = 0; pass < passes; ++pass) {\n                fill(count.begin(),\
    \ count.end(), 0);\n                int shift = pass * radix_bits;\n         \
    \       for (int id : ord) ++count[(keys[id] >> shift) & mask];\n            \
    \    position[0] = 0;\n                for (int i = 0; i + 1 < bucket_count; ++i)\
    \ {\n                    position[i + 1] = position[i] + count[i];\n         \
    \       }\n                for (int id : ord) {\n                    buf[position[(keys[id]\
    \ >> shift) & mask]++] = id;\n                }\n                ord.swap(buf);\n\
    \            }\n\n            vals.clear();\n            vals.reserve(slot_count);\n\
    \            bool has_previous = false;\n            Key previous = 0;\n     \
    \       for (int id : ord) {\n                if (!has_previous || keys[id] !=\
    \ previous) {\n                    vals.push_back(slot_values[id]);\n        \
    \            previous = keys[id];\n                    has_previous = true;\n\
    \                }\n                slot_value_index[id] = (int)vals.size() -\
    \ 1;\n            }\n        }\n        else {\n            vals = slot_values;\n\
    \            sort(vals.begin(), vals.end());\n            int value_count = 0;\n\
    \            for (int i = 0; i < (int)vals.size(); ++i) {\n                if\
    \ (value_count == 0 ||\n                    !equivalent(vals[value_count - 1],\
    \ vals[i])) {\n                    if (value_count != i) vals[value_count] = move(vals[i]);\n\
    \                    ++value_count;\n                }\n            }\n      \
    \      vals.resize(value_count);\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                slot_value_index[i] = (int)(lower_bound(\n         \
    \               vals.begin(), vals.end(), slot_values[i]) - vals.begin());\n \
    \           }\n        }\n        build_value_search_tree();\n        fixed_values\
    \ = slot_count == n;\n        current_slot.resize(n);\n        weights = w;\n\
    \        for (int i = 0; i < n; ++i) {\n            current_slot[i] = find_slot(i,\
    \ v[i]);\n            assert(current_slot[i] != -1);\n        }\n\n        if\
    \ (slot_count == 0) {\n            lg = blocks = 0;\n            mid.clear();\n\
    \            row_offset.clear();\n            bit.clear();\n            pref.clear();\n\
    \            zero_count_fenwick.clear();\n            zero_sum_fenwick.clear();\n\
    \            leaf_count_fenwick.assign(1, 0);\n            leaf_sum_fenwick.assign(1,\
    \ U());\n            base_sum_fenwick.assign(1, U());\n            slot_value_index.clear();\n\
    \            update_offset.clear();\n            update_position.clear();\n  \
    \          leaf_position.clear();\n            value_candidates.clear();\n   \
    \         value_candidates.shrink_to_fit();\n            built = true;\n     \
    \       return;\n        }\n\n        lg = 0;\n        while ((1LL << lg) < (int)vals.size())\
    \ ++lg;\n        if (lg == 0) lg = 1;\n        blocks = (slot_count + 63) >> 6;\n\
    \n        vector<unsigned char> active(slot_count, 0);\n        vector<U> active_weight(slot_count,\
    \ U());\n        for (int i = 0; i < n; ++i) {\n            active[current_slot[i]]\
    \ = 1;\n            active_weight[current_slot[i]] = w[i];\n        }\n\n    \
    \    mid.assign(lg, 0);\n        bit.assign(lg * blocks, 0);\n        pref.assign(lg\
    \ * (blocks + 1), 0);\n        vector<int> cur(slot_count), nxt(slot_count);\n\
    \        for (int i = 0; i < slot_count; ++i) cur[i] = i;\n\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            auto *row = bit.data()\
    \ + d * blocks;\n            auto *row_pref = pref.data() + d * (blocks + 1);\n\
    \            int zero_count = 0;\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                int b = (slot_value_index[cur[i]] >> shift) & 1;\n \
    \               if (b) row[i >> 6] |= 1ULL << (i & 63);\n                else\
    \ ++zero_count;\n            }\n            mid[d] = zero_count;\n           \
    \ for (int i = 0; i < blocks; ++i) {\n                row_pref[i + 1] = row_pref[i]\
    \ + popcount(row[i]);\n            }\n\n            int zi = 0, oi = zero_count;\n\
    \            for (int i = 0; i < slot_count; ++i) {\n                int id =\
    \ cur[i];\n                if ((slot_value_index[id] >> shift) & 1) nxt[oi++]\
    \ = id;\n                else nxt[zi++] = id;\n            }\n            cur.swap(nxt);\n\
    \        }\n\n        row_offset.resize(lg);\n        size_t fenwick_size = 0;\n\
    \        for (int d = 0; d < lg; ++d) {\n            row_offset[d] = (int)fenwick_size;\n\
    \            fenwick_size += (size_t)mid[d] + 1;\n        }\n        if (fixed_values)\
    \ zero_count_fenwick.clear();\n        else zero_count_fenwick.assign(fenwick_size,\
    \ 0);\n        zero_sum_fenwick.assign(fenwick_size, U());\n        update_offset.resize(slot_count\
    \ + 1);\n        for (int i = 0; i < slot_count; ++i) {\n            update_offset[i\
    \ + 1] = update_offset[i] +\n                    lg - __builtin_popcount((unsigned)slot_value_index[i]);\n\
    \        }\n        update_position.resize(update_offset.back());\n        vector<int>\
    \ update_next = update_offset;\n        leaf_position.resize(slot_count);\n\n\
    \        for (int i = 0; i < slot_count; ++i) cur[i] = i;\n        for (int d\
    \ = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int start = row_offset[d];\n\
    \            int zi = 0, oi = mid[d];\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                int id = cur[i];\n                if ((slot_value_index[id]\
    \ >> shift) & 1) {\n                    nxt[oi++] = id;\n                }\n \
    \               else {\n                    nxt[zi] = id;\n                  \
    \  update_position[update_next[id]++] = zi;\n                    if (active[id])\
    \ {\n                        if (!fixed_values) zero_count_fenwick[start + zi\
    \ + 1] = 1;\n                        zero_sum_fenwick[start + zi + 1] = active_weight[id];\n\
    \                    }\n                    ++zi;\n                }\n       \
    \     }\n            if (!fixed_values) fenwick_build(zero_count_fenwick, start,\
    \ mid[d]);\n            fenwick_build(zero_sum_fenwick, start, mid[d]);\n    \
    \        cur.swap(nxt);\n        }\n\n        if (fixed_values) leaf_count_fenwick.clear();\n\
    \        else leaf_count_fenwick.assign(slot_count + 1, 0);\n        leaf_sum_fenwick.assign(slot_count\
    \ + 1, U());\n        for (int i = 0; i < slot_count; ++i) {\n            int\
    \ id = cur[i];\n            leaf_position[id] = i;\n            if (active[id])\
    \ {\n                if (!fixed_values) leaf_count_fenwick[i + 1] = 1;\n     \
    \           leaf_sum_fenwick[i + 1] = active_weight[id];\n            }\n    \
    \    }\n        if (!fixed_values) fenwick_build(leaf_count_fenwick, 0, slot_count);\n\
    \        fenwick_build(leaf_sum_fenwick, 0, slot_count);\n\n        base_sum_fenwick.assign(n\
    \ + 1, U());\n        for (int i = 0; i < n; ++i) base_sum_fenwick[i + 1] = w[i];\n\
    \        fenwick_build(base_sum_fenwick, 0, n);\n\n        value_candidates.clear();\n\
    \        value_candidates.shrink_to_fit();\n        built = true;\n    }\n\n \
    \   void add_slot(int slot, int count_delta, const U &sum_delta) {\n        const\
    \ int *positions = update_position.data() + update_offset[slot];\n        int\
    \ xi = slot_value_index[slot];\n        unsigned zero_mask = (~(unsigned)xi) &\
    \ ((1U << lg) - 1);\n        while (zero_mask) {\n            int shift = 31 -\
    \ __builtin_clz(zero_mask);\n            int d = lg - 1 - shift;\n           \
    \ int p = *positions++;\n            if (count_delta != 0) {\n               \
    \ fenwick_add_count_sum(\n                        zero_count_fenwick, zero_sum_fenwick,\n\
    \                        row_offset[d], mid[d], p, count_delta, sum_delta);\n\
    \            }\n            else {\n                fenwick_add(\n           \
    \             zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);\n      \
    \      }\n            zero_mask ^= 1U << shift;\n        }\n        int p = leaf_position[slot];\n\
    \        if (count_delta != 0) {\n            fenwick_add_count_sum(\n       \
    \             leaf_count_fenwick, leaf_sum_fenwick,\n                    0, slot_count,\
    \ p, count_delta, sum_delta);\n        }\n        else {\n            fenwick_add(leaf_sum_fenwick,\
    \ 0, slot_count, p, sum_delta);\n        }\n    }\n\n    void add_slot_sum(int\
    \ slot, const U &sum_delta) {\n        const int *positions = update_position.data()\
    \ + update_offset[slot];\n        int xi = slot_value_index[slot];\n        unsigned\
    \ zero_mask = (~(unsigned)xi) & ((1U << lg) - 1);\n        while (zero_mask) {\n\
    \            int shift = 31 - __builtin_clz(zero_mask);\n            int d = lg\
    \ - 1 - shift;\n            int p = *positions++;\n            fenwick_add(\n\
    \                    zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);\n\
    \            zero_mask ^= 1U << shift;\n        }\n        int p = leaf_position[slot];\n\
    \        fenwick_add(leaf_sum_fenwick, 0, slot_count, p, sum_delta);\n    }\n\n\
    \    bool set_value(int k, const T &x) {\n        assert(built && 0 <= k && k\
    \ < n);\n        int next_slot = find_slot(k, x);\n        if (next_slot == -1)\
    \ return false;\n        int old_slot = current_slot[k];\n        if (old_slot\
    \ == next_slot) return true;\n        add_slot(old_slot, -1, U() - weights[k]);\n\
    \        add_slot(next_slot, 1, weights[k]);\n        current_slot[k] = next_slot;\n\
    \        return true;\n    }\n\n    void set_weight(int k, const U &w) {\n   \
    \     assert(built && 0 <= k && k < n);\n        U delta = w - weights[k];\n \
    \       fenwick_add(base_sum_fenwick, 0, n, k, delta);\n        add_slot_sum(current_slot[k],\
    \ delta);\n        weights[k] = w;\n    }\n\n    void add_weight(int k, const\
    \ U &delta) {\n        assert(built && 0 <= k && k < n);\n        fenwick_add(base_sum_fenwick,\
    \ 0, n, k, delta);\n        add_slot_sum(current_slot[k], delta);\n        weights[k]\
    \ += delta;\n    }\n\n    bool set(int k, const T &x, const U &w) {\n        assert(built\
    \ && 0 <= k && k < n);\n        int next_slot = find_slot(k, x);\n        if (next_slot\
    \ == -1) return false;\n        int old_slot = current_slot[k];\n        if (old_slot\
    \ == next_slot) {\n            set_weight(k, w);\n            return true;\n \
    \       }\n        fenwick_add(base_sum_fenwick, 0, n, k, w - weights[k]);\n \
    \       add_slot(old_slot, -1, U() - weights[k]);\n        add_slot(next_slot,\
    \ 1, w);\n        current_slot[k] = next_slot;\n        weights[k] = w;\n    \
    \    return true;\n    }\n\n    const T &get_value(int k) const {\n        assert(built\
    \ && 0 <= k && k < n);\n        return slot_values[current_slot[k]];\n    }\n\n\
    \    const U &get_weight(int k) const {\n        assert(built && 0 <= k && k <\
    \ n);\n        return weights[k];\n    }\n\n    template <bool need_count, bool\
    \ need_sum>\n    CountSum count_sum_less_index_internal(int l, int r, int xi)\
    \ const {\n        assert(built && 0 <= l && l <= r && r <= n);\n        if (xi\
    \ <= 0 || l >= r || n == 0) return {0, U()};\n        if (xi >= (int)vals.size())\
    \ {\n            U sum = U();\n            if constexpr (need_sum) {\n       \
    \         sum = fenwick_range(base_sum_fenwick, 0, l, r);\n            }\n   \
    \         return {need_count ? r - l : 0, sum};\n        }\n\n        l = offset[l];\n\
    \        r = offset[r];\n        CountSum res{0, U()};\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n  \
    \          rank1_pair(bit_data, pref_data, l, r, l1, r1);\n            int l0\
    \ = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n             \
    \   if (fixed_values) {\n                    if constexpr (need_count) res.count\
    \ += r0 - l0;\n                    if constexpr (need_sum) {\n               \
    \         res.sum += fenwick_range(\n                                zero_sum_fenwick,\
    \ row_offset[d], l0, r0);\n                    }\n                }\n        \
    \        else {\n                    if constexpr (need_count && need_sum) {\n\
    \                        CountSum part = fenwick_range_count_sum(\n          \
    \                      zero_count_fenwick, zero_sum_fenwick,\n               \
    \                 row_offset[d], l0, r0);\n                        res.count +=\
    \ part.count;\n                        res.sum += part.sum;\n                \
    \    }\n                    else {\n                        if constexpr (need_count)\
    \ {\n                            res.count += fenwick_range(\n               \
    \                     zero_count_fenwick, row_offset[d], l0, r0);\n          \
    \              }\n                        if constexpr (need_sum) {\n        \
    \                    res.sum += fenwick_range(\n                             \
    \       zero_sum_fenwick, row_offset[d], l0, r0);\n                        }\n\
    \                    }\n                }\n                l = mid[d] + l1;\n\
    \                r = mid[d] + r1;\n            }\n            else {\n       \
    \         l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ res;\n    }\n\n    CountSum count_sum_less_index(int l, int r, int xi) const\
    \ {\n        return count_sum_less_index_internal<true, true>(l, r, xi);\n   \
    \ }\n\n    CountSum count_sum_less(int l, int r, const T &x) const {\n       \
    \ return count_sum_less_index(l, r, lower_bound_value(x));\n    }\n\n    CountSum\
    \ count_sum_less_equal(int l, int r, const T &x) const {\n        return count_sum_less_index(l,\
    \ r, upper_bound_value(x));\n    }\n\n    int count_less(int l, int r, const T\
    \ &x) const {\n        return count_sum_less_index_internal<true, false>(\n  \
    \              l, r, lower_bound_value(x)).count;\n    }\n\n    int count_less_equal(int\
    \ l, int r, const T &x) const {\n        return count_sum_less_index_internal<true,\
    \ false>(\n                l, r, upper_bound_value(x)).count;\n    }\n\n    U\
    \ sum_less(int l, int r, const T &x) const {\n        return count_sum_less_index_internal<false,\
    \ true>(\n                l, r, lower_bound_value(x)).sum;\n    }\n\n    U sum_less_equal(int\
    \ l, int r, const T &x) const {\n        return count_sum_less_index_internal<false,\
    \ true>(\n                l, r, upper_bound_value(x)).sum;\n    }\n\n    pair<U,\
    \ U> sum_less_index_pair(int l, int r, int first_xi, int second_xi) const {\n\
    \        assert(built && 0 <= l && l <= r && r <= n);\n        if (l >= r) return\
    \ {U(), U()};\n        int value_count = (int)vals.size();\n        if (first_xi\
    \ <= 0 || first_xi >= value_count ||\n            second_xi <= 0 || second_xi\
    \ >= value_count) {\n            return {\n                    count_sum_less_index_internal<false,\
    \ true>(l, r, first_xi).sum,\n                    count_sum_less_index_internal<false,\
    \ true>(l, r, second_xi).sum\n            };\n        }\n\n        int first_l\
    \ = offset[l], first_r = offset[r];\n        int second_l = first_l, second_r\
    \ = first_r;\n        U first_sum = U(), second_sum = U();\n        const auto\
    \ *bit_data = bit.data();\n        const int *pref_data = pref.data();\n     \
    \   for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int first_l1,\
    \ first_r1;\n            rank1_pair(bit_data, pref_data, first_l, first_r, first_l1,\
    \ first_r1);\n            int first_l0 = first_l - first_l1;\n            int\
    \ first_r0 = first_r - first_r1;\n            if ((first_xi >> shift) & 1) {\n\
    \                first_sum += fenwick_range(\n                        zero_sum_fenwick,\
    \ row_offset[d], first_l0, first_r0);\n                first_l = mid[d] + first_l1;\n\
    \                first_r = mid[d] + first_r1;\n            }\n            else\
    \ {\n                first_l = first_l0;\n                first_r = first_r0;\n\
    \            }\n\n            int second_l1, second_r1;\n            rank1_pair(bit_data,\
    \ pref_data, second_l, second_r, second_l1, second_r1);\n            int second_l0\
    \ = second_l - second_l1;\n            int second_r0 = second_r - second_r1;\n\
    \            if ((second_xi >> shift) & 1) {\n                second_sum += fenwick_range(\n\
    \                        zero_sum_fenwick, row_offset[d], second_l0, second_r0);\n\
    \                second_l = mid[d] + second_l1;\n                second_r = mid[d]\
    \ + second_r1;\n            }\n            else {\n                second_l =\
    \ second_l0;\n                second_r = second_r0;\n            }\n\n       \
    \     bit_data += blocks;\n            pref_data += blocks + 1;\n        }\n \
    \       return {first_sum, second_sum};\n    }\n\n    Cursor range_cursor(int\
    \ l, int r) const {\n        assert(built && 0 <= l && l <= r && r <= n);\n  \
    \      return Cursor(this, 0, offset[l], offset[r], 0,\n                     \
    \ {r - l, fenwick_range(base_sum_fenwick, 0, l, r)});\n    }\n\n    Children split(const\
    \ Cursor &cur) const {\n        assert(cur.owner_ == this);\n        assert(!cur.is_leaf());\n\
    \n        const auto *row = bit.data() + cur.depth_ * blocks;\n        const int\
    \ *row_pref = pref.data() + cur.depth_ * (blocks + 1);\n        int l1, r1;\n\
    \        rank1_pair(row, row_pref, cur.l_, cur.r_, l1, r1);\n        int l0 =\
    \ cur.l_ - l1;\n        int r0 = cur.r_ - r1;\n\n        CountSum low;\n     \
    \   if (fixed_values) {\n            low = {\n                    r0 - l0,\n \
    \                   fenwick_range(\n                            zero_sum_fenwick,\
    \ row_offset[cur.depth_], l0, r0)\n            };\n        }\n        else {\n\
    \            low = fenwick_range_count_sum(\n                    zero_count_fenwick,\
    \ zero_sum_fenwick,\n                    row_offset[cur.depth_], l0, r0);\n  \
    \      }\n        CountSum high{\n                cur.all_.count - low.count,\n\
    \                cur.all_.sum - low.sum\n        };\n\n        int next_depth\
    \ = cur.depth_ + 1;\n        int prefix = cur.value_index_ << 1;\n        return\
    \ {\n                Cursor(this, next_depth, l0, r0, prefix, low),\n        \
    \        Cursor(this, next_depth,\n                       mid[cur.depth_] + l1,\
    \ mid[cur.depth_] + r1,\n                       prefix | 1, high)\n        };\n\
    \    }\n\n    U sum_k_smallest(int l, int r, int k) const {\n        assert(built\
    \ && 0 <= l && l <= r && r <= n);\n        assert(0 <= k && k <= r - l);\n   \
    \     if (k == 0) return U();\n        if (k == r - l) {\n            return fenwick_range(base_sum_fenwick,\
    \ 0, l, r);\n        }\n\n        l = offset[l];\n        r = offset[r];\n   \
    \     U res = U();\n        const auto *bit_data = bit.data();\n        const\
    \ int *pref_data = pref.data();\n        for (int d = 0; d < lg; ++d) {\n    \
    \        int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            int zero_count = fixed_values\
    \ ? r0 - l0 :\n                    fenwick_range(zero_count_fenwick, row_offset[d],\
    \ l0, r0);\n            if (k < zero_count) {\n                l = l0;\n     \
    \           r = r0;\n            }\n            else {\n                res +=\
    \ fenwick_range(zero_sum_fenwick, row_offset[d], l0, r0);\n                k -=\
    \ zero_count;\n                if (k == 0) return res;\n                l = mid[d]\
    \ + l1;\n                r = mid[d] + r1;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n\n        if (fixed_values)\
    \ {\n            return res + fenwick_range(leaf_sum_fenwick, 0, l, l + k);\n\
    \        }\n        int before = fenwick_prefix(leaf_count_fenwick, 0, l);\n \
    \       int end = fenwick_lower_bound(\n                leaf_count_fenwick, 0,\
    \ slot_count, before + k);\n        return res + fenwick_range(leaf_sum_fenwick,\
    \ 0, l, end);\n    }\n\n    template <bool need_count, bool need_sum>\n    CountSum\
    \ count_sum_equal_internal(int l, int r, int xi) const {\n        assert(built\
    \ && 0 <= l && l <= r && r <= n);\n        if (l >= r || xi < 0 || xi >= (int)vals.size())\
    \ return {0, U()};\n        l = offset[l];\n        r = offset[r];\n        const\
    \ auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n           \
    \ int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n  \
    \          if ((xi >> shift) & 1) {\n                l = mid[d] + l1;\n      \
    \          r = mid[d] + r1;\n            }\n            else {\n             \
    \   l -= l1;\n                r -= r1;\n            }\n            bit_data +=\
    \ blocks;\n            pref_data += blocks + 1;\n        }\n        int count\
    \ = 0;\n        U sum = U();\n        if (fixed_values) {\n            if constexpr\
    \ (need_count) count = r - l;\n            if constexpr (need_sum) {\n       \
    \         sum = fenwick_range(leaf_sum_fenwick, 0, l, r);\n            }\n   \
    \         return {count, sum};\n        }\n        if constexpr (need_count &&\
    \ need_sum) {\n            return fenwick_range_count_sum(\n                 \
    \   leaf_count_fenwick, leaf_sum_fenwick, 0, l, r);\n        }\n        if constexpr\
    \ (need_count) count = fenwick_range(leaf_count_fenwick, 0, l, r);\n        if\
    \ constexpr (need_sum) sum = fenwick_range(leaf_sum_fenwick, 0, l, r);\n     \
    \   return {count, sum};\n    }\n\n    CountSum count_sum_equal(int l, int r,\
    \ const T &x) const {\n        assert(built);\n        int xi = lower_bound_value(x);\n\
    \        if (xi == (int)vals.size() || !equivalent(vals[xi], x)) return {0, U()};\n\
    \        return count_sum_equal_internal<true, true>(l, r, xi);\n    }\n\n   \
    \ int freq(int l, int r, const T &x) const {\n        assert(built);\n       \
    \ int xi = lower_bound_value(x);\n        if (xi == (int)vals.size() || !equivalent(vals[xi],\
    \ x)) return 0;\n        return count_sum_equal_internal<true, false>(l, r, xi).count;\n\
    \    }\n\n    U sum_equal(int l, int r, const T &x) const {\n        assert(built);\n\
    \        int xi = lower_bound_value(x);\n        if (xi == (int)vals.size() ||\
    \ !equivalent(vals[xi], x)) return U();\n        return count_sum_equal_internal<false,\
    \ true>(l, r, xi).sum;\n    }\n\n    CountSum range_count_sum(int l, int r, const\
    \ T &lower, const T &upper) const {\n        CountSum hi = count_sum_less(l, r,\
    \ upper);\n        CountSum lo = count_sum_less(l, r, lower);\n        return\
    \ {hi.count - lo.count, hi.sum - lo.sum};\n    }\n\n    int range_freq(int l,\
    \ int r, const T &lower, const T &upper) const {\n        return count_less(l,\
    \ r, upper) - count_less(l, r, lower);\n    }\n\n    U range_sum(int l, int r,\
    \ const T &lower, const T &upper) const {\n        int lower_xi = lower_bound_value(lower);\n\
    \        int upper_xi = lower_bound_value(upper);\n        auto sums = sum_less_index_pair(l,\
    \ r, lower_xi, upper_xi);\n        return sums.second - sums.first;\n    }\n};\n\
    \n/**\n * @brief \u52D5\u7684\u91CD\u307F\u4ED8\u304DWavelet Matrix(Dynamic Weighted\
    \ Wavelet Matrix)\n */\n"
  code: "template <class T, class U>\nstruct DynamicWeightedWaveletMatrix {\n    struct\
    \ CountSum {\n        int count;\n        U sum;\n    };\n\n    static constexpr\
    \ bool use_fast_value_search =\n            is_integral<T>::value && !is_same<T,\
    \ bool>::value &&\n            sizeof(T) <= 8;\n\n    class Cursor {\n       \
    \ friend struct DynamicWeightedWaveletMatrix;\n\n        const DynamicWeightedWaveletMatrix\
    \ *owner_;\n        int depth_, l_, r_, value_index_;\n        CountSum all_;\n\
    \n        Cursor(const DynamicWeightedWaveletMatrix *owner, int depth,\n     \
    \          int l, int r, int value_index, CountSum all)\n            : owner_(owner),\
    \ depth_(depth), l_(l), r_(r),\n              value_index_(value_index), all_(all)\
    \ {}\n\n    public:\n        bool is_leaf() const {\n            return depth_\
    \ == owner_->lg;\n        }\n\n        bool empty() const {\n            return\
    \ all_.count == 0;\n        }\n\n        int count() const {\n            return\
    \ all_.count;\n        }\n\n        const U &sum() const {\n            return\
    \ all_.sum;\n        }\n\n        const CountSum &info() const {\n           \
    \ return all_;\n        }\n\n        const T &value() const {\n            assert(is_leaf()\
    \ && !empty());\n            assert(0 <= value_index_ && value_index_ < (int)owner_->vals.size());\n\
    \            return owner_->vals[value_index_];\n        }\n    };\n\n    struct\
    \ Children {\n        Cursor low;\n        Cursor high;\n    };\n\n    int n,\
    \ lg, blocks, slot_count;\n    bool initialized, built;\n    bool fixed_values;\n\
    \    vector<int> mid;\n    vector<int> row_offset;\n    vector<unsigned long long>\
    \ bit;\n    vector<int> pref;\n    vector<int> zero_count_fenwick;\n    vector<U>\
    \ zero_sum_fenwick;\n    vector<int> leaf_count_fenwick;\n    vector<U> leaf_sum_fenwick;\n\
    \    vector<U> base_sum_fenwick;\n    vector<int> offset;\n    vector<int> current_slot;\n\
    \    vector<int> slot_value_index;\n    vector<int> update_offset;\n    vector<int>\
    \ update_position;\n    vector<int> leaf_position;\n    vector<U> weights;\n \
    \   vector<T> vals;\n    vector<T> value_search_tree;\n    vector<int> value_search_rank;\n\
    \    vector<T> slot_values;\n    vector<pair<int, T>> value_candidates;\n\n  \
    \  DynamicWeightedWaveletMatrix()\n        : n(0), lg(0), blocks(0), slot_count(0),\
    \ initialized(false), built(false),\n          fixed_values(false) {}\n\n    explicit\
    \ DynamicWeightedWaveletMatrix(int n) : DynamicWeightedWaveletMatrix() {\n   \
    \     init(n);\n    }\n\n    DynamicWeightedWaveletMatrix(const vector<T> &v,\
    \ const vector<U> &w)\n        : DynamicWeightedWaveletMatrix((int)v.size()) {\n\
    \        build(v, w);\n    }\n\n    DynamicWeightedWaveletMatrix(const vector<T>\
    \ &v, const vector<U> &w,\n                                 const vector<pair<int,\
    \ T>> &candidates)\n        : DynamicWeightedWaveletMatrix((int)v.size()) {\n\
    \        reserve_candidates((int)candidates.size());\n        for (const auto\
    \ &[k, x] : candidates) add_value_candidate(k, x);\n        build(v, w);\n   \
    \ }\n\n    void init(int size) {\n        assert(size >= 0);\n        n = size;\n\
    \        lg = blocks = slot_count = 0;\n        initialized = true;\n        built\
    \ = false;\n        fixed_values = false;\n        mid.clear();\n        row_offset.clear();\n\
    \        bit.clear();\n        pref.clear();\n        zero_count_fenwick.clear();\n\
    \        zero_sum_fenwick.clear();\n        leaf_count_fenwick.clear();\n    \
    \    leaf_sum_fenwick.clear();\n        base_sum_fenwick.clear();\n        offset.clear();\n\
    \        current_slot.clear();\n        slot_value_index.clear();\n        update_offset.clear();\n\
    \        update_position.clear();\n        leaf_position.clear();\n        weights.clear();\n\
    \        vals.clear();\n        value_search_tree.clear();\n        value_search_rank.clear();\n\
    \        slot_values.clear();\n        value_candidates.clear();\n    }\n\n  \
    \  void reserve_candidates(int capacity) {\n        assert(initialized && !built\
    \ && capacity >= 0);\n        value_candidates.reserve(capacity);\n    }\n\n \
    \   void add_value_candidate(int k, const T &x) {\n        assert(initialized\
    \ && !built);\n        assert(0 <= k && k < n);\n        value_candidates.push_back({k,\
    \ x});\n    }\n\n    static bool equivalent(const T &a, const T &b) {\n      \
    \  return !(a < b) && !(b < a);\n    }\n\n    int lower_bound_value(const T &x)\
    \ const {\n        if constexpr (use_fast_value_search) {\n            unsigned\
    \ k = 1;\n            unsigned size = (unsigned)vals.size();\n            constexpr\
    \ unsigned prefetch_scale = sizeof(T) <= 4 ? 16 : 8;\n            while (k <=\
    \ size) {\n                if (k <= size / prefetch_scale) {\n               \
    \     __builtin_prefetch(\n                            value_search_tree.data()\
    \ + k * prefetch_scale);\n                }\n                k = (k << 1) + (value_search_tree[k]\
    \ < x);\n            }\n            unsigned inverted = ~k;\n            if (inverted\
    \ == 0) return (int)size;\n            k >>= __builtin_ctz(inverted) + 1;\n  \
    \          return k == 0 ? (int)size : value_search_rank[k];\n        }\n    \
    \    return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \    }\n\n    int upper_bound_value(const T &x) const {\n        if constexpr\
    \ (use_fast_value_search) {\n            unsigned k = 1;\n            unsigned\
    \ size = (unsigned)vals.size();\n            constexpr unsigned prefetch_scale\
    \ = sizeof(T) <= 4 ? 16 : 8;\n            while (k <= size) {\n              \
    \  if (k <= size / prefetch_scale) {\n                    __builtin_prefetch(\n\
    \                            value_search_tree.data() + k * prefetch_scale);\n\
    \                }\n                k = (k << 1) + !(x < value_search_tree[k]);\n\
    \            }\n            unsigned inverted = ~k;\n            if (inverted\
    \ == 0) return (int)size;\n            k >>= __builtin_ctz(inverted) + 1;\n  \
    \          return k == 0 ? (int)size : value_search_rank[k];\n        }\n    \
    \    return (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \    }\n\n    void build_value_search_tree() {\n        if constexpr (use_fast_value_search)\
    \ {\n            int size = (int)vals.size();\n            value_search_tree.resize(size\
    \ + 1);\n            value_search_rank.resize(size + 1);\n            int rank\
    \ = 0;\n            auto visit = [&](auto &&self, unsigned k) -> void {\n    \
    \            if (k > (unsigned)size) return;\n                self(self, k <<\
    \ 1);\n                value_search_tree[k] = vals[rank];\n                value_search_rank[k]\
    \ = rank++;\n                self(self, k << 1 | 1);\n            };\n       \
    \     visit(visit, 1);\n        }\n    }\n\n    template <class X>\n    static\
    \ auto encode_key(X x) -> typename make_unsigned<X>::type {\n        using Key\
    \ = typename make_unsigned<X>::type;\n        Key key = static_cast<Key>(x);\n\
    \        if constexpr (is_signed<X>::value) {\n            key ^= Key(1) << (sizeof(X)\
    \ * 8 - 1);\n        }\n        return key;\n    }\n\n    static inline int popcount(unsigned\
    \ long long x) {\n#if defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\")) {\n            unsigned long long result;\n            __asm__(\"popcnt{q\
    \ %1, %0| %0, %1}\"\n                    : \"=r\"(result) : \"r\"(x) : \"cc\"\
    );\n            return (int)result;\n        }\n#endif\n        return __builtin_popcountll(x);\n\
    \    }\n\n    static inline void popcount_pair(unsigned long long x,\n       \
    \                              unsigned long long y,\n                       \
    \              int &x_count, int &y_count) {\n#if defined(__x86_64__)\n      \
    \  if (__builtin_cpu_supports(\"popcnt\")) {\n            unsigned long long x_result,\
    \ y_result;\n            __asm__(\"popcnt{q %1, %0| %0, %1}\"\n              \
    \      : \"=r\"(x_result) : \"r\"(x) : \"cc\");\n            __asm__(\"popcnt{q\
    \ %1, %0| %0, %1}\"\n                    : \"=r\"(y_result) : \"r\"(y) : \"cc\"\
    );\n            x_count = (int)x_result;\n            y_count = (int)y_result;\n\
    \            return;\n        }\n#endif\n        x_count = __builtin_popcountll(x);\n\
    \        y_count = __builtin_popcountll(y);\n    }\n\n    static inline void rank1_pair(const\
    \ unsigned long long *row,\n                                  const int *row_pref,\n\
    \                                  int l, int r, int &l1, int &r1) {\n       \
    \ int l_block = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem =\
    \ l & 63;\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n  \
    \      int r_rem = r & 63;\n        if (l_rem && r_rem) {\n            int l_count,\
    \ r_count;\n            popcount_pair(\n                    row[l_block] & ((1ULL\
    \ << l_rem) - 1),\n                    row[r_block] & ((1ULL << r_rem) - 1),\n\
    \                    l_count, r_count);\n            l1 += l_count;\n        \
    \    r1 += r_count;\n            return;\n        }\n        if (l_rem) l1 +=\
    \ popcount(row[l_block] & ((1ULL << l_rem) - 1));\n        if (r_rem) r1 += popcount(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class V>\n    static void\
    \ fenwick_build(vector<V> &fw, int start, int length) {\n        for (int i =\
    \ 1; i <= length; ++i) {\n            int j = i + (i & -i);\n            if (j\
    \ <= length) fw[start + j] += fw[start + i];\n        }\n    }\n\n    template\
    \ <class V>\n    static void fenwick_add(vector<V> &fw, int start, int length,\
    \ int k, const V &x) {\n        for (++k; k <= length; k += k & -k) fw[start +\
    \ k] += x;\n    }\n\n    template <class V>\n    static V fenwick_prefix(const\
    \ vector<V> &fw, int start, int k) {\n        V res = V();\n        for (; k >\
    \ 0; k -= k & -k) res += fw[start + k];\n        return res;\n    }\n\n    template\
    \ <class V>\n    static V fenwick_range(const vector<V> &fw, int start, int l,\
    \ int r) {\n        return fenwick_prefix(fw, start, r) - fenwick_prefix(fw, start,\
    \ l);\n    }\n\n    static CountSum fenwick_range_count_sum(\n            const\
    \ vector<int> &count_fw, const vector<U> &sum_fw,\n            int start, int\
    \ l, int r) {\n        CountSum res{0, U()};\n        for (; r > 0; r -= r & -r)\
    \ {\n            res.count += count_fw[start + r];\n            res.sum += sum_fw[start\
    \ + r];\n        }\n        for (; l > 0; l -= l & -l) {\n            res.count\
    \ -= count_fw[start + l];\n            res.sum -= sum_fw[start + l];\n       \
    \ }\n        return res;\n    }\n\n    static void fenwick_add_count_sum(\n  \
    \          vector<int> &count_fw, vector<U> &sum_fw,\n            int start, int\
    \ length, int k, int count_delta, const U &sum_delta) {\n        for (++k; k <=\
    \ length; k += k & -k) {\n            count_fw[start + k] += count_delta;\n  \
    \          sum_fw[start + k] += sum_delta;\n        }\n    }\n\n    static int\
    \ fenwick_lower_bound(const vector<int> &fw, int start, int length, int target)\
    \ {\n        assert(target > 0);\n        int k = 0;\n        int step = 1;\n\
    \        while ((step << 1) <= length) step <<= 1;\n        for (; step > 0; step\
    \ >>= 1) {\n            int next = k + step;\n            if (next <= length &&\
    \ fw[start + next] < target) {\n                k = next;\n                target\
    \ -= fw[start + next];\n            }\n        }\n        return k + 1;\n    }\n\
    \n    int find_slot(int k, const T &x) const {\n        auto first = slot_values.begin()\
    \ + offset[k];\n        auto last = slot_values.begin() + offset[k + 1];\n   \
    \     auto it = lower_bound(first, last, x);\n        if (it == last || !equivalent(*it,\
    \ x)) return -1;\n        return (int)(it - slot_values.begin());\n    }\n\n \
    \   void build(const vector<T> &v, const vector<U> &w) {\n        if (!initialized)\
    \ init((int)v.size());\n        assert(!built);\n        assert((int)v.size()\
    \ == n && (int)w.size() == n);\n\n        vector<int> raw_offset(n + 1, 0);\n\
    \        for (const auto &[k, x] : value_candidates) {\n            (void)x;\n\
    \            ++raw_offset[k + 1];\n        }\n        for (int i = 0; i < n; ++i)\
    \ ++raw_offset[i + 1];\n        for (int i = 0; i < n; ++i) raw_offset[i + 1]\
    \ += raw_offset[i];\n\n        vector<T> raw_values(raw_offset[n]);\n        vector<int>\
    \ write_position = raw_offset;\n        for (const auto &[k, x] : value_candidates)\
    \ {\n            raw_values[write_position[k]++] = x;\n        }\n        for\
    \ (int i = 0; i < n; ++i) {\n            raw_values[write_position[i]++] = v[i];\n\
    \        }\n\n        offset.assign(n + 1, 0);\n        slot_values.clear();\n\
    \        slot_values.reserve(raw_values.size());\n        for (int k = 0; k <\
    \ n; ++k) {\n            auto first = raw_values.begin() + raw_offset[k];\n  \
    \          auto last = raw_values.begin() + raw_offset[k + 1];\n            sort(first,\
    \ last);\n            for (auto it = first; it != last; ++it) {\n            \
    \    if ((int)slot_values.size() == offset[k] ||\n                    !equivalent(slot_values.back(),\
    \ *it)) {\n                    slot_values.push_back(move(*it));\n           \
    \     }\n            }\n            offset[k + 1] = (int)slot_values.size();\n\
    \        }\n        slot_count = (int)slot_values.size();\n\n        slot_value_index.resize(slot_count);\n\
    \        if constexpr (is_integral<T>::value && !is_same<T, bool>::value &&\n\
    \                      sizeof(T) <= 8) {\n            using Key = typename make_unsigned<T>::type;\n\
    \            vector<Key> keys(slot_count);\n            vector<int> ord(slot_count),\
    \ buf(slot_count);\n            for (int i = 0; i < slot_count; ++i) {\n     \
    \           keys[i] = encode_key(slot_values[i]);\n                ord[i] = i;\n\
    \            }\n\n            constexpr int radix_bits = 16;\n            constexpr\
    \ int bucket_count = 1 << radix_bits;\n            constexpr int mask = bucket_count\
    \ - 1;\n            int passes = (int)(sizeof(Key) * 8 + radix_bits - 1) / radix_bits;\n\
    \            vector<int> count(bucket_count), position(bucket_count);\n      \
    \      for (int pass = 0; pass < passes; ++pass) {\n                fill(count.begin(),\
    \ count.end(), 0);\n                int shift = pass * radix_bits;\n         \
    \       for (int id : ord) ++count[(keys[id] >> shift) & mask];\n            \
    \    position[0] = 0;\n                for (int i = 0; i + 1 < bucket_count; ++i)\
    \ {\n                    position[i + 1] = position[i] + count[i];\n         \
    \       }\n                for (int id : ord) {\n                    buf[position[(keys[id]\
    \ >> shift) & mask]++] = id;\n                }\n                ord.swap(buf);\n\
    \            }\n\n            vals.clear();\n            vals.reserve(slot_count);\n\
    \            bool has_previous = false;\n            Key previous = 0;\n     \
    \       for (int id : ord) {\n                if (!has_previous || keys[id] !=\
    \ previous) {\n                    vals.push_back(slot_values[id]);\n        \
    \            previous = keys[id];\n                    has_previous = true;\n\
    \                }\n                slot_value_index[id] = (int)vals.size() -\
    \ 1;\n            }\n        }\n        else {\n            vals = slot_values;\n\
    \            sort(vals.begin(), vals.end());\n            int value_count = 0;\n\
    \            for (int i = 0; i < (int)vals.size(); ++i) {\n                if\
    \ (value_count == 0 ||\n                    !equivalent(vals[value_count - 1],\
    \ vals[i])) {\n                    if (value_count != i) vals[value_count] = move(vals[i]);\n\
    \                    ++value_count;\n                }\n            }\n      \
    \      vals.resize(value_count);\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                slot_value_index[i] = (int)(lower_bound(\n         \
    \               vals.begin(), vals.end(), slot_values[i]) - vals.begin());\n \
    \           }\n        }\n        build_value_search_tree();\n        fixed_values\
    \ = slot_count == n;\n        current_slot.resize(n);\n        weights = w;\n\
    \        for (int i = 0; i < n; ++i) {\n            current_slot[i] = find_slot(i,\
    \ v[i]);\n            assert(current_slot[i] != -1);\n        }\n\n        if\
    \ (slot_count == 0) {\n            lg = blocks = 0;\n            mid.clear();\n\
    \            row_offset.clear();\n            bit.clear();\n            pref.clear();\n\
    \            zero_count_fenwick.clear();\n            zero_sum_fenwick.clear();\n\
    \            leaf_count_fenwick.assign(1, 0);\n            leaf_sum_fenwick.assign(1,\
    \ U());\n            base_sum_fenwick.assign(1, U());\n            slot_value_index.clear();\n\
    \            update_offset.clear();\n            update_position.clear();\n  \
    \          leaf_position.clear();\n            value_candidates.clear();\n   \
    \         value_candidates.shrink_to_fit();\n            built = true;\n     \
    \       return;\n        }\n\n        lg = 0;\n        while ((1LL << lg) < (int)vals.size())\
    \ ++lg;\n        if (lg == 0) lg = 1;\n        blocks = (slot_count + 63) >> 6;\n\
    \n        vector<unsigned char> active(slot_count, 0);\n        vector<U> active_weight(slot_count,\
    \ U());\n        for (int i = 0; i < n; ++i) {\n            active[current_slot[i]]\
    \ = 1;\n            active_weight[current_slot[i]] = w[i];\n        }\n\n    \
    \    mid.assign(lg, 0);\n        bit.assign(lg * blocks, 0);\n        pref.assign(lg\
    \ * (blocks + 1), 0);\n        vector<int> cur(slot_count), nxt(slot_count);\n\
    \        for (int i = 0; i < slot_count; ++i) cur[i] = i;\n\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            auto *row = bit.data()\
    \ + d * blocks;\n            auto *row_pref = pref.data() + d * (blocks + 1);\n\
    \            int zero_count = 0;\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                int b = (slot_value_index[cur[i]] >> shift) & 1;\n \
    \               if (b) row[i >> 6] |= 1ULL << (i & 63);\n                else\
    \ ++zero_count;\n            }\n            mid[d] = zero_count;\n           \
    \ for (int i = 0; i < blocks; ++i) {\n                row_pref[i + 1] = row_pref[i]\
    \ + popcount(row[i]);\n            }\n\n            int zi = 0, oi = zero_count;\n\
    \            for (int i = 0; i < slot_count; ++i) {\n                int id =\
    \ cur[i];\n                if ((slot_value_index[id] >> shift) & 1) nxt[oi++]\
    \ = id;\n                else nxt[zi++] = id;\n            }\n            cur.swap(nxt);\n\
    \        }\n\n        row_offset.resize(lg);\n        size_t fenwick_size = 0;\n\
    \        for (int d = 0; d < lg; ++d) {\n            row_offset[d] = (int)fenwick_size;\n\
    \            fenwick_size += (size_t)mid[d] + 1;\n        }\n        if (fixed_values)\
    \ zero_count_fenwick.clear();\n        else zero_count_fenwick.assign(fenwick_size,\
    \ 0);\n        zero_sum_fenwick.assign(fenwick_size, U());\n        update_offset.resize(slot_count\
    \ + 1);\n        for (int i = 0; i < slot_count; ++i) {\n            update_offset[i\
    \ + 1] = update_offset[i] +\n                    lg - __builtin_popcount((unsigned)slot_value_index[i]);\n\
    \        }\n        update_position.resize(update_offset.back());\n        vector<int>\
    \ update_next = update_offset;\n        leaf_position.resize(slot_count);\n\n\
    \        for (int i = 0; i < slot_count; ++i) cur[i] = i;\n        for (int d\
    \ = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int start = row_offset[d];\n\
    \            int zi = 0, oi = mid[d];\n            for (int i = 0; i < slot_count;\
    \ ++i) {\n                int id = cur[i];\n                if ((slot_value_index[id]\
    \ >> shift) & 1) {\n                    nxt[oi++] = id;\n                }\n \
    \               else {\n                    nxt[zi] = id;\n                  \
    \  update_position[update_next[id]++] = zi;\n                    if (active[id])\
    \ {\n                        if (!fixed_values) zero_count_fenwick[start + zi\
    \ + 1] = 1;\n                        zero_sum_fenwick[start + zi + 1] = active_weight[id];\n\
    \                    }\n                    ++zi;\n                }\n       \
    \     }\n            if (!fixed_values) fenwick_build(zero_count_fenwick, start,\
    \ mid[d]);\n            fenwick_build(zero_sum_fenwick, start, mid[d]);\n    \
    \        cur.swap(nxt);\n        }\n\n        if (fixed_values) leaf_count_fenwick.clear();\n\
    \        else leaf_count_fenwick.assign(slot_count + 1, 0);\n        leaf_sum_fenwick.assign(slot_count\
    \ + 1, U());\n        for (int i = 0; i < slot_count; ++i) {\n            int\
    \ id = cur[i];\n            leaf_position[id] = i;\n            if (active[id])\
    \ {\n                if (!fixed_values) leaf_count_fenwick[i + 1] = 1;\n     \
    \           leaf_sum_fenwick[i + 1] = active_weight[id];\n            }\n    \
    \    }\n        if (!fixed_values) fenwick_build(leaf_count_fenwick, 0, slot_count);\n\
    \        fenwick_build(leaf_sum_fenwick, 0, slot_count);\n\n        base_sum_fenwick.assign(n\
    \ + 1, U());\n        for (int i = 0; i < n; ++i) base_sum_fenwick[i + 1] = w[i];\n\
    \        fenwick_build(base_sum_fenwick, 0, n);\n\n        value_candidates.clear();\n\
    \        value_candidates.shrink_to_fit();\n        built = true;\n    }\n\n \
    \   void add_slot(int slot, int count_delta, const U &sum_delta) {\n        const\
    \ int *positions = update_position.data() + update_offset[slot];\n        int\
    \ xi = slot_value_index[slot];\n        unsigned zero_mask = (~(unsigned)xi) &\
    \ ((1U << lg) - 1);\n        while (zero_mask) {\n            int shift = 31 -\
    \ __builtin_clz(zero_mask);\n            int d = lg - 1 - shift;\n           \
    \ int p = *positions++;\n            if (count_delta != 0) {\n               \
    \ fenwick_add_count_sum(\n                        zero_count_fenwick, zero_sum_fenwick,\n\
    \                        row_offset[d], mid[d], p, count_delta, sum_delta);\n\
    \            }\n            else {\n                fenwick_add(\n           \
    \             zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);\n      \
    \      }\n            zero_mask ^= 1U << shift;\n        }\n        int p = leaf_position[slot];\n\
    \        if (count_delta != 0) {\n            fenwick_add_count_sum(\n       \
    \             leaf_count_fenwick, leaf_sum_fenwick,\n                    0, slot_count,\
    \ p, count_delta, sum_delta);\n        }\n        else {\n            fenwick_add(leaf_sum_fenwick,\
    \ 0, slot_count, p, sum_delta);\n        }\n    }\n\n    void add_slot_sum(int\
    \ slot, const U &sum_delta) {\n        const int *positions = update_position.data()\
    \ + update_offset[slot];\n        int xi = slot_value_index[slot];\n        unsigned\
    \ zero_mask = (~(unsigned)xi) & ((1U << lg) - 1);\n        while (zero_mask) {\n\
    \            int shift = 31 - __builtin_clz(zero_mask);\n            int d = lg\
    \ - 1 - shift;\n            int p = *positions++;\n            fenwick_add(\n\
    \                    zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);\n\
    \            zero_mask ^= 1U << shift;\n        }\n        int p = leaf_position[slot];\n\
    \        fenwick_add(leaf_sum_fenwick, 0, slot_count, p, sum_delta);\n    }\n\n\
    \    bool set_value(int k, const T &x) {\n        assert(built && 0 <= k && k\
    \ < n);\n        int next_slot = find_slot(k, x);\n        if (next_slot == -1)\
    \ return false;\n        int old_slot = current_slot[k];\n        if (old_slot\
    \ == next_slot) return true;\n        add_slot(old_slot, -1, U() - weights[k]);\n\
    \        add_slot(next_slot, 1, weights[k]);\n        current_slot[k] = next_slot;\n\
    \        return true;\n    }\n\n    void set_weight(int k, const U &w) {\n   \
    \     assert(built && 0 <= k && k < n);\n        U delta = w - weights[k];\n \
    \       fenwick_add(base_sum_fenwick, 0, n, k, delta);\n        add_slot_sum(current_slot[k],\
    \ delta);\n        weights[k] = w;\n    }\n\n    void add_weight(int k, const\
    \ U &delta) {\n        assert(built && 0 <= k && k < n);\n        fenwick_add(base_sum_fenwick,\
    \ 0, n, k, delta);\n        add_slot_sum(current_slot[k], delta);\n        weights[k]\
    \ += delta;\n    }\n\n    bool set(int k, const T &x, const U &w) {\n        assert(built\
    \ && 0 <= k && k < n);\n        int next_slot = find_slot(k, x);\n        if (next_slot\
    \ == -1) return false;\n        int old_slot = current_slot[k];\n        if (old_slot\
    \ == next_slot) {\n            set_weight(k, w);\n            return true;\n \
    \       }\n        fenwick_add(base_sum_fenwick, 0, n, k, w - weights[k]);\n \
    \       add_slot(old_slot, -1, U() - weights[k]);\n        add_slot(next_slot,\
    \ 1, w);\n        current_slot[k] = next_slot;\n        weights[k] = w;\n    \
    \    return true;\n    }\n\n    const T &get_value(int k) const {\n        assert(built\
    \ && 0 <= k && k < n);\n        return slot_values[current_slot[k]];\n    }\n\n\
    \    const U &get_weight(int k) const {\n        assert(built && 0 <= k && k <\
    \ n);\n        return weights[k];\n    }\n\n    template <bool need_count, bool\
    \ need_sum>\n    CountSum count_sum_less_index_internal(int l, int r, int xi)\
    \ const {\n        assert(built && 0 <= l && l <= r && r <= n);\n        if (xi\
    \ <= 0 || l >= r || n == 0) return {0, U()};\n        if (xi >= (int)vals.size())\
    \ {\n            U sum = U();\n            if constexpr (need_sum) {\n       \
    \         sum = fenwick_range(base_sum_fenwick, 0, l, r);\n            }\n   \
    \         return {need_count ? r - l : 0, sum};\n        }\n\n        l = offset[l];\n\
    \        r = offset[r];\n        CountSum res{0, U()};\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n  \
    \          rank1_pair(bit_data, pref_data, l, r, l1, r1);\n            int l0\
    \ = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n             \
    \   if (fixed_values) {\n                    if constexpr (need_count) res.count\
    \ += r0 - l0;\n                    if constexpr (need_sum) {\n               \
    \         res.sum += fenwick_range(\n                                zero_sum_fenwick,\
    \ row_offset[d], l0, r0);\n                    }\n                }\n        \
    \        else {\n                    if constexpr (need_count && need_sum) {\n\
    \                        CountSum part = fenwick_range_count_sum(\n          \
    \                      zero_count_fenwick, zero_sum_fenwick,\n               \
    \                 row_offset[d], l0, r0);\n                        res.count +=\
    \ part.count;\n                        res.sum += part.sum;\n                \
    \    }\n                    else {\n                        if constexpr (need_count)\
    \ {\n                            res.count += fenwick_range(\n               \
    \                     zero_count_fenwick, row_offset[d], l0, r0);\n          \
    \              }\n                        if constexpr (need_sum) {\n        \
    \                    res.sum += fenwick_range(\n                             \
    \       zero_sum_fenwick, row_offset[d], l0, r0);\n                        }\n\
    \                    }\n                }\n                l = mid[d] + l1;\n\
    \                r = mid[d] + r1;\n            }\n            else {\n       \
    \         l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ res;\n    }\n\n    CountSum count_sum_less_index(int l, int r, int xi) const\
    \ {\n        return count_sum_less_index_internal<true, true>(l, r, xi);\n   \
    \ }\n\n    CountSum count_sum_less(int l, int r, const T &x) const {\n       \
    \ return count_sum_less_index(l, r, lower_bound_value(x));\n    }\n\n    CountSum\
    \ count_sum_less_equal(int l, int r, const T &x) const {\n        return count_sum_less_index(l,\
    \ r, upper_bound_value(x));\n    }\n\n    int count_less(int l, int r, const T\
    \ &x) const {\n        return count_sum_less_index_internal<true, false>(\n  \
    \              l, r, lower_bound_value(x)).count;\n    }\n\n    int count_less_equal(int\
    \ l, int r, const T &x) const {\n        return count_sum_less_index_internal<true,\
    \ false>(\n                l, r, upper_bound_value(x)).count;\n    }\n\n    U\
    \ sum_less(int l, int r, const T &x) const {\n        return count_sum_less_index_internal<false,\
    \ true>(\n                l, r, lower_bound_value(x)).sum;\n    }\n\n    U sum_less_equal(int\
    \ l, int r, const T &x) const {\n        return count_sum_less_index_internal<false,\
    \ true>(\n                l, r, upper_bound_value(x)).sum;\n    }\n\n    pair<U,\
    \ U> sum_less_index_pair(int l, int r, int first_xi, int second_xi) const {\n\
    \        assert(built && 0 <= l && l <= r && r <= n);\n        if (l >= r) return\
    \ {U(), U()};\n        int value_count = (int)vals.size();\n        if (first_xi\
    \ <= 0 || first_xi >= value_count ||\n            second_xi <= 0 || second_xi\
    \ >= value_count) {\n            return {\n                    count_sum_less_index_internal<false,\
    \ true>(l, r, first_xi).sum,\n                    count_sum_less_index_internal<false,\
    \ true>(l, r, second_xi).sum\n            };\n        }\n\n        int first_l\
    \ = offset[l], first_r = offset[r];\n        int second_l = first_l, second_r\
    \ = first_r;\n        U first_sum = U(), second_sum = U();\n        const auto\
    \ *bit_data = bit.data();\n        const int *pref_data = pref.data();\n     \
    \   for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int first_l1,\
    \ first_r1;\n            rank1_pair(bit_data, pref_data, first_l, first_r, first_l1,\
    \ first_r1);\n            int first_l0 = first_l - first_l1;\n            int\
    \ first_r0 = first_r - first_r1;\n            if ((first_xi >> shift) & 1) {\n\
    \                first_sum += fenwick_range(\n                        zero_sum_fenwick,\
    \ row_offset[d], first_l0, first_r0);\n                first_l = mid[d] + first_l1;\n\
    \                first_r = mid[d] + first_r1;\n            }\n            else\
    \ {\n                first_l = first_l0;\n                first_r = first_r0;\n\
    \            }\n\n            int second_l1, second_r1;\n            rank1_pair(bit_data,\
    \ pref_data, second_l, second_r, second_l1, second_r1);\n            int second_l0\
    \ = second_l - second_l1;\n            int second_r0 = second_r - second_r1;\n\
    \            if ((second_xi >> shift) & 1) {\n                second_sum += fenwick_range(\n\
    \                        zero_sum_fenwick, row_offset[d], second_l0, second_r0);\n\
    \                second_l = mid[d] + second_l1;\n                second_r = mid[d]\
    \ + second_r1;\n            }\n            else {\n                second_l =\
    \ second_l0;\n                second_r = second_r0;\n            }\n\n       \
    \     bit_data += blocks;\n            pref_data += blocks + 1;\n        }\n \
    \       return {first_sum, second_sum};\n    }\n\n    Cursor range_cursor(int\
    \ l, int r) const {\n        assert(built && 0 <= l && l <= r && r <= n);\n  \
    \      return Cursor(this, 0, offset[l], offset[r], 0,\n                     \
    \ {r - l, fenwick_range(base_sum_fenwick, 0, l, r)});\n    }\n\n    Children split(const\
    \ Cursor &cur) const {\n        assert(cur.owner_ == this);\n        assert(!cur.is_leaf());\n\
    \n        const auto *row = bit.data() + cur.depth_ * blocks;\n        const int\
    \ *row_pref = pref.data() + cur.depth_ * (blocks + 1);\n        int l1, r1;\n\
    \        rank1_pair(row, row_pref, cur.l_, cur.r_, l1, r1);\n        int l0 =\
    \ cur.l_ - l1;\n        int r0 = cur.r_ - r1;\n\n        CountSum low;\n     \
    \   if (fixed_values) {\n            low = {\n                    r0 - l0,\n \
    \                   fenwick_range(\n                            zero_sum_fenwick,\
    \ row_offset[cur.depth_], l0, r0)\n            };\n        }\n        else {\n\
    \            low = fenwick_range_count_sum(\n                    zero_count_fenwick,\
    \ zero_sum_fenwick,\n                    row_offset[cur.depth_], l0, r0);\n  \
    \      }\n        CountSum high{\n                cur.all_.count - low.count,\n\
    \                cur.all_.sum - low.sum\n        };\n\n        int next_depth\
    \ = cur.depth_ + 1;\n        int prefix = cur.value_index_ << 1;\n        return\
    \ {\n                Cursor(this, next_depth, l0, r0, prefix, low),\n        \
    \        Cursor(this, next_depth,\n                       mid[cur.depth_] + l1,\
    \ mid[cur.depth_] + r1,\n                       prefix | 1, high)\n        };\n\
    \    }\n\n    U sum_k_smallest(int l, int r, int k) const {\n        assert(built\
    \ && 0 <= l && l <= r && r <= n);\n        assert(0 <= k && k <= r - l);\n   \
    \     if (k == 0) return U();\n        if (k == r - l) {\n            return fenwick_range(base_sum_fenwick,\
    \ 0, l, r);\n        }\n\n        l = offset[l];\n        r = offset[r];\n   \
    \     U res = U();\n        const auto *bit_data = bit.data();\n        const\
    \ int *pref_data = pref.data();\n        for (int d = 0; d < lg; ++d) {\n    \
    \        int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            int zero_count = fixed_values\
    \ ? r0 - l0 :\n                    fenwick_range(zero_count_fenwick, row_offset[d],\
    \ l0, r0);\n            if (k < zero_count) {\n                l = l0;\n     \
    \           r = r0;\n            }\n            else {\n                res +=\
    \ fenwick_range(zero_sum_fenwick, row_offset[d], l0, r0);\n                k -=\
    \ zero_count;\n                if (k == 0) return res;\n                l = mid[d]\
    \ + l1;\n                r = mid[d] + r1;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n\n        if (fixed_values)\
    \ {\n            return res + fenwick_range(leaf_sum_fenwick, 0, l, l + k);\n\
    \        }\n        int before = fenwick_prefix(leaf_count_fenwick, 0, l);\n \
    \       int end = fenwick_lower_bound(\n                leaf_count_fenwick, 0,\
    \ slot_count, before + k);\n        return res + fenwick_range(leaf_sum_fenwick,\
    \ 0, l, end);\n    }\n\n    template <bool need_count, bool need_sum>\n    CountSum\
    \ count_sum_equal_internal(int l, int r, int xi) const {\n        assert(built\
    \ && 0 <= l && l <= r && r <= n);\n        if (l >= r || xi < 0 || xi >= (int)vals.size())\
    \ return {0, U()};\n        l = offset[l];\n        r = offset[r];\n        const\
    \ auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n           \
    \ int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n  \
    \          if ((xi >> shift) & 1) {\n                l = mid[d] + l1;\n      \
    \          r = mid[d] + r1;\n            }\n            else {\n             \
    \   l -= l1;\n                r -= r1;\n            }\n            bit_data +=\
    \ blocks;\n            pref_data += blocks + 1;\n        }\n        int count\
    \ = 0;\n        U sum = U();\n        if (fixed_values) {\n            if constexpr\
    \ (need_count) count = r - l;\n            if constexpr (need_sum) {\n       \
    \         sum = fenwick_range(leaf_sum_fenwick, 0, l, r);\n            }\n   \
    \         return {count, sum};\n        }\n        if constexpr (need_count &&\
    \ need_sum) {\n            return fenwick_range_count_sum(\n                 \
    \   leaf_count_fenwick, leaf_sum_fenwick, 0, l, r);\n        }\n        if constexpr\
    \ (need_count) count = fenwick_range(leaf_count_fenwick, 0, l, r);\n        if\
    \ constexpr (need_sum) sum = fenwick_range(leaf_sum_fenwick, 0, l, r);\n     \
    \   return {count, sum};\n    }\n\n    CountSum count_sum_equal(int l, int r,\
    \ const T &x) const {\n        assert(built);\n        int xi = lower_bound_value(x);\n\
    \        if (xi == (int)vals.size() || !equivalent(vals[xi], x)) return {0, U()};\n\
    \        return count_sum_equal_internal<true, true>(l, r, xi);\n    }\n\n   \
    \ int freq(int l, int r, const T &x) const {\n        assert(built);\n       \
    \ int xi = lower_bound_value(x);\n        if (xi == (int)vals.size() || !equivalent(vals[xi],\
    \ x)) return 0;\n        return count_sum_equal_internal<true, false>(l, r, xi).count;\n\
    \    }\n\n    U sum_equal(int l, int r, const T &x) const {\n        assert(built);\n\
    \        int xi = lower_bound_value(x);\n        if (xi == (int)vals.size() ||\
    \ !equivalent(vals[xi], x)) return U();\n        return count_sum_equal_internal<false,\
    \ true>(l, r, xi).sum;\n    }\n\n    CountSum range_count_sum(int l, int r, const\
    \ T &lower, const T &upper) const {\n        CountSum hi = count_sum_less(l, r,\
    \ upper);\n        CountSum lo = count_sum_less(l, r, lower);\n        return\
    \ {hi.count - lo.count, hi.sum - lo.sum};\n    }\n\n    int range_freq(int l,\
    \ int r, const T &lower, const T &upper) const {\n        return count_less(l,\
    \ r, upper) - count_less(l, r, lower);\n    }\n\n    U range_sum(int l, int r,\
    \ const T &lower, const T &upper) const {\n        int lower_xi = lower_bound_value(lower);\n\
    \        int upper_xi = lower_bound_value(upper);\n        auto sums = sum_less_index_pair(l,\
    \ r, lower_xi, upper_xi);\n        return sums.second - sums.first;\n    }\n};\n\
    \n/**\n * @brief \u52D5\u7684\u91CD\u307F\u4ED8\u304DWavelet Matrix(Dynamic Weighted\
    \ Wavelet Matrix)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dynamic_weighted_wavelet_matrix.cpp
  requiredBy: []
  timestamp: '2026-07-26 11:18:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_dynamic_weighted_wavelet_matrix.test.cpp
  - test/yosupo_point_set_range_frequency.test.cpp
  - test/yosupo_point_add_rectangle_sum_dynamic_weighted_wavelet_matrix.test.cpp
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
- `range_cursor(l, r)`
  区間 $[l, r)$ に対応する二分木の根を `Cursor` として返す
- `split(cur)`
  葉でない `Cursor` を値の小さい子 `low` と大きい子 `high` に分ける
- `Cursor::is_leaf()` / `empty()` / `count()` / `sum()` / `info()`
  葉か、空か、含まれる要素数・重み和を返す
- `Cursor::value()`
  空でない葉が表す値を返す。葉でない場合や空の場合は呼べない
- `count_sum_less(l, r, x)` / `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満または以下の要素数と重み和を返す
- `count_less(l, r, x)` / `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数または重み和を返す
- `sum_k_smallest(l, r, k)`
  区間 $[l, r)$ の要素を値の昇順に並べたとき、小さい方から `k` 個の重み和を返す。`0 <= k <= r - l` とし、同値の要素は位置が小さい順に扱う
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

`Cursor` を使うと、必要な側だけへ値の二分木を降りられる。

```cpp
auto cur = wm.range_cursor(l, r);
assert(!cur.empty());
while (!cur.is_leaf()) {
    auto children = wm.split(cur);
    cur = children.high.empty() ? children.low : children.high;
}
auto maximum = cur.value();
```

更新を行うと、それ以前に作った `Cursor` は無効になる。

## 実装上の補足
- 各位置の候補を連続したスロットへ展開し、各位置につき一つのスロットだけを有効にする
- 値変更は旧スロットの無効化と新スロットの有効化で処理する
- $M$ を登録後の候補スロット数、$\sigma$ を候補値の種類数とする
- 構築は $O(M \log M + M \log \sigma)$
- 更新と `less`・値区間・`sum_k_smallest` クエリは $O(\log \sigma \log M)$
- `freq` と `sum_equal` は $O(\log \sigma + \log M)$
- `range_cursor` は $O(\log N)$、`split` は $O(\log M)$。根から葉まで降りると $O(\log \sigma \log M)$
- メモリ使用量は $O(M \log \sigma)$
- `U` は `U()` を零元として加算と減算ができる型を使う
