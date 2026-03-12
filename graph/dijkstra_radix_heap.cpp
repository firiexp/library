#include "dijkstra_common.cpp"
#include "../datastructure/radixheap.cpp"

template <typename T>
struct DijkstraRadixHeapQueue {
    static_assert(numeric_limits<T>::is_integer, "dijkstra_radix_heap requires integer costs");
    static_assert(numeric_limits<T>::is_signed, "dijkstra_radix_heap requires signed integer costs");
    static_assert(sizeof(T) <= sizeof(ll), "dijkstra_radix_heap requires costs that fit in long long");

    RadixHeap<ll, int> Q;

    bool empty() const { return Q.empty(); }

    void push(T cost, int v) {
        Q.emplace((ll)cost, v);
    }

    pair<T, int> pop() {
        auto [cost, v] = Q.top();
        Q.pop();
        return {static_cast<T>(cost), v};
    }
};

template <typename T>
vector<T> dijkstra_radix_heap(int s, const vector<vector<edge<T>>> &G) {
    DijkstraRadixHeapQueue<T> Q;
    return dijkstra_internal(s, G, Q);
}

/**
 * @brief Dijkstra法(Radix Heap)
 */
