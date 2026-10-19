template<class T>
class PersistentQueue {
    struct Node {
        T value;
        size_t offset;
    };
    struct Version {
        int tail, length;
    };

    vector<Node> nodes;
    vector<int> ancestors;
    vector<Version> versions{{-1, 0}};

public:
    int push(int version, const T &value) {
        assert(0 <= version && version < (int)versions.size());
        auto state = versions[version];
        int length = state.length + 1;
        size_t offset = ancestors.size();
        ancestors.push_back(state.tail);
        for (int bit = 1; (1LL << bit) < length; ++bit) {
            int half = ancestors[offset + bit - 1];
            ancestors.push_back(ancestors[nodes[half].offset + bit - 1]);
        }
        int id = (int)nodes.size();
        nodes.push_back({value, offset});
        versions.push_back({id, length});
        return (int)versions.size() - 1;
    }

    int pop(int version) {
        assert(!empty(version));
        auto state = versions[version];
        if (--state.length == 0) state.tail = -1;
        versions.push_back(state);
        return (int)versions.size() - 1;
    }

    T front(int version) const {
        return get(version, 0);
    }

    T get(int version, int k) const {
        int node = versions[version].tail;
        int distance = versions[version].length - 1 - k;
        for (int bit = 0; distance; ++bit, distance >>= 1)
            if (distance & 1) node = ancestors[nodes[node].offset + bit];
        return nodes[node].value;
    }

    T back(int version) const {
        return nodes[versions[version].tail].value;
    }

    int size(int version) const {
        assert(0 <= version && version < (int)versions.size());
        return versions[version].length;
    }

    bool empty(int version) const { return size(version) == 0; }
};

/**
 * @brief 永続キュー
 */
