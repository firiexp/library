template<class T, class SumT = long long, bool Largest = true>
class TopKSum {
private:
    multiset<T> selected_;
    multiset<T> other_;
    int K_ = 0;
    int total_size_ = 0;
    SumT total_sum_ = 0;
    SumT selected_sum_ = 0;

    static bool selected_before(const T& a, const T& b) {
        if constexpr (Largest) return a > b;
        else return a < b;
    }

    typename multiset<T>::iterator selected_boundary() {
        assert(!selected_.empty());
        if constexpr (Largest) return selected_.begin();
        else return prev(selected_.end());
    }

    typename multiset<T>::const_iterator selected_boundary() const {
        assert(!selected_.empty());
        if constexpr (Largest) return selected_.begin();
        else return prev(selected_.end());
    }

    typename multiset<T>::iterator other_best() {
        assert(!other_.empty());
        if constexpr (Largest) return prev(other_.end());
        else return other_.begin();
    }

    void move_selected_to_other() {
        auto it = selected_boundary();
        T x = *it;
        selected_.erase(it);
        selected_sum_ -= (SumT)x;
        other_.insert(x);
    }

    void move_other_to_selected() {
        auto it = other_best();
        T x = *it;
        other_.erase(it);
        selected_.insert(x);
        selected_sum_ += (SumT)x;
    }

    void rebalance() {
        int target = min(K_, total_size_);
        while ((int)selected_.size() > target) move_selected_to_other();
        while ((int)selected_.size() < target) move_other_to_selected();
        while (!selected_.empty() && !other_.empty()) {
            auto sit = selected_boundary();
            auto oit = other_best();
            T s = *sit;
            T o = *oit;
            if (!selected_before(o, s)) break;
            selected_.erase(sit);
            other_.erase(oit);
            selected_.insert(o);
            other_.insert(s);
            selected_sum_ += (SumT)o - (SumT)s;
        }
    }

public:
    explicit TopKSum(int K = 0) : K_(K) {
        assert(K >= 0);
    }

    TopKSum(const TopKSum&) = delete;
    TopKSum& operator=(const TopKSum&) = delete;

    int k() const {
        return K_;
    }

    void set_k(int new_k) {
        assert(new_k >= 0);
        K_ = new_k;
        rebalance();
    }

    int size() const {
        return total_size_;
    }

    bool empty() const {
        return total_size_ == 0;
    }

    SumT total_sum() const {
        return total_sum_;
    }

    void insert(const T& x) {
        ++total_size_;
        total_sum_ += (SumT)x;
        if ((int)selected_.size() < K_) {
            selected_.insert(x);
            selected_sum_ += (SumT)x;
        } else if (selected_.empty()) {
            other_.insert(x);
        } else {
            T s = *selected_boundary();
            if (selected_before(x, s)) {
                selected_.insert(x);
                selected_sum_ += (SumT)x;
            } else {
                other_.insert(x);
            }
        }
        rebalance();
    }

    bool erase_one(const T& x) {
        auto it = selected_.find(x);
        if (it != selected_.end()) {
            selected_sum_ -= (SumT)x;
            selected_.erase(it);
        } else {
            it = other_.find(x);
            if (it == other_.end()) return false;
            other_.erase(it);
        }
        --total_size_;
        total_sum_ -= (SumT)x;
        rebalance();
        return true;
    }

    bool has_kth() const {
        return 1 <= K_ && K_ <= total_size_;
    }

    T kth() const {
        assert(has_kth());
        return *selected_boundary();
    }

    SumT sum_topk() const {
        return selected_sum_;
    }
};

/**
 * @brief 上位K和管理
 */
