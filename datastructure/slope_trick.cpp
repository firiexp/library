template<class T>
struct SlopeTrick {
    static constexpr T INF = numeric_limits<T>::max() / 4;
    static constexpr bool raw_eval_cache = is_integral<T>::value && sizeof(T) <= 8;
    using EvalSum = conditional_t<raw_eval_cache, __int128, T>;

    T min_f = 0;
    priority_queue<T> L;
    priority_queue<T, vector<T>, greater<T>> R;
    T add_l = 0, add_r = 0;
    mutable bool eval_cache_valid = false;
    mutable vector<T> eval_l, eval_r;
    mutable vector<EvalSum> eval_l_sum, eval_r_sum;

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
    template<class Q>
    struct HeapAccess : Q {
        static const vector<T> &values(const Q &q) { return q.*&HeapAccess::c; }
    };
    void build_eval_cache() const {
        eval_l = HeapAccess<decltype(L)>::values(L);
        eval_r = HeapAccess<decltype(R)>::values(R);
        sort(eval_l.begin(), eval_l.end());
        sort(eval_r.begin(), eval_r.end());
        if constexpr (!raw_eval_cache) {
            for (T &x : eval_l) x += add_l;
            for (T &x : eval_r) x += add_r;
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
        invalidate_eval_cache();
        if (!L.empty() && a < top_L()) {
            min_f += top_L() - a;
            push_L(a);
            push_L(a);
            push_R(pop_L());
        } else if (!R.empty() && top_R() < a) {
            min_f += a - top_R();
            push_R(a);
            push_R(a);
            push_L(pop_R());
        } else {
            push_L(a);
            push_R(a);
        }
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
        if constexpr (!raw_eval_cache) invalidate_eval_cache();
    }

    void shift(T a) {
        shift(a, a);
    }

    T eval(T x) const {
        if (!eval_cache_valid) build_eval_cache();
        EvalSum lx = x, rx = x;
        if constexpr (raw_eval_cache) {
            lx -= static_cast<EvalSum>(add_l);
            rx -= static_cast<EvalSum>(add_r);
        }
        EvalSum res = min_f;
        int li = upper_bound(eval_l.begin(), eval_l.end(), lx) - eval_l.begin();
        res += eval_l_sum.back() - eval_l_sum[li] - lx * static_cast<EvalSum>(eval_l.size() - li);
        int ri = lower_bound(eval_r.begin(), eval_r.end(), rx) - eval_r.begin();
        res += rx * static_cast<EvalSum>(ri) - eval_r_sum[ri];
        return static_cast<T>(res);
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
