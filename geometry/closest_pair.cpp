pair<int, int> closest_pair(const vector<pair<long long, long long>> &points) {
    using Dist = __int128_t;
    struct P {
        long long x;
        long long y;
        int idx;
    };

    int n = points.size();
    assert(n >= 2);
    vector<P> ps(n);
    for (int i = 0; i < n; ++i) {
        ps[i] = {points[i].first, points[i].second, i};
    }
    sort(ps.begin(), ps.end(), [](const P &a, const P &b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.idx < b.idx;
    });

    Dist best = -1;
    pair<int, int> ans = {-1, -1};
    auto update = [&](const P &a, const P &b) {
        Dist dx = Dist(a.x) - Dist(b.x);
        Dist dy = Dist(a.y) - Dist(b.y);
        Dist d = dx * dx + dy * dy;
        pair<int, int> cand = {a.idx, b.idx};
        if (best == -1 || d < best) {
            best = d;
            ans = cand;
        }
    };
    update(ps[0], ps[1]);

    auto dfs = [&](auto &&self, int l, int r) -> vector<int> {
        if (r - l == 1) return {l};
        int m = (l + r) >> 1;
        long long mx = ps[m].x;
        vector<int> left = self(self, l, m);
        vector<int> right = self(self, m, r);
        vector<int> ord;
        vector<int> near;
        ord.reserve(r - l);
        near.reserve(r - l);
        int i = 0, j = 0;
        while (i < (int)left.size() || j < (int)right.size()) {
            int idx;
            if (j == (int)right.size() || (i < (int)left.size() && ps[left[i]].y < ps[right[j]].y)) {
                idx = left[i++];
            } else {
                idx = right[j++];
            }
            ord.push_back(idx);
            Dist dx = Dist(ps[idx].x) - Dist(mx);
            if (dx * dx > best) continue;
            for (int k = (int)near.size() - 1; k >= 0; --k) {
                int idy = near[k];
                Dist dy = Dist(ps[idx].y) - Dist(ps[idy].y);
                if (best == 0 || dy * dy > best) break;
                update(ps[idx], ps[idy]);
            }
            near.push_back(idx);
        }
        return ord;
    };
    dfs(dfs, 0, n);
    return ans;
}

/**
 * @brief Closest Pair
 */
