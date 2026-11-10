#include "order_statistic_tree.cpp"

template<class T>
class PointSetRangeFrequency {
    vector<T> values_;
    OrderStatisticTree<pair<T, int>> positions_;

    static vector<pair<T, int>> keys(const vector<T>& values) {
        vector<pair<T, int>> result;
        result.reserve(values.size());
        for (int i = 0; i < (int)values.size(); ++i) result.emplace_back(values[i], i);
        return result;
    }

public:
    explicit PointSetRangeFrequency(vector<T> values)
        : values_(move(values)), positions_(keys(values_)) {}

    int size() const { return (int)values_.size(); }

    const T& get(int p) const {
        assert(0 <= p && p < size());
        return values_[p];
    }

    void set(int p, const T& x) {
        assert(0 <= p && p < size());
        if (!(values_[p] < x) && !(x < values_[p])) return;
        positions_.erase_one({values_[p], p});
        values_[p] = x;
        positions_.insert({values_[p], p});
    }

    int freq(int l, int r, const T& x) const {
        assert(0 <= l && l <= r && r <= size());
        return positions_.order_of_key({x, r}) - positions_.order_of_key({x, l});
    }
};

/**
 * @brief 点更新・区間頻度
 */
