#include "dijkstra_common.cpp"
#include "../datastructure/radixheap.cpp"

struct DijkstraRadixHeapQueue {
    RadixHeap<long long, int> Q;

    bool empty() const { return Q.empty(); }

    void push(long long cost, int v) {
        Q.emplace(cost, v);
    }

    pair<long long, int> pop() {
        auto [cost, v] = Q.top();
        Q.pop();
        return {cost, v};
    }
};

vector<long long> dijkstra_radix_heap(int s, const vector<vector<edge<long long>>> &G) {
    DijkstraRadixHeapQueue Q;
    return dijkstra_internal(s, G, Q);
}

/**
 * @brief Dijkstra法(Radix Heap)
 */
