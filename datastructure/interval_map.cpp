#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_INTERVAL_MAP_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_INTERVAL_MAP_CPP

template<class T>
class IntervalMap {
    long long n;
    map<long long, T> runs;
    using Iterator = typename map<long long, T>::iterator;

    Iterator split(long long position) {
        if (position == n) return runs.end();
        auto it = prev(runs.upper_bound(position));
        if (it->first == position) return it;
        return runs.emplace_hint(next(it), position, it->second);
    }

public:
    IntervalMap(long long n, const T &value) : n(n) {
        assert(n >= 0);
        if (n > 0) runs.emplace(0, value);
    }

    explicit IntervalMap(const vector<T> &values) : n(values.size()) {
        for (long long i = 0; i < n; ++i) {
            if (i == 0 || !(values[i - 1] == values[i])) {
                runs.emplace_hint(runs.end(), i, values[i]);
            }
        }
    }

    T get(long long position) const {
        assert(0 <= position && position < n);
        return prev(runs.upper_bound(position))->second;
    }

    template<class Callback>
    void for_each_interval(long long l, long long r, Callback callback) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        auto it = prev(runs.upper_bound(l));
        while (l < r) {
            auto following = next(it);
            long long end = following == runs.end() ? r : min(r, following->first);
            callback(l, end, it->second);
            l = end;
            it = following;
        }
    }

    template<class Callback>
    void assign(long long l, long long r, T value, Callback callback) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        auto last = split(r), first = split(l);
        for (auto it = first; it != last; ++it) {
            auto following = next(it);
            callback(it->first, following == runs.end() ? n : following->first,
                     static_cast<const T &>(it->second));
        }
        runs.erase(first, last);
        auto it = runs.emplace_hint(last, l, std::move(value));
        if (it != runs.begin() && prev(it)->second == it->second) {
            auto previous = prev(it);
            runs.erase(it);
            it = previous;
        }
        auto following = next(it);
        if (following != runs.end() && following->second == it->second) runs.erase(following);
    }

    void assign(long long l, long long r, T value) {
        assign(l, r, std::move(value), [](long long, long long, const T &) {});
    }
};

#endif

/**
 * @brief Interval Map
 */
