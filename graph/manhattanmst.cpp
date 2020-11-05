template<typename T>
vector<pair<int, int>> manhattanMST(vector<T> xs, vector<T> ys) {
    using P = pair<int, int>;
    vector<P> es;
    vector<int> ord(xs.size());
    for (int s = 0; s < 4; s++) {
        iota(ord.begin(), ord.end(), 0);
        auto cmp = [&](int i, int j) -> bool {
            if (xs[i]+ys[i] != xs[j]+ys[j]) return xs[i]+ys[i] < xs[j]+ys[j];
            return (s>>1) ^ (i > j);
        };
        sort(ord.begin(), ord.end(), cmp);
        map<pair<T, int>, int> idx;
        for (auto &&i : ord) {
            pair<T, int> p = {-ys[i], (s == 3)?i:-i};
            for (auto it = idx.lower_bound(p); it != idx.end(); it = idx.erase(it)) {
                if (xs[i] - xs[it->second] < ys[i] - ys[it->second]) break;
                es.emplace_back(i, it->second);
            }
            idx[p] = i;
        }
        swap(xs, ys);
        if(s&1) for(auto &&i : xs) i = -i;
    }
    return es;
}