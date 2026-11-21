int chromatic_number(int n, const vector<pair<int, int>> &edges) {
    assert(0 <= n && n <= 20);
    if (edges.empty()) return n == 0 ? 0 : 1;
    vector<int> neighbors(n);
    for (auto [u, v] : edges) {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        neighbors[u] |= 1 << v;
        neighbors[v] |= 1 << u;
    }

    int full = (1 << n) - 1;
    vector<int> independent_count(full + 1);
    independent_count[0] = 1;
    for (int mask = 1; mask <= full; ++mask) {
        int v = __builtin_ctz(mask), rest = mask & (mask - 1);
        independent_count[mask] = independent_count[rest] + independent_count[rest & ~neighbors[v]];
    }
    vector<int> coefficient(independent_count[full] + 1);
    for (int mask = 0; mask <= full; ++mask) {
        coefficient[independent_count[mask]] += __builtin_parity(full ^ mask) ? -1 : 1;
    }

    int answer = n, certified_bits = 0;
    constexpr int bits = 35;
    for (int prime : {31, 29, 23, 19, 17, 13, 11, 7, 5, 3, 2}) {
        long long mod = prime;
        while (mod < (1LL << bits)) mod *= prime;
        vector<long long> covers(answer);
        for (int count = 1; count <= independent_count[full]; ++count) {
            if (coefficient[count] == 0) continue;
            long long term = coefficient[count];
            for (int k = 1; k < answer; ++k) {
                term = term * count % mod;
                covers[k] += term;
            }
        }
        for (int k = 1; k < answer; ++k) {
            if (covers[k] % mod != 0) {
                answer = k;
                break;
            }
        }
        certified_bits += bits;
        if (certified_bits > n * (answer - 1)) break;
    }
    return answer;
}

/**
 * @brief 無向グラフの彩色数
 */
