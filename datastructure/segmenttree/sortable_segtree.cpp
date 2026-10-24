#include "segtree.cpp"

template<class M>
class SortableSegmentTree {
public:
    using T = typename M::T;
    struct NodeStats {
        size_t allocations, releases, live, peak_live, slots;
    };

private:
    struct Node {
        int left, right, count;
        T forward, backward;
    };
    int n, free_head = 0;
    uint32_t upper;
    vector<Node> nodes;
    vector<int> roots;
    vector<bool> descending;
    std::set<int> starts;
    SegmentTree<M> outer;
    size_t allocations = 0, releases = 0, peak_live = 0;

    int allocate(Node node) {
        int id;
        if (free_head) {
            id = free_head;
            free_head = nodes[id].left;
            nodes[id] = move(node);
        } else {
            id = nodes.size();
            nodes.push_back(move(node));
        }
        ++allocations;
        peak_live = max(peak_live, allocations - releases);
        return id;
    }

    void release(int id) {
        nodes[id] = {free_head, 0, 0, M::e(), M::e()};
        free_head = id;
        ++releases;
    }

    void pull(int id) {
        int l = nodes[id].left, r = nodes[id].right;
        nodes[id].count = nodes[l].count + nodes[r].count;
        nodes[id].forward = M::f(nodes[l].forward, nodes[r].forward);
        nodes[id].backward = M::f(nodes[r].backward, nodes[l].backward);
    }

    int singleton(uint32_t key, const T &value, uint32_t l, uint32_t r) {
        int id = allocate({0, 0, 1, value, value});
        if (r - l == 1) return id;
        uint32_t mid = l + (r - l) / 2;
        if (key < mid) {
            int child = singleton(key, value, l, mid);
            nodes[id].left = child;
        } else {
            int child = singleton(key, value, mid, r);
            nodes[id].right = child;
        }
        return id;
    }

    pair<int, int> split(int id, int count) {
        if (count == 0) return {0, id};
        if (count == nodes[id].count) return {id, 0};
        int other = allocate({0, 0, 0, M::e(), M::e()});
        int l = nodes[id].left, r = nodes[id].right;
        int left_count = nodes[l].count;
        if (count < left_count) {
            auto parts = split(l, count);
            nodes[id].left = parts.first;
            nodes[id].right = 0;
            nodes[other].left = parts.second;
            nodes[other].right = r;
        } else if (count == left_count) {
            nodes[id].right = 0;
            nodes[other].right = r;
        } else {
            auto parts = split(r, count - left_count);
            nodes[id].right = parts.first;
            nodes[other].right = parts.second;
        }
        pull(id);
        pull(other);
        return {id, other};
    }

    int meld(int a, int b) {
        if (!a || !b) return a ? a : b;
        nodes[a].left = meld(nodes[a].left, nodes[b].left);
        nodes[a].right = meld(nodes[a].right, nodes[b].right);
        release(b);
        pull(a);
        return a;
    }

    T product(int start) const {
        const auto &node = nodes[roots[start]];
        return descending[start] ? node.backward : node.forward;
    }

    std::set<int>::iterator cut(int position) {
        auto next = starts.lower_bound(position);
        if (*next == position) return next;
        int start = *prev(next);
        int offset = position - start;
        int count = descending[start] ? nodes[roots[start]].count - offset : offset;
        auto parts = split(roots[start], count);
        if (descending[start]) swap(parts.first, parts.second);
        roots[start] = parts.first;
        roots[position] = parts.second;
        descending[position] = descending[start];
        outer.update(start, product(start));
        outer.update(position, product(position));
        return starts.insert(next, position);
    }

    void sort_range(int l, int r, bool reverse) {
        if (l == r) return;
        auto end = cut(r), begin = cut(l);
        int root = roots[l];
        for (auto it = next(begin); it != end;) {
            int start = *it;
            root = meld(root, roots[start]);
            roots[start] = 0;
            outer.update(start, M::e());
            it = starts.erase(it);
        }
        roots[l] = root;
        descending[l] = reverse;
        outer.update(l, product(l));
    }

public:
    SortableSegmentTree(const vector<int> &keys, const vector<T> &values,
                        uint64_t key_upper = uint64_t(1) << 31)
        : n(keys.size()), upper(key_upper), roots(n), descending(n), outer(n) {
        int height = 0;
        for (uint64_t width = 1; width < key_upper; width <<= 1) ++height;
        nodes.reserve(size_t(n) * (height + 1) + 1);
        nodes.push_back({0, 0, 0, M::e(), M::e()});
        for (int i = 0; i < n; ++i) {
            assert(keys[i] >= 0 && uint64_t(keys[i]) < key_upper);
            roots[i] = singleton(keys[i], values[i], 0, upper);
            starts.insert(starts.end(), i);
            outer.set(i, values[i]);
        }
        starts.insert(starts.end(), n);
        outer.build();
    }

    int size() const { return n; }

    pair<int, T> get(int position) const {
        assert(0 <= position && position < n);
        int start = *prev(starts.upper_bound(position));
        int id = roots[start], rank = position - start;
        if (descending[start]) rank = nodes[id].count - 1 - rank;
        uint32_t l = 0, r = upper;
        while (r - l > 1) {
            int child = nodes[id].left;
            uint32_t mid = l + (r - l) / 2;
            if (rank < nodes[child].count) {
                id = child;
                r = mid;
            } else {
                rank -= nodes[child].count;
                id = nodes[id].right;
                l = mid;
            }
        }
        return {int(l), nodes[id].forward};
    }

    void set(int position, int key, const T &value) {
        cut(position);
        cut(position + 1);
        int id = roots[position];
        while (id) {
            int child = nodes[id].left ? nodes[id].left : nodes[id].right;
            release(id);
            id = child;
        }
        roots[position] = singleton(key, value, 0, upper);
        descending[position] = false;
        outer.update(position, value);
    }

    void sort_ascending(int l, int r) { sort_range(l, r, false); }
    void sort_descending(int l, int r) { sort_range(l, r, true); }

    T fold(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::e();
        cut(l);
        cut(r);
        return outer.query(l, r);
    }

    NodeStats node_stats() const {
        return {allocations, releases, allocations - releases, peak_live, nodes.size() - 1};
    }
};

/**
 * @brief 区間ソートと区間積
 */
