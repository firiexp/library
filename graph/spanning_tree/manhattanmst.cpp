template<typename T>
vector<pair<int, int>> manhattanMST(vector<T> xs, vector<T> ys) {
    int n = xs.size();
    auto order_by = [&](auto key) {
        vector<pair<decltype(key(0)), int>> keys;
        keys.reserve(n);
        for (int i = 0; i < n; ++i) keys.emplace_back(key(i), i);
        sort(keys.begin(), keys.end());
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = keys[i].second;
        return order;
    };
    auto ranks = [&](const vector<int> &order) {
        vector<int> rank(n);
        for (int i = 0; i < n; ++i) rank[order[i]] = i;
        return rank;
    };

    auto x_rank = ranks(order_by([&](int i) -> T { return xs[i]; }));
    auto y_rank = ranks(order_by([&](int i) -> T { return ys[i]; }));
    auto sum_order = order_by([&](int i) { return xs[i] + ys[i]; });
    auto diff_order = order_by([&](int i) { return xs[i] - ys[i]; });
    vector<int> bit(size_t(n) + 1);
    vector<pair<int, int>> edges;
    edges.reserve(size_t(n) * 4);
    auto sweep = [&](const vector<int> &order, const vector<int> &axis_rank,
                     const vector<int> &cost_order) {
        auto cost_rank = ranks(cost_order);
        fill(bit.begin(), bit.end(), n);
        for (int i : order) {
            int pos = n - axis_rank[i], best = n;
            for (int j = pos; j > 0; j -= j & -j) best = min(best, bit[j]);
            if (best < n) edges.emplace_back(i, cost_order[best]);
            int cost = cost_rank[i];
            for (size_t j = pos; j < bit.size() && cost < bit[j]; j += j & -j) bit[j] = cost;
        }
    };

    sweep(sum_order, x_rank, diff_order);
    reverse(diff_order.begin(), diff_order.end());
    sweep(sum_order, y_rank, diff_order);
    sweep(diff_order, y_rank, sum_order);
    reverse(sum_order.begin(), sum_order.end());
    for (int &x : x_rank) x = n - 1 - x;
    sweep(diff_order, x_rank, sum_order);
    return edges;
}

/**
 * @brief マンハッタンMST(Manhattan MST)
 */
