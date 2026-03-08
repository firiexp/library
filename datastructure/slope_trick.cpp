template<class T>
struct SlopeTrick {
    static constexpr T INF = numeric_limits<T>::max() / 4;

    T min_f = 0;
    priority_queue<T> L;
    priority_queue<T, vector<T>, greater<T>> R;
    T add_l = 0, add_r = 0;

    struct Query {
        T lx, rx, min_f;
    };

private:
    void push_L(T a) { L.push(a - add_l); }
    void push_R(T a) { R.push(a - add_r); }
    T top_L() const { return L.empty() ? -INF : L.top() + add_l; }
    T top_R() const { return R.empty() ? INF : R.top() + add_r; }
    T pop_L() {
        T x = top_L();
        if (!L.empty()) L.pop();
        return x;
    }
    T pop_R() {
        T x = top_R();
        if (!R.empty()) R.pop();
        return x;
    }
    size_t size() const { return L.size() + R.size(); }

public:
    Query query() const {
        return {top_L(), top_R(), min_f};
    }

    void add_all(T a) {
        min_f += a;
    }

    void add_a_minus_x(T a) {
        min_f += max<T>(0, a - top_R());
        push_R(a);
        push_L(pop_R());
    }

    void add_x_minus_a(T a) {
        min_f += max<T>(0, top_L() - a);
        push_L(a);
        push_R(pop_L());
    }

    void add_abs(T a) {
        add_a_minus_x(a);
        add_x_minus_a(a);
    }

    void clear_right() {
        decltype(R){}.swap(R);
    }

    void clear_left() {
        decltype(L){}.swap(L);
    }

    void shift(T a, T b) {
        assert(a <= b);
        add_l += a;
        add_r += b;
    }

    void shift(T a) {
        shift(a, a);
    }

    T eval(T x) const {
        T res = min_f;
        auto lq = L;
        auto rq = R;
        while (!lq.empty()) {
            res += max<T>(0, lq.top() + add_l - x);
            lq.pop();
        }
        while (!rq.empty()) {
            res += max<T>(0, x - (rq.top() + add_r));
            rq.pop();
        }
        return res;
    }

    void merge(SlopeTrick &st) {
        if (st.size() > size()) swap(*this, st);
        while (!st.L.empty()) add_a_minus_x(st.pop_L());
        while (!st.R.empty()) add_x_minus_a(st.pop_R());
        min_f += st.min_f;
    }
};

/**
 * @brief Slope Trick
 */
