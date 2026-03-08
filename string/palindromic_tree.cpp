template<int W, char start = 'a'>
struct PalindromicTree {
    struct Node {
        int link;
        int len;
        int first_pos;
        int occ;
        int next[W];

        Node(int link = 0, int len = 0, int first_pos = -1)
            : link(link), len(len), first_pos(first_pos), occ(0) {
            fill(next, next + W, -1);
        }
    };

    vector<Node> nodes;
    vector<int> path;
    string s;
    int last;

    PalindromicTree(): nodes(), path(), s(), last(1) {
        nodes.reserve(2);
        nodes.emplace_back(0, -1, -1);
        nodes.emplace_back(0, 0, -1);
    }

    explicit PalindromicTree(const string &t): PalindromicTree() {
        reserve(t.size());
        build(t);
    }

    void reserve(int n) {
        nodes.reserve(n + 2);
        path.reserve(n);
        s.reserve(n);
    }

    static int ord(char c) {
        return c - start;
    }

    int suffix_link(int v, int pos, int c) const {
        while (true) {
            int j = pos - 1 - nodes[v].len;
            if (j >= 0 && ord(s[j]) == c) return v;
            v = nodes[v].link;
        }
    }

    int add(char ch) {
        int c = ord(ch);
        int pos = s.size();
        s.push_back(ch);

        int p = suffix_link(last, pos, c);
        if (nodes[p].next[c] != -1) {
            last = nodes[p].next[c];
            ++nodes[last].occ;
            path.push_back(last);
            return last;
        }

        int cur = nodes.size();
        nodes.emplace_back(0, nodes[p].len + 2, pos);
        nodes[p].next[c] = cur;
        if (nodes[cur].len == 1) {
            nodes[cur].link = 1;
        } else {
            int q = suffix_link(nodes[p].link, pos, c);
            nodes[cur].link = nodes[q].next[c];
        }
        last = cur;
        ++nodes[last].occ;
        path.push_back(last);
        return last;
    }

    void build(const string &t) {
        for (auto &&c : t) add(c);
    }

    vector<int> count() const {
        vector<int> res(nodes.size());
        for (int i = 0; i < (int)nodes.size(); ++i) res[i] = nodes[i].occ;
        vector<int> ord(nodes.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) { return nodes[a].len > nodes[b].len; });
        for (auto &&v : ord) {
            if (v >= 2) res[nodes[v].link] += res[v];
        }
        return res;
    }
};

/**
 * @brief Palindromic Tree
 * @docs _md/palindromic_tree.md
 */
