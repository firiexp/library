template<class T, bool get_max>
class CHT {
    using P = pair<T, T>;
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

    void add_line(T a, T b) { // add ax + b
        if(get_max) a = -a, b = -b;
        P L(a, b);
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

    T val(const P &L, const T &x) { return L.first * x + L.second; }
    T query(T x){
        int l = -1, r = lines.size() - 1;
        while(r - l > 1){
            int mid = (l+r) >> 1;
            if(val(lines[mid], x) >= val(lines[mid+1], x)) l = mid;
            else r = mid;
        }
        return get_max ? -val(lines[r], x) : val(lines[r], x);
    }

    T query_increase(T x){
        while(lines.size() >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();
        return get_max ? -val(lines.front(), x) : val(lines.front(), x);
    }

    T query_decrease(T x){
        while(lines.size() >= 2 && val(lines.back(), x) >= val(lines[lines.size() - 2], x)) lines.pop_back();
        return get_max ? -val(lines.back(), x) : val(lines.back(), x);
    }
};
