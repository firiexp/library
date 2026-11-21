#ifndef FIRIEXP_LIBRARY_UTIL_MO_WITH_UPDATES_CPP
#define FIRIEXP_LIBRARY_UTIL_MO_WITH_UPDATES_CPP

struct MoUpdateQuery {
    int l, r, t, no;
    MoUpdateQuery(int l, int r, int t, int no) : l(l), r(r), t(t), no(no) {}
    MoUpdateQuery() : MoUpdateQuery(0, 0, 0, 0) {}
};

template<class AddLeft, class AddRight, class EraseLeft, class EraseRight,
         class Apply, class Undo, class Output>
void mo_with_updates_solve(int n, const vector<MoUpdateQuery> &queries,
                           AddLeft add_left, AddRight add_right, EraseLeft erase_left,
                           EraseRight erase_right, Apply apply, Undo undo, Output output,
                           int bucket_size = 0) {
    assert(n >= 0);
    if (queries.empty()) return;
    if (bucket_size <= 0) bucket_size = max(1, (int)cbrt((double)n * n));
    vector<pair<array<int, 3>, size_t>> order;
    order.reserve(queries.size());
    for (size_t i = 0; i < queries.size(); ++i) {
        const auto &q = queries[i];
        assert(0 <= q.l && q.l <= q.r && q.r <= n && q.t >= 0);
        int left_block = q.l / bucket_size, right_block = q.r / bucket_size;
        int right_order = (left_block & 1) ? right_block : -right_block;
        int time_order = ((left_block ^ right_block) & 1) ? -q.t : q.t;
        order.push_back({{left_block, right_order, time_order}, i});
    }
    sort(order.begin(), order.end());
    int l = 0, r = 0, t = 0;
    for (const auto &entry : order) {
        const auto &q = queries[entry.second];
        while (t < q.t) apply(t++, l, r);
        while (q.t < t) undo(--t, l, r);
        while (q.l < l) add_left(--l);
        while (r < q.r) add_right(r++);
        while (l < q.l) erase_left(l++);
        while (q.r < r) erase_right(--r);
        output(q.no);
    }
}

#endif

/**
 * @brief 1点更新付きMo
 */
