template<class T, class SumT = long long>
class IntervalSet {
public:
    struct Interval {
        T l, r;
    };

private:
    struct Compare {
        using is_transparent = void;

        bool operator()(const Interval& a, const Interval& b) const {
            return a.l < b.l;
        }
        bool operator()(const Interval& a, const T& x) const {
            return a.l < x;
        }
        bool operator()(const T& x, const Interval& a) const {
            return x < a.l;
        }
    };

    set<Interval, Compare> st_;
    SumT total_ = 0;

    static SumT seg_len(const Interval& seg) {
        return static_cast<SumT>(seg.r) - static_cast<SumT>(seg.l);
    }

    typename set<Interval, Compare>::const_iterator find_interval_it(T x) const {
        auto it = st_.upper_bound(x);
        if (it == st_.begin()) return st_.end();
        --it;
        if (it->l <= x && x < it->r) return it;
        return st_.end();
    }

public:
    using const_iterator = typename set<Interval, Compare>::const_iterator;

    IntervalSet() = default;

    bool empty() const {
        return st_.empty();
    }

    int size() const {
        return (int)st_.size();
    }

    SumT total_length() const {
        return total_;
    }

    const_iterator begin() const {
        return st_.begin();
    }

    const_iterator end() const {
        return st_.end();
    }

    vector<Interval> intervals() const {
        return vector<Interval>(st_.begin(), st_.end());
    }

    bool contains(T x) const {
        return find_interval_it(x) != st_.end();
    }

    Interval find_interval(T x) const {
        auto it = find_interval_it(x);
        if (it == st_.end()) return {-1, -1};
        return *it;
    }

    Interval insert(T l, T r) {
        if (!(l < r)) return {l, l};

        auto it = st_.lower_bound(l);

        if (it != st_.begin()) {
            auto pit = prev(it);
            if (pit->r >= l) {
                l = min(l, pit->l);
                r = max(r, pit->r);
                total_ -= seg_len(*pit);
                it = st_.erase(pit);
            }
        }

        while (it != st_.end() && it->l <= r) {
            r = max(r, it->r);
            total_ -= seg_len(*it);
            it = st_.erase(it);
        }

        auto new_it = st_.insert(it, {l, r});
        total_ += static_cast<SumT>(r) - static_cast<SumT>(l);
        return *new_it;
    }

    SumT erase(T l, T r) {
        if (!(l < r)) return 0;

        SumT removed = 0;
        vector<Interval> add_back;

        auto it = st_.lower_bound(l);
        if (it != st_.begin()) --it;

        while (it != st_.end() && it->l < r) {
            if (it->r <= l) {
                ++it;
                continue;
            }

            Interval cur = *it;
            it = st_.erase(it);
            total_ -= seg_len(cur);

            T a = max(cur.l, l);
            T b = min(cur.r, r);
            removed += static_cast<SumT>(b) - static_cast<SumT>(a);

            if (cur.l < l) add_back.push_back({cur.l, l});
            if (r < cur.r) add_back.push_back({r, cur.r});
        }

        for (const auto& seg : add_back) {
            st_.insert(seg);
            total_ += seg_len(seg);
        }

        return removed;
    }

    SumT covered_length(T l, T r) const {
        if (!(l < r)) return 0;

        SumT res = 0;
        auto it = st_.lower_bound(l);
        if (it != st_.begin()) --it;

        while (it != st_.end() && it->l < r) {
            if (l < it->r) {
                T a = max(l, it->l);
                T b = min(r, it->r);
                if (a < b) {
                    res += static_cast<SumT>(b) - static_cast<SumT>(a);
                }
            }
            ++it;
        }
        return res;
    }

    T mex(T x) const {
        auto it = find_interval_it(x);
        if (it == st_.end()) return x;
        return it->r;
    }

    void clear() {
        st_.clear();
        total_ = 0;
    }

    Interval prev_interval(T x) const {
        auto it = st_.upper_bound(x);
        if (it == st_.begin()) return {-1, -1};
        --it;
        return *it;
    }

    Interval next_interval(T x) const {
        auto fit = find_interval_it(x);
        if (fit != st_.end()) return *fit;

        auto it = st_.lower_bound(x);
        if (it == st_.end()) return {-1, -1};
        return *it;
    }
};

/**
 * @brief 区間集合(Interval Set)
 */
