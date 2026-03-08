template<int W, char start = 'a'>
struct SuffixAutomaton {
    struct Node {
        int link;
        int len;
        int occ;
        int next[W];
        Node(int link = -1, int len = 0, int occ = 0): link(link), len(len), occ(occ) {
            fill(next, next + W, -1);
        }
    };

    vector<Node> nodes;
    int last;

    SuffixAutomaton(): nodes(1), last(0) {}

    template<class Container>
    explicit SuffixAutomaton(const Container &s): SuffixAutomaton() {
        reserve(s.size());
        for (auto &&c : s) add(c);
    }

    void reserve(int n) {
        nodes.reserve(2 * n + 1);
    }

    static int ord(char c) {
        return c - start;
    }

    int add(char c) {
        int k = ord(c);
        int cur = nodes.size();
        nodes.emplace_back(0, nodes[last].len + 1, 1);
        int p = last;
        while (p != -1 && nodes[p].next[k] == -1) {
            nodes[p].next[k] = cur;
            p = nodes[p].link;
        }
        if (p == -1) {
            nodes[cur].link = 0;
            last = cur;
            return cur;
        }
        int q = nodes[p].next[k];
        if (nodes[p].len + 1 == nodes[q].len) {
            nodes[cur].link = q;
            last = cur;
            return cur;
        }
        int clone = nodes.size();
        nodes.push_back(nodes[q]);
        nodes[clone].len = nodes[p].len + 1;
        nodes[clone].occ = 0;
        while (p != -1 && nodes[p].next[k] == q) {
            nodes[p].next[k] = clone;
            p = nodes[p].link;
        }
        nodes[q].link = nodes[cur].link = clone;
        last = cur;
        return cur;
    }

    template<class Container>
    void build(const Container &s) {
        reserve(s.size());
        for (auto &&c : s) add(c);
    }

    long long count_distinct_substrings() const {
        long long res = 0;
        for (int i = 1; i < (int)nodes.size(); ++i) {
            res += nodes[i].len - nodes[nodes[i].link].len;
        }
        return res;
    }

    vector<int> order_by_length() const {
        int max_len = 0;
        for (auto &&node : nodes) max_len = max(max_len, node.len);
        vector<int> cnt(max_len + 1);
        for (auto &&node : nodes) cnt[node.len]++;
        for (int i = 1; i <= max_len; ++i) cnt[i] += cnt[i - 1];
        vector<int> ord(nodes.size());
        for (int i = (int)nodes.size() - 1; i >= 0; --i) {
            ord[--cnt[nodes[i].len]] = i;
        }
        return ord;
    }

    vector<int> substring_occurrences() const {
        auto cnt = nodes;
        auto ord = order_by_length();
        for (int i = (int)ord.size() - 1; i >= 1; --i) {
            int v = ord[i];
            cnt[cnt[v].link].occ += cnt[v].occ;
        }
        vector<int> res(nodes.size());
        for (int i = 0; i < (int)nodes.size(); ++i) res[i] = cnt[i].occ;
        return res;
    }
};
/**
 * @brief Suffix Automaton
 */
