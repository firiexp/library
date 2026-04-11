template <class T, size_t N>
struct NdVec {
    array<int, N> dim{};
    array<long long, N> stride{};
    vector<T> data;

    NdVec() = default;

    NdVec(array<int, N> dim_, const T &init = T()) : dim(dim_) {
        long long sz = 1;
        for (size_t i = 0; i < N; ++i) assert(dim[i] >= 0);
        for (size_t i = N; i-- > 0;) {
            stride[i] = sz;
            sz *= dim[i];
        }
        data.assign(sz, init);
    }

    long long size() const {
        return (long long)data.size();
    }

    template <class... Idx>
    long long index(Idx... idx) const {
        static_assert(sizeof...(Idx) == N);
        array<long long, N> id{static_cast<long long>(idx)...};
        long long p = 0;
        for (size_t i = 0; i < N; ++i) p += id[i] * stride[i];
        return p;
    }

    template <class... Idx>
    T &operator()(Idx... idx) {
        return data[index(idx...)];
    }

    template <class... Idx>
    const T &operator()(Idx... idx) const {
        return data[index(idx...)];
    }

    void fill(const T &value) {
        std::fill(data.begin(), data.end(), value);
    }
};

/**
 * @brief 多次元配列(NdVec)
 */
