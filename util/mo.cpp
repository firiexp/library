#ifndef FIRIEXP_LIBRARY_UTIL_MO_CPP
#define FIRIEXP_LIBRARY_UTIL_MO_CPP

struct Query {
    static inline int bucket_size = 1;
    static inline int &B = bucket_size;
    int l, r, no;
    Query(int l, int r, int no) : l(l), r(r), no(no) {}
    Query() : l(0), r(0), no(0) {}
    bool operator<(const Query &a) const {
        int ablock = this->l / bucket_size, bblock = a.l / bucket_size;
        if(ablock != bblock) return ablock < bblock;
        if(ablock & 1) return this->r < a.r;
        else return this->r > a.r;
    }
};

template<class AddLeft, class AddRight, class EraseLeft, class EraseRight, class Output>
void mo_solve(int n, const vector<Query>& queries, AddLeft add_left, AddRight add_right,
              EraseLeft erase_left, EraseRight erase_right, Output output, int bucket_size = 0) {
    if (queries.empty()) return;
    if (bucket_size <= 0) bucket_size = max(1, (int)(n / sqrt((double)queries.size())));
    struct OrderedQuery {
        uint64_t key;
        size_t index;
    };
    vector<OrderedQuery> qs;
    qs.reserve(queries.size());
    for (size_t i = 0; i < queries.size(); ++i) {
        uint32_t block = queries[i].l / bucket_size;
        uint32_t right = queries[i].r;
        if (!(block & 1)) right = ~right;
        qs.push_back({(uint64_t(block) << 32) | right, i});
    }
    sort(qs.begin(), qs.end(), [](const OrderedQuery& a, const OrderedQuery& b) {
        return a.key < b.key;
    });
    int l = 0, r = 0;
    for (const auto& ordered : qs) {
        const auto& q = queries[ordered.index];
        while (q.l < l) add_left(--l);
        while (r < q.r) add_right(r++);
        while (l < q.l) erase_left(l++);
        while (q.r < r) erase_right(--r);
        output(q.no);
    }
}

#endif

/**
 * @brief Mo's Algorithm
 */
