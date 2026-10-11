template<int W, class F> // W -> word size
struct Trie {
    struct Node {
        char c;
        array<int, W> nxt;
        vector<int> idxs;
        int id;
        explicit Node(char c): c(c), id(-1){
            fill(nxt.begin(),nxt.end(), -1);
        }
    };
    vector<Node> v;
    F f;
    explicit Trie(F f, char c = '$') : f(f) {
        v.emplace_back(c);
    }
    void add(const string &s, int x){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(~v[cur].nxt[k]){
                cur = v[cur].nxt[k];
                continue;
            }
            int npos = v.size();
            v[cur].nxt[k] = npos;
            v.emplace_back(i);
            cur = npos;
        }
        v[cur].id = x;
        v[cur].idxs.emplace_back(x);
    }

    int find(const string &s){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(v[cur].nxt[k] < 0) return -1;
            cur = v[cur].nxt[k];
        }
        return cur;
    }
    int find(int cur, char c) {return v[cur].nxt[f(c)]; }
    int id(int cur) { return cur < 0 ? -1 : v[cur].id;}

    vector<int> idxs(int cur) { return cur < 0 ? vector<int>() : v[cur].idxs; }

    struct PrefixIntervals {
        vector<int> order;
        vector<pair<int, int>> range;
    };

    PrefixIntervals prefix_intervals() const {
        PrefixIntervals result;
        result.range.resize(v.size());
        vector<pair<int, int>> stack{{0, 0}};
        while (!stack.empty()) {
            int node = stack.back().first;
            int& next = stack.back().second;
            if (next == 0) {
                result.range[node].first = result.order.size();
                result.order.insert(result.order.end(), v[node].idxs.begin(), v[node].idxs.end());
            }
            while (next < W && v[node].nxt[next] == -1) ++next;
            if (next == W) {
                result.range[node].second = result.order.size();
                stack.pop_back();
            } else {
                int child = v[node].nxt[next++];
                stack.emplace_back(child, 0);
            }
        }
        return result;
    }
};

/**
 * @brief Trie 木
 */
