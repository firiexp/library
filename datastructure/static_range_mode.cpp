template<class T>
class StaticRangeMode {
    struct Occurrence {
        int id, rank;
    };
    vector<T> values;
    int width;
    vector<Occurrence> occurrence;
    vector<vector<int>> positions;
    vector<vector<pair<int, int>>> modes;

public:
    explicit StaticRangeMode(vector<T> a)
        : values(move(a)), width(max(1, int(sqrt(values.size())))), occurrence(values.size()) {
        int n = values.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) { return values[i] < values[j]; });
        for (int k = 0; k < n; ++k) {
            if (k == 0 || values[order[k - 1]] < values[order[k]]) positions.emplace_back();
            occurrence[order[k]].id = int(positions.size()) - 1;
        }
        for (int i = 0; i < n; ++i) {
            auto &list = positions[occurrence[i].id];
            occurrence[i].rank = list.size();
            list.push_back(i);
        }

        int blocks = n / width;
        modes.resize(blocks);
        for (int first = 0; first < blocks; ++first) {
            vector<int> count(positions.size());
            pair<int, int> best{0, 0};
            for (int b = first; b < blocks; ++b) {
                for (int i = b * width; i < (b + 1) * width; ++i) {
                    int freq = ++count[occurrence[i].id];
                    if (freq > best.second) best = {i, freq};
                }
                modes[first].push_back(best);
            }
        }
    }

    pair<T, int> query(int l, int r) const {
        assert(0 <= l && l < r && r <= int(values.size()));
        int first = l / width + (l % width != 0), last = r / width;
        int index = l, freq = 0, prefix_end = r, suffix_begin = r;
        if (first < last) {
            tie(index, freq) = modes[first][last - first - 1];
            prefix_end = first * width;
            suffix_begin = last * width;
        }
        for (int i = l; i < prefix_end; ++i) {
            auto [id, rank] = occurrence[i];
            const auto &list = positions[id];
            while (freq < int(list.size()) - rank && list[rank + freq] < r) {
                index = i;
                ++freq;
            }
        }
        for (int i = r - 1; i >= suffix_begin; --i) {
            auto [id, rank] = occurrence[i];
            const auto &list = positions[id];
            while (freq <= rank && list[rank - freq] >= l) {
                index = i;
                ++freq;
            }
        }
        return {values[index], freq};
    }
};

/**
 * @brief 静的配列の区間最頻値
 */
