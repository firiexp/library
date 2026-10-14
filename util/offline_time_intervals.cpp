#ifndef FIRIEXP_LIBRARY_UTIL_OFFLINE_TIME_INTERVALS_CPP
#define FIRIEXP_LIBRARY_UTIL_OFFLINE_TIME_INTERVALS_CPP

class OfflineTimeIntervals {
    struct Interval {
        int l, r, id;
    };
    int q;
    vector<Interval> intervals;

public:
    explicit OfflineTimeIntervals(int q) : q(q) { assert(q >= 0); }

    void add_interval(int l, int r, int event_id) {
        assert(0 <= l && l <= r && r <= q);
        if (l < r) intervals.push_back({l, r, event_id});
    }

    template<class Snapshot, class Apply, class Rollback, class Answer>
    void run(Snapshot snapshot, Apply apply, Rollback rollback, Answer answer) const {
        if (q == 0) return;
        size_t size = 1;
        while (size < (size_t)q) size *= 2;
        auto decompose = [&](const Interval &interval, auto visit) {
            size_t l = size + interval.l, r = size + interval.r;
            while (l < r) {
                if (l & 1) visit(l++);
                if (r & 1) visit(--r);
                l /= 2;
                r /= 2;
            }
        };
        vector<size_t> offset(2 * size + 1);
        for (const auto &interval : intervals) {
            decompose(interval, [&](size_t node) { ++offset[node + 1]; });
        }
        for (size_t i = 1; i < offset.size(); ++i) offset[i] += offset[i - 1];
        vector<int> events(offset.back());
        {
            auto cursor = offset;
            for (const auto &interval : intervals) {
                decompose(interval, [&](size_t node) { events[cursor[node]++] = interval.id; });
            }
        }
        auto dfs = [&](auto &&self, size_t node, size_t l, size_t r) -> void {
            if (l >= (size_t)q) return;
            auto state = snapshot();
            for (size_t i = offset[node]; i < offset[node + 1]; ++i) apply(events[i]);
            if (r - l == 1) answer((int)l);
            else {
                size_t mid = l + (r - l) / 2;
                self(self, node * 2, l, mid);
                self(self, node * 2 + 1, mid, r);
            }
            rollback(state);
        };
        dfs(dfs, 1, 0, size);
    }
};

#endif

/**
 * @brief 追加・削除クエリのオフライン処理
 */
