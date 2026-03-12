template<class T>
struct SlopeTrick {
    static constexpr T INF = numeric_limits<T>::max() / 4;

    T min_f = 0;
    priority_queue<T> L;
    priority_queue<T, vector<T>, greater<T>> R;
    T add_l = 0, add_r = 0;
    mutable bool eval_cache_valid = false;
    mutable vector<T> eval_l, eval_r;
    mutable vector<T> eval_l_sum, eval_r_sum;

    struct Query {
        T lx, rx, min_f;
    };

private:
    void push_L(T a) { L.push(a - add_l); }
    void push_R(T a) { R.push(a - add_r); }
    T top_L() const { return L.empty() ? -INF : L.top() + add_l; }
    T top_R() const { return R.empty() ? INF : R.top() + add_r; }
    T pop_L() {
        invalidate_eval_cache();
        T x = top_L();
        if (!L.empty()) L.pop();
        return x;
    }
    T pop_R() {
        invalidate_eval_cache();
        T x = top_R();
        if (!R.empty()) R.pop();
        return x;
    }
    size_t size() const { return L.size() + R.size(); }
    void invalidate_eval_cache() {
        eval_cache_valid = false;
    }
    void build_eval_cache() const {
        if (eval_cache_valid) return;

        auto lq = L;
        auto rq = R;
        eval_l.clear();
        eval_r.clear();
        eval_l.reserve(lq.size());
        eval_r.reserve(rq.size());
        while (!lq.empty()) {
            eval_l.emplace_back(lq.top() + add_l);
            lq.pop();
        }
        reverse(eval_l.begin(), eval_l.end());
        while (!rq.empty()) {
            eval_r.emplace_back(rq.top() + add_r);
            rq.pop();
        }

        eval_l_sum.assign(eval_l.size() + 1, 0);
        for (int i = 0; i < (int)eval_l.size(); ++i) {
            eval_l_sum[i + 1] = eval_l_sum[i] + eval_l[i];
        }
        eval_r_sum.assign(eval_r.size() + 1, 0);
        for (int i = 0; i < (int)eval_r.size(); ++i) {
            eval_r_sum[i + 1] = eval_r_sum[i] + eval_r[i];
        }
        eval_cache_valid = true;
    }

public:
    Query query() const {
        return {top_L(), top_R(), min_f};
    }

    void add_all(T a) {
        min_f += a;
    }

    void add_a_minus_x(T a) {
        invalidate_eval_cache();
        min_f += max<T>(0, a - top_R());
        push_R(a);
        push_L(pop_R());
    }

    void add_x_minus_a(T a) {
        invalidate_eval_cache();
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
        invalidate_eval_cache();
    }

    void clear_left() {
        decltype(L){}.swap(L);
        invalidate_eval_cache();
    }

    void shift(T a, T b) {
        assert(a <= b);
        add_l += a;
        add_r += b;
        invalidate_eval_cache();
    }

    void shift(T a) {
        shift(a, a);
    }

    T eval(T x) const {
        build_eval_cache();
        T res = min_f;
        int li = upper_bound(eval_l.begin(), eval_l.end(), x) - eval_l.begin();
        res += eval_l_sum.back() - eval_l_sum[li] - x * static_cast<T>(eval_l.size() - li);
        int ri = lower_bound(eval_r.begin(), eval_r.end(), x) - eval_r.begin();
        res += x * static_cast<T>(ri) - eval_r_sum[ri];
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
