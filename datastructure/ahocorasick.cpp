template<int W, int start>
class AhoCorasick {
public:
    struct Node {
        array<int, W> to;
        int fail;
        int val;
    };
    explicit AhoCorasick() : v(1) {}
    vector<Node> v;
    vector<int> ord;
    int add(string &s, int cur = 0){
        for (auto &&i : s) {
            if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();
            cur = v[cur].to[i-start];
        }
        return cur;
    }

    void build() {
        v[0].fail = -1;
        int l = 0, r = 1;
        ord.clear();
        ord.reserve(v.size());
        ord.emplace_back(0);
        while(l < r){
            int i = ord[l]; l++;
            for (int c = 0; c < W; ++c) {
                if(!v[i].to[c]) continue;
                int to = v[i].to[c];
                v[to].fail = (v[i].fail == -1 ? 0 : v[v[i].fail].to[c]);
                ord.emplace_back(to);
                r++;
            }
            if(i != 0){
                for (int c = 0; c < W; ++c) {
                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];
                }
            }
        }
    }
    inline int next(int x, char c){ return v[x].to[c-start]; }

    vector<long long> occurrence_counts(const string &text) const {
        vector<long long> counts(v.size());
        counts[0] = 1;
        int state = 0;
        for (char c : text) {
            state = v[state].to[c - start];
            ++counts[state];
        }
        for (int i = (int)ord.size() - 1; i > 0; --i) {
            int state = ord[i];
            counts[v[state].fail] += counts[state];
        }
        return counts;
    }
};
/**
 * @brief Aho-Corasick法
 */
