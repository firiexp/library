#ifndef FIRIEXP_LIBRARY_UTIL_COORDINATE_COMPRESSION_CPP
#define FIRIEXP_LIBRARY_UTIL_COORDINATE_COMPRESSION_CPP

template<class T>
class CoordinateCompression {
    static_assert(!is_same<T, bool>::value);
    vector<T> values_;

    static pair<int, int> make_range(int l, int r) {
        return {l, max(l, r)};
    }

public:
    explicit CoordinateCompression(vector<T> values) : values_(move(values)) {
        assert(values_.size() <= (size_t)numeric_limits<int>::max());
        sort(values_.begin(), values_.end());
        values_.erase(unique(values_.begin(), values_.end(), [](const T& a, const T& b) {
            return !(a < b) && !(b < a);
        }), values_.end());
    }

    int size() const { return (int)values_.size(); }

    int index(const T& x) const {
        int i = lower_bound(x);
        return i < size() && !(x < values_[i]) ? i : -1;
    }

    const T& value(int i) const {
        assert(0 <= i && i < size());
        return values_[i];
    }

    int lower_bound(const T& x) const {
        return (int)(std::lower_bound(values_.begin(), values_.end(), x) - values_.begin());
    }

    int upper_bound(const T& x) const {
        return (int)(std::upper_bound(values_.begin(), values_.end(), x) - values_.begin());
    }

    pair<int, int> range(const T& l, const T& r) const {
        return make_range(lower_bound(l), lower_bound(r));
    }

    pair<int, int> range_closed(const T& l, const T& r) const {
        return make_range(lower_bound(l), upper_bound(r));
    }

    pair<int, int> range_open(const T& l, const T& r) const {
        return make_range(upper_bound(l), lower_bound(r));
    }

    pair<int, int> range_open_closed(const T& l, const T& r) const {
        return make_range(upper_bound(l), upper_bound(r));
    }
};

#endif

/**
 * @brief 座標圧縮と区間変換
 */
