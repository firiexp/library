struct BoundedKnapsackItem {
    int weight;
    long long value, count;
};

vector<long long> bounded_knapsack(const vector<BoundedKnapsackItem>& items, int capacity) {
    const long long unreachable = -INF<ll>;
    vector<long long> dp(capacity + 1, unreachable);
    unique_ptr<long long[]> values;
    unique_ptr<int[]> indices;
    dp[0] = 0;
    for (auto [weight, value, count] : items) {
        int limit = capacity / weight;
        int copies = (int)min(count, (long long)limit);
        if (copies == 0) continue;
        if (copies == limit) {
            for (int w = weight; w <= capacity; ++w) {
                if (dp[w - weight] != unreachable)
                    dp[w] = max(dp[w], dp[w - weight] + value);
            }
        } else if (copies <= 32) {
            for (int step = 1; copies > 0; step <<= 1) {
                int take = min(step, copies);
                int total_weight = take * weight;
                long long total_value = take * value;
                for (int w = capacity; w >= total_weight; --w) {
                    if (dp[w - total_weight] != unreachable)
                        dp[w] = max(dp[w], dp[w - total_weight] + total_value);
                }
                copies -= take;
            }
        } else {
            if (!indices) {
                indices.reset(new int[capacity + 1]);
                values.reset(new long long[capacity + 1]);
            }
            for (int r = 0; r < weight; ++r) {
                int head = 0, tail = 0;
                for (int j = 0; j <= (capacity - r) / weight; ++j) {
                    int w = r + j * weight;
                    long long offset = j * value;
                    while (head < tail && indices[head] < j - copies) ++head;
                    if (dp[w] != unreachable) {
                        long long candidate = dp[w] - offset;
                        while (head < tail && values[tail - 1] <= candidate) --tail;
                        indices[tail] = j;
                        values[tail++] = candidate;
                    }
                    dp[w] = head < tail ? values[head] + offset : unreachable;
                }
            }
        }
    }
    return dp;
}

/**
 * @brief 個数制限付きナップサック
 */
