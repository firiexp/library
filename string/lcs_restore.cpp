vector<pair<int, int>> lcs_restore(const string &a, const string &b) {
    if (a.empty() || b.empty()) return {};
    bool swapped = a.size() < b.size();
    const string &x = swapped ? b : a;
    const string &y = swapped ? a : b;
    int n = x.size(), m = y.size();
    vector<int> prefix(m + 1), suffix(m + 1);
    vector<pair<int, int>> result;
    auto solve = [&](auto &&self, int left, int right, int lo, int hi) -> void {
        if (left == right || lo == hi) return;
        if (right - left == 1) {
            for (int j = lo; j < hi; ++j) if (x[left] == y[j]) {
                if (swapped) result.emplace_back(j, left);
                else result.emplace_back(left, j);
                break;
            }
            return;
        }
        int mid = left + (right - left) / 2, width = hi - lo;
        fill(prefix.begin(), prefix.begin() + width + 1, 0);
        fill(suffix.begin(), suffix.begin() + width + 1, 0);
        for (int i = left; i < mid; ++i) {
            int previous = 0;
            for (int j = 0; j < width; ++j) {
                int next = prefix[j + 1];
                prefix[j + 1] = x[i] == y[lo + j] ? previous + 1 : max(prefix[j], next);
                previous = next;
            }
        }
        for (int i = right - 1; i >= mid; --i) {
            int previous = 0;
            for (int j = 0; j < width; ++j) {
                int next = suffix[j + 1];
                suffix[j + 1] = x[i] == y[hi - 1 - j] ? previous + 1 : max(suffix[j], next);
                previous = next;
            }
        }
        int split = 0;
        for (int j = 1; j <= width; ++j)
            if (prefix[j] + suffix[width - j] > prefix[split] + suffix[width - split]) split = j;
        self(self, left, mid, lo, lo + split);
        self(self, mid, right, lo + split, hi);
    };
    solve(solve, 0, n, 0, m);
    return result;
}

/**
 * @brief 最長共通部分列の添字復元
 */
