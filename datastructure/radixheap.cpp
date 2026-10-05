template <class K, class V>
class RadixHeap {
    static constexpr int bit_length = sizeof(K)*8;
    K last;
    size_t sz, cnt;
    
    array<vector<pair<K, V>>, bit_length> v;
    static inline int bsr(int x){
        return x ? bit_length-__builtin_clz(x) : 0;
    }
    static inline int bsr(ll x){
        return x ? bit_length-__builtin_clzll(x) : 0;
    }

    void pull() {
        if(cnt < v[0].size()) return;
        int i = 1;
        while(v[i].empty()) i++;
        last = min_element(v[i].begin(),v[i].end())->first;
        for (auto &&x : v[i]) v[bsr(x.first ^ last)].push_back(x);
        v[i].clear();
    }
public:
    RadixHeap() : last(0), sz(0), cnt(0) {}
    void emplace(K x, V val){
        sz++;
        v[bsr(x^last)].emplace_back(x, val);
    }

    pair<K, V> top() {
        pull();
        return v[0][cnt];
    }

    void pop() {
        pull();
        sz--;
        cnt++;
        auto &bucket = v[0];
        if (cnt == bucket.size()) {
            bucket.clear();
            cnt = 0;
        } else if (cnt >= bucket.size() - cnt) {
            // Move at most as many survivors as the pops since the last compaction.
            if constexpr (is_move_assignable<pair<K, V>>::value) {
                bucket.erase(bucket.begin(), bucket.begin() + cnt);
            } else {
                // Keep supporting copy-constructible, non-assignable payloads.
                vector<pair<K, V>> rest;
                rest.reserve(bucket.capacity());
                for (size_t i = cnt; i < bucket.size(); ++i) rest.push_back(bucket[i]);
                bucket.swap(rest);
            }
            cnt = 0;
        }
    }

    size_t size() const { return sz; }
    bool empty() const { return !sz; }
};
