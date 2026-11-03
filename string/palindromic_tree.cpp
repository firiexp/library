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

    struct Partitions {
        vector<int> count, prev;
    };

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
        for (int v = (int)nodes.size() - 1; v >= 2; --v) {
            res[nodes[v].link] += res[v];
        }
        return res;
    }

    Partitions min_partitions() const {
        int n = s.size(), size = nodes.size();
        vector<int> diff(size), series(size);
        for (int v = 2; v < size; ++v) {
            int link = nodes[v].link;
            diff[v] = nodes[v].len - nodes[link].len;
            series[v] = diff[v] == diff[link] ? series[link] : link;
        }
        Partitions result{vector<int>(n + 1, n + 1), vector<int>(n + 1, -1)};
        result.count[0] = 0;
        vector<pair<int, int>> best(size, {n + 1, -1});
        for (int i = 1; i <= n; ++i) {
            for (int v = path[i - 1]; nodes[v].len > 0; v = series[v]) {
                int from = i - nodes[series[v]].len - diff[v];
                best[v] = {result.count[from], from};
                int link = nodes[v].link;
                if (diff[v] == diff[link]) best[v] = min(best[v], best[link]);
                if (best[v].first + 1 < result.count[i]) {
                    result.count[i] = best[v].first + 1;
                    result.prev[i] = best[v].second;
                }
            }
        }
        return result;
    }
};

template<int W, char start = 'a'>
class PalindromicPartition {
    using Partitions = typename PalindromicTree<W, start>::Partitions;
    PalindromicTree<W, start> tree;
    Partitions result{{0}, {-1}};
    vector<int> diff{0, 0}, series{0, 0};
    vector<pair<int, int>> best = vector<pair<int, int>>(2, {INT_MAX, -1});

public:
    PalindromicPartition() = default;

    explicit PalindromicPartition(const string &s) {
        reserve(s.size());
        build(s);
    }

    void reserve(int n) {
        tree.reserve(n);
        result.count.reserve(n + 1);
        result.prev.reserve(n + 1);
        diff.reserve(n + 2);
        series.reserve(n + 2);
        best.reserve(n + 2);
    }

    int add(char c) {
        int last = tree.add(c);
        const auto &nodes = tree.nodes;
        if (diff.size() < nodes.size()) {
            int v = diff.size(), link = nodes[v].link;
            diff.push_back(nodes[v].len - nodes[link].len);
            series.push_back(diff[v] == diff[link] ? series[link] : link);
            best.emplace_back(INT_MAX, -1);
        }
        int i = result.count.size();
        result.count.push_back(i + 1);
        result.prev.push_back(-1);
        for (int v = last; nodes[v].len > 0; v = series[v]) {
            int from = i - nodes[series[v]].len - diff[v];
            best[v] = {result.count[from], from};
            int link = nodes[v].link;
            if (diff[v] == diff[link]) best[v] = min(best[v], best[link]);
            if (best[v].first + 1 < result.count[i]) {
                result.count[i] = best[v].first + 1;
                result.prev[i] = best[v].second;
            }
        }
        return count();
    }

    void build(const string &s) {
        for (char c : s) add(c);
    }

    int count() const {
        return result.count.back();
    }

    const Partitions &partitions() const {
        return result;
    }
};

/**
 * @brief 回文木(Palindromic Tree)
 */
