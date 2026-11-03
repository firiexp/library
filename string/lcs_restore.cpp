vector<pair<int, int>> lcs_restore(const string &a, const string &b) {
    if (a.empty() || b.empty()) return {};
    bool swapped = a.size() < b.size();
    const string &x = swapped ? b : a;
    const string &y = swapped ? a : b;
    int n = x.size(), m = y.size();
    int lead = 0, tail = 0;
    while (lead < m && x[lead] == y[lead]) ++lead;
    while (tail < m - lead && x[n - 1 - tail] == y[m - 1 - tail]) ++tail;
    vector<int> prefix(m - lead - tail + 1), suffix(m - lead - tail + 1);
    vector<pair<int, int>> result;
    for (int i = 0; i < lead; ++i) result.emplace_back(i, i);
    auto bit_row = [&](int left, int right, int lo, int hi, bool reverse, vector<int> &row) {
        int width = hi - lo, words = (width + 63) / 64;
        vector<uint64_t> mask(size_t(256) * words), dp(words);
        for (int j = 0; j < width; ++j) {
            unsigned char c = y[reverse ? hi - 1 - j : lo + j];
            mask[size_t(c) * words + j / 64] |= uint64_t(1) << (j % 64);
        }
        for (int i = 0; i < right - left; ++i) {
            unsigned char c = x[reverse ? right - 1 - i : left + i];
            const uint64_t *match = mask.data() + size_t(c) * words;
            uint64_t shift = 1, borrow = 0;
            for (int j = 0; j < words; ++j) {
                uint64_t bits = dp[j] | match[j], shifted = (dp[j] << 1) | shift;
                shift = dp[j] >> 63;
                uint64_t difference = bits - shifted;
                uint64_t next = (bits < shifted) | (difference < borrow);
                dp[j] = bits & ~(difference - borrow);
                borrow = next;
            }
        }
        row[0] = 0;
        for (int j = 0; j < width; ++j) row[j + 1] = row[j] + ((dp[j / 64] >> (j % 64)) & 1);
    };
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
        if (width >= 64 && right - left >= 64) {
            bit_row(left, mid, lo, hi, false, prefix);
            bit_row(mid, right, lo, hi, true, suffix);
        } else {
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
        }
        int split = 0;
        for (int j = 1; j <= width; ++j)
            if (prefix[j] + suffix[width - j] > prefix[split] + suffix[width - split]) split = j;
        self(self, left, mid, lo, lo + split);
        self(self, mid, right, lo + split, hi);
    };
    solve(solve, lead, n - tail, lead, m - tail);
    for (int i = tail; i > 0; --i) {
        if (swapped) result.emplace_back(m - i, n - i);
        else result.emplace_back(n - i, m - i);
    }
    return result;
}

/**
 * @brief 最長共通部分列の添字復元
 */
