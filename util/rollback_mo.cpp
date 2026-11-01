#ifndef FIRIEXP_LIBRARY_UTIL_ROLLBACK_MO_CPP
#define FIRIEXP_LIBRARY_UTIL_ROLLBACK_MO_CPP

#include "mo.cpp"

template<class State>
void rollback_mo_solve(int n, const vector<Query> &queries, State &state, int bucket_size = 0) {
    assert(n >= 0);
    if (queries.empty()) return;
    if (bucket_size <= 0) bucket_size = max(1, (int)(n / sqrt((double)queries.size())));
    struct OrderedQuery {
        uint64_t key;
        size_t index;
    };
    vector<OrderedQuery> ordered;
    ordered.reserve(queries.size());
    for (size_t i = 0; i < queries.size(); ++i) {
        const auto &q = queries[i];
        assert(0 <= q.l && q.l <= q.r && q.r <= n);
        uint32_t block = q.l / bucket_size;
        ordered.push_back({(uint64_t(block) << 32) | uint32_t(q.r), i});
    }
    sort(ordered.begin(), ordered.end(), [](const OrderedQuery &a, const OrderedQuery &b) {
        return a.key < b.key;
    });
    int block = -1, end = 0, right = 0;
    for (const auto &item : ordered) {
        const auto &q = queries[item.index];
        int next_block = int(item.key >> 32);
        if (next_block != block) {
            state.reset();
            block = next_block;
            int begin = block * bucket_size;
            end = begin + min(bucket_size, n - begin);
            right = end;
        }
        if (q.r <= end) {
            auto token = state.snapshot();
            for (int i = q.l; i < q.r; ++i) state.add_right(i);
            state.output(q.no);
            state.rollback(token);
        } else {
            while (right < q.r) state.add_right(right++);
            auto token = state.snapshot();
            for (int i = end; i > q.l;) state.add_left(--i);
            state.output(q.no);
            state.rollback(token);
        }
    }
    state.reset();
}

#endif

/**
 * @brief Rollbackを使うMo
 */
