class FastSet {
    int n;
    vector<vector<unsigned long long>> layers;

public:
    explicit FastSet(int n) : n(n) {
        assert(n >= 0);
        while (n > 0) {
            n = (n + 63LL) / 64;
            layers.emplace_back(n, 0);
            if (n == 1) break;
        }
    }

    explicit FastSet(const vector<bool> &present) : FastSet((int)present.size()) {
        for (int i = 0; i < n; ++i)
            if (present[i]) layers[0][i >> 6] |= 1ULL << (i & 63);
        for (int h = 1; h < (int)layers.size(); ++h)
            for (int i = 0; i < (int)layers[h - 1].size(); ++i)
                if (layers[h - 1][i]) layers[h][i >> 6] |= 1ULL << (i & 63);
    }

    bool contains(int x) const {
        assert(0 <= x && x < n);
        return (layers[0][x >> 6] >> (x & 63)) & 1;
    }

    void insert(int x) {
        assert(0 <= x && x < n);
        for (auto &layer : layers) {
            auto &word = layer[x >> 6];
            bool nonempty = word != 0;
            word |= 1ULL << (x & 63);
            if (nonempty) break;
            x >>= 6;
        }
    }

    void erase(int x) {
        assert(0 <= x && x < n);
        for (auto &layer : layers) {
            auto &word = layer[x >> 6];
            word &= ~(1ULL << (x & 63));
            if (word) break;
            x >>= 6;
        }
    }

    int next(int x) const {
        assert(0 <= x && x <= n);
        if (x == n) return -1;
        for (int h = 0; h < (int)layers.size(); ++h) {
            if ((x >> 6) >= (int)layers[h].size()) return -1;
            auto word = layers[h][x >> 6] >> (x & 63);
            if (!word) {
                x = (x >> 6) + 1;
                continue;
            }
            x += __builtin_ctzll(word);
            for (int j = h - 1; j >= 0; --j)
                x = x * 64 + __builtin_ctzll(layers[j][x]);
            return x;
        }
        return -1;
    }

    int prev(int x) const {
        assert(-1 <= x && x < n);
        if (x == -1) return -1;
        for (int h = 0; h < (int)layers.size(); ++h) {
            auto word = layers[h][x >> 6] << (63 - (x & 63));
            if (!word) {
                x = (x >> 6) - 1;
                if (x < 0) return -1;
                continue;
            }
            x -= __builtin_clzll(word);
            for (int j = h - 1; j >= 0; --j)
                x = x * 64 + 63 - __builtin_clzll(layers[j][x]);
            return x;
        }
        return -1;
    }
};

/**
 * @brief 整数集合の前後検索(FastSet)
 */
