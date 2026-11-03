template<class T, bool get_max, bool store_id = false>
class CHT {
    struct LineWithId {
        T first, second;
        int id = -1;
    };
    using P = conditional_t<store_id, LineWithId, pair<T, T>>;
    deque<P> lines;
public:
    CHT() = default;
    bool check(P l1, P l2, P l3){
        if constexpr (is_integral_v<T>) {
            return (((__int128)l2.second - l1.second) * ((__int128)l2.first - l3.first)
                 >= ((__int128)l3.second - l2.second) * ((__int128)l1.first - l2.first));
        } else {
            return ((static_cast<long double>(l2.second) - l1.second) * (static_cast<long double>(l2.first) - l3.first)
                 >= (static_cast<long double>(l3.second) - l2.second) * (static_cast<long double>(l1.first) - l2.first));
        }
    }

    void add_line(T a, T b, int id = -1) {
        if(get_max) a = -a, b = -b;
        P L{a, b};
        if constexpr (store_id) L.id = id;
        if(lines.empty()){
            lines.emplace_back(L);
            return;
        }
        if(lines.front().first <= a){
            if(lines.front().first == a){
                if(lines.front().second <= b) return;
                else lines.pop_front();
            }
            while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();
            lines.emplace_front(L);
        }else {
            if(lines.back().first == a){
                if(lines.back().second <= b) return;
                else lines.pop_back();
            }
            while(lines.size() >= 2 && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();
            lines.emplace_back(L);
        }
    }

    T val(const P &L, const T &x) const { return L.first * x + L.second; }
private:
    template<bool with_id>
    auto result(const P &line, T x) const {
        T value = get_max ? -val(line, x) : val(line, x);
        if constexpr (with_id) {
            static_assert(store_id, "ID queries require store_id = true");
            return pair<T, int>{value, line.id};
        } else {
            return value;
        }
    }

    template<bool with_id>
    auto query_impl(T x) const {
        assert(!lines.empty());
        int l = -1, r = lines.size() - 1;
        while(r - l > 1){
            int mid = (l+r) >> 1;
            if(val(lines[mid], x) >= val(lines[mid+1], x)) l = mid;
            else r = mid;
        }
        return result<with_id>(lines[r], x);
    }

    template<bool with_id>
    auto query_increase_impl(T x){
        assert(!lines.empty());
        while(lines.size() >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();
        return result<with_id>(lines.front(), x);
    }

    template<bool with_id>
    auto query_decrease_impl(T x){
        assert(!lines.empty());
        while(lines.size() >= 2 && val(lines.back(), x) >= val(lines[lines.size() - 2], x)) lines.pop_back();
        return result<with_id>(lines.back(), x);
    }

public:
    T query(T x) const { return query_impl<false>(x); }
    T query_increase(T x) { return query_increase_impl<false>(x); }
    T query_decrease(T x) { return query_decrease_impl<false>(x); }
    pair<T, int> query_with_id(T x) const { return query_impl<true>(x); }
    pair<T, int> query_increase_with_id(T x) { return query_increase_impl<true>(x); }
    pair<T, int> query_decrease_with_id(T x) { return query_decrease_impl<true>(x); }
};
