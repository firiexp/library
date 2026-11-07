#ifndef FIRIEXP_LIBRARY_STRING_SUFFIX_AUTOMATON_CPP
#define FIRIEXP_LIBRARY_STRING_SUFFIX_AUTOMATON_CPP

template<int W, char start = 'a'>
struct SuffixAutomaton {
    struct Node {
        int link;
        int len;
        int occ;
        int first_pos;
        int next[W];
        Node(int link = -1, int len = 0, int occ = 0): link(link), len(len), occ(occ), first_pos(len - 1) {
            fill(next, next + W, -1);
        }
    };

    vector<Node> nodes;
    int last;

    struct SubstringMatch {
        int s_l, s_r, t_l, t_r;
    };

    SuffixAutomaton(): nodes(1), last(0) {}

    template<class T>
    explicit SuffixAutomaton(const T &s): SuffixAutomaton() {
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
        ways.clear();
        occurrence_begin.clear();
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
        } else {
            int q = nodes[p].next[k];
            if (nodes[p].len + 1 == nodes[q].len) {
                nodes[cur].link = q;
            } else {
                int clone = nodes.size();
                nodes.push_back(nodes[q]);
                nodes[clone].len = nodes[p].len + 1;
                nodes[clone].occ = 0;
                while (p != -1 && nodes[p].next[k] == q) {
                    nodes[p].next[k] = clone;
                    p = nodes[p].link;
                }
                nodes[q].link = nodes[cur].link = clone;
            }
        }
        distinct += nodes[cur].len - nodes[nodes[cur].link].len;
        last = cur;
        return cur;
    }

    template<class T>
    void build(const T &s) {
        reserve(s.size());
        for (auto &&c : s) add(c);
    }

    template<class T>
    SubstringMatch longest_common_substring(const T &t) const {
        SubstringMatch result{0, 0, 0, 0};
        int state = 0, length = 0, index = 0;
        for (auto c : t) {
            int k = ord(c);
            if (k < 0 || k >= W) {
                state = length = 0;
            } else {
                while (state && nodes[state].next[k] == -1) {
                    state = nodes[state].link;
                    length = nodes[state].len;
                }
                if (nodes[state].next[k] == -1) length = 0;
                else {
                    state = nodes[state].next[k];
                    ++length;
                }
                if (length > result.s_r - result.s_l) {
                    int end = nodes[state].first_pos + 1;
                    result = {end - length, end, index + 1 - length, index + 1};
                }
            }
            ++index;
        }
        return result;
    }

    long long count_distinct_substrings() const {
        return distinct;
    }

    optional<pair<int, int>> kth_substring(long long k) const {
        if (k < 0) return nullopt;
        if (ways.empty()) {
            auto order = order_by_length();
            ways.assign(nodes.size(), 1);
            for (int i = (int)order.size() - 1; i >= 0; --i) {
                int v = order[i];
                for (int to : nodes[v].next) if (to != -1) ways[v] += ways[to];
            }
        }
        if (k >= ways[0] - 1) return nullopt;
        int v = 0, length = 0;
        while (true) {
            for (int to : nodes[v].next) {
                if (to == -1) continue;
                if (k >= ways[to]) {
                    k -= ways[to];
                    continue;
                }
                v = to;
                ++length;
                if (k == 0) {
                    int end = nodes[v].first_pos + 1;
                    return pair<int, int>{end - length, end};
                }
                --k;
                break;
            }
        }
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
        vector<int> cnt(nodes.size());
        for (int i = 0; i < (int)nodes.size(); ++i) cnt[i] = nodes[i].occ;
        auto ord = order_by_length();
        for (int i = (int)ord.size() - 1; i >= 1; --i) {
            int v = ord[i];
            cnt[nodes[v].link] += cnt[v];
        }
        return cnt;
    }

    template<class Emit>
    void for_each_occurrence(string_view pattern, Emit &&emit) const {
        if (pattern.empty()) {
            for (int i = 0; i <= nodes[last].len; ++i) emit(i);
            return;
        }
        if (pattern.size() > size_t(nodes[last].len)) return;
        int v = 0;
        for (char c : pattern) {
            int k = ord(c);
            if (k < 0 || k >= W || nodes[v].next[k] == -1) return;
            v = nodes[v].next[k];
        }
        if (occurrence_begin.empty()) prepare_occurrences();
        for (int i = occurrence_begin[v]; i < occurrence_end[v]; ++i)
            emit(occurrence_positions[i] + 1 - int(pattern.size()));
    }

private:
    long long distinct = 0;
    mutable vector<long long> ways;
    mutable vector<int> occurrence_begin, occurrence_end, occurrence_positions;

    void prepare_occurrences() const {
        int n = nodes.size();
        vector<int> head(n, -1), next(n, -1), stack{0};
        for (int v = 1; v < n; ++v) {
            int p = nodes[v].link;
            next[v] = head[p];
            head[p] = v;
        }
        occurrence_begin.resize(n);
        occurrence_end.resize(n);
        occurrence_positions.clear();
        occurrence_positions.reserve(nodes[last].len);
        stack.reserve(n);
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            if (v < 0) {
                occurrence_end[~v] = occurrence_positions.size();
                continue;
            }
            occurrence_begin[v] = occurrence_positions.size();
            if (nodes[v].occ) occurrence_positions.push_back(nodes[v].first_pos);
            stack.push_back(~v);
            for (int u = head[v]; u != -1; u = next[u]) stack.push_back(u);
        }
    }
};

#endif

/**
 * @brief Suffix Automaton
 */
