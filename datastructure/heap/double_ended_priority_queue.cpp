#ifndef FIRIEXP_LIBRARY_DOUBLE_ENDED_PRIORITY_QUEUE_CPP
#define FIRIEXP_LIBRARY_DOUBLE_ENDED_PRIORITY_QUEUE_CPP

template<class T>
class DoubleEndedPriorityQueue {
    std::vector<T> heap;

    std::size_t endpoint(std::size_t node, bool upper) const {
        std::size_t low = 2 * node;
        return low + (upper && low + 1 < size());
    }

    bool order_pair(std::size_t node) {
        std::size_t low = 2 * node;
        if (low + 1 == size() || !(heap[low + 1] < heap[low])) return false;
        std::iter_swap(heap.begin() + low, heap.begin() + low + 1);
        return true;
    }

    bool precedes(std::size_t a, std::size_t b, bool upper) const {
        return upper ? heap[b] < heap[a] : heap[a] < heap[b];
    }

    void sift_down(std::size_t node, bool upper) {
        const std::size_t nodes = (size() + 1) / 2;
        while (node < nodes / 2) {
            std::size_t child = 2 * node + 1;
            std::size_t next = endpoint(child, upper);
            if (child + 1 < nodes) {
                std::size_t sibling = endpoint(child + 1, upper);
                if (precedes(sibling, next, upper)) next = sibling;
            }
            std::size_t current = endpoint(node, upper);
            if (!precedes(next, current, upper)) break;
            std::iter_swap(heap.begin() + current, heap.begin() + next);
            node = next / 2;
            order_pair(node);
        }
    }

    T pop_end(bool upper) {
        assert(!empty());
        std::size_t i = endpoint(0, upper);
        T result = std::move(heap[i]);
        if (i + 1 < size()) heap[i] = std::move(heap.back());
        heap.pop_back();
        sift_down(0, upper);
        return result;
    }

public:
    using const_reference = typename std::vector<T>::const_reference;

    DoubleEndedPriorityQueue() = default;

    explicit DoubleEndedPriorityQueue(std::vector<T> values) : heap(std::move(values)) {
        for (std::size_t node = (size() + 1) / 2; node > 0; ) {
            --node;
            order_pair(node);
            sift_down(node, false);
            sift_down(node, true);
        }
    }

    bool empty() const { return heap.empty(); }
    std::size_t size() const { return heap.size(); }
    void reserve(std::size_t capacity) { heap.reserve(capacity); }

    const_reference min() const {
        assert(!empty());
        return heap.front();
    }

    const_reference max() const {
        assert(!empty());
        return heap[endpoint(0, true)];
    }

    void push(T value) {
        heap.push_back(std::move(value));
        std::size_t i = size() - 1;
        if (order_pair(i / 2)) --i;
        while (i >= 2) {
            std::size_t parent = 2 * ((i / 2 - 1) / 2);
            if (heap[parent + 1] < heap[i]) ++parent;
            else if (!(heap[i] < heap[parent])) break;
            std::iter_swap(heap.begin() + i, heap.begin() + parent);
            i = parent;
        }
    }

    T pop_min() { return pop_end(false); }
    T pop_max() { return pop_end(true); }
};

#endif

/**
 * @brief 両端優先度付きキュー
 */
