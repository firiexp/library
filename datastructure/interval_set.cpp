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
            if (pit->r >= l) it = pit;
        }

        if (it != st_.end() && it->l <= l && r <= it->r) return *it;
        if (it == st_.end() || r < it->l) {
            total_ += static_cast<SumT>(r) - static_cast<SumT>(l);
            return *st_.insert(it, {l, r});
        }

        l = min(l, it->l);
        r = max(r, it->r);
        total_ -= seg_len(*it);
        auto node = st_.extract(it++);
        while (it != st_.end() && it->l <= r) {
            r = max(r, it->r);
            total_ -= seg_len(*it);
            it = st_.erase(it);
        }

        node.value() = {l, r};
        auto new_it = st_.insert(it, move(node));
        total_ += static_cast<SumT>(r) - static_cast<SumT>(l);
        return *new_it;
    }

    SumT erase(T l, T r) {
        if (!(l < r)) return 0;

        SumT removed = 0;

        auto it = st_.lower_bound(l);
        if (it != st_.begin()) --it;

        while (it != st_.end() && it->l < r) {
            if (it->r <= l) {
                ++it;
                continue;
            }

            Interval cur = *it;
            T a = max(cur.l, l);
            T b = min(cur.r, r);
            removed += static_cast<SumT>(b) - static_cast<SumT>(a);

            if (cur.l < l || r < cur.r) {
                auto node = st_.extract(it++);
                if (cur.l < l) {
                    node.value().r = l;
                    st_.insert(it, move(node));
                    if (r < cur.r) st_.insert(it, {r, cur.r});
                } else {
                    node.value().l = r;
                    st_.insert(it, move(node));
                }
            } else {
                it = st_.erase(it);
            }
        }

        total_ -= removed;
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
