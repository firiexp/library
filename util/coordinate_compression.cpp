#ifndef FIRIEXP_LIBRARY_UTIL_COORDINATE_COMPRESSION_CPP
#define FIRIEXP_LIBRARY_UTIL_COORDINATE_COMPRESSION_CPP

template<class T>
class CoordinateCompression {
    static_assert(is_integral<T>::value && !is_same<T, bool>::value && sizeof(T) <= 8);
    vector<T> values_;

    static uint64_t key(T x) {
        uint64_t result = static_cast<uint64_t>(x);
        if constexpr (is_signed<T>::value) result ^= uint64_t(1) << 63;
        return result;
    }

    void sort_values() {
        if (values_.size() < 8192) {
            sort(values_.begin(), values_.end());
            return;
        }
        if (is_sorted(values_.begin(), values_.end())) return;
        auto [lo, hi] = minmax_element(values_.begin(), values_.end());
        uint64_t minimum = key(*lo), span = key(*hi) - minimum;
        int bucket_count = span < 65536 ? (int)span + 1 : 65536;
        vector<T> buffer(values_.size());
        vector<int> count(bucket_count);
        for (int shift = 0; span; shift += 16, span >>= 16) {
            fill(count.begin(), count.end(), 0);
            auto digit = [&](T x) {
                return ((key(x) - minimum) >> shift) & 65535;
            };
            for (T x : values_) ++count[digit(x)];
            int offset = 0;
            for (int& c : count) {
                int frequency = c;
                c = offset;
                offset += frequency;
            }
            for (T x : values_) buffer[count[digit(x)]++] = x;
            values_.swap(buffer);
        }
    }

    static pair<int, int> make_range(int l, int r) {
        return {l, max(l, r)};
    }

public:
    explicit CoordinateCompression(vector<T> values) : values_(move(values)) {
        sort_values();
        values_.erase(unique(values_.begin(), values_.end()), values_.end());
    }

    int size() const { return (int)values_.size(); }

    int index(const T& x) const {
        int i = lower_bound(x);
        return i < size() && values_[i] == x ? i : -1;
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
