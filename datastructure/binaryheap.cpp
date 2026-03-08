template<typename T>
struct binary_heap {
    ll S;
    vector<T> Q;
    binary_heap() : S(0), Q() {}

    T top() const { return Q.front(); }
    size_t size() const { return Q.size(); }
    void pop() {
        pop_heap(Q.begin(),Q.end());
        S -= Q.back();
        Q.pop_back();
    }
    void emplace(T x) {
        S += x;
        Q.emplace_back(x);
        push_heap(Q.begin(),Q.end());
    }
    bool empty() { return Q.empty(); }
    ll sum() const { return S; }
};

/**
 * @brief 二分ヒープ(Binary Heap)
 * @docs _md/binaryheap.md
 */
