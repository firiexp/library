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
    vector<Query> qs = queries;
    sort(qs.begin(), qs.end(), [&](const Query& a, const Query& b) {
        int ablock = a.l / bucket_size, bblock = b.l / bucket_size;
        if (ablock != bblock) return ablock < bblock;
        return ablock & 1 ? a.r < b.r : a.r > b.r;
    });
    int l = 0, r = 0;
    for (const auto& q : qs) {
        while (q.l < l) add_left(--l);
        while (r < q.r) add_right(r++);
        while (l < q.l) erase_left(l++);
        while (q.r < r) erase_right(--r);
        output(q.no);
    }
}

/**
 * @brief Mo's Algorithm
 */
