template<class T, class F = less<T>>
class monotonic_queue {
    deque<int> indices;
    deque<pair<int, T>> candidates;
    optional<int> last_index;
    F compare;
public:
    explicit monotonic_queue(F compare = F{}) : compare(std::move(compare)) {}

    bool empty() const {
        return indices.empty();
    }

    const pair<int, T>& front() const {
        assert(!empty());
        return candidates.front();
    }

    void push(int index, T value) {
        assert(!last_index || *last_index < index);
        while (!candidates.empty() && !compare(candidates.back().second, value))
            candidates.pop_back();
        candidates.emplace_back(index, std::move(value));
        indices.push_back(index);
        last_index = index;
    }

    void push(T value) {
        assert(!last_index || *last_index < numeric_limits<int>::max());
        push(last_index.value_or(-1) + 1, std::move(value));
    }

    void pop() {
        assert(!empty());
        if (indices.front() == candidates.front().first) candidates.pop_front();
        indices.pop_front();
    }

    void pop_until(int min_index) {
        while (!empty() && indices.front() < min_index) pop();
    }
};

template<class T, class F>
class sliding_window {
    vector<T> v;
    deque<int> Q;
    F f;
public:
    int l, r;
    explicit sliding_window(const vector<T>& v, F f) : v(v), f(f), l(0), r(0) {}
    void set(const vector<T>& u) {
        v = u;
        reset();
    }
    void reset(){
        Q.clear();
        l = 0, r = 0;
    }
    void slideL(){
        if(Q.front() == l++) Q.pop_front();
    }
    void slideR(){
        while(!Q.empty() && !f(v[Q.back()], v[r])) Q.pop_back();
        Q.push_back(r++);
    }
    int get_index() const {
        if(l == r) return 0;
        return Q.front();
    }
    T value() const {
        if constexpr (is_convertible_v<int, T> || is_convertible_v<nullptr_t, T>) {
            if (l == r) return 0;
        }
        assert(l < r);
        return v[Q.front()];
    }
};

/**
 * @brief スライド最小値(最大値)
 */
