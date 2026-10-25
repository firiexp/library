#ifndef FIRIEXP_LIBRARY_STRING_LEX_TRIE_CPP
#define FIRIEXP_LIBRARY_STRING_LEX_TRIE_CPP

class LexTrie {
    struct Node {
        int parent, jump, len, c, first, head;
    };

    vector<Node> nodes;
    vector<int> table;
    size_t used = 0;
    uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();

    uint64_t hash(int p, int c) const {
        uint64_t x = ((uint64_t(uint32_t(p)) << 32) | uint32_t(c)) + seed;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t slot(int p, int c) const {
        size_t mask = table.size() - 1;
        size_t i = hash(p, c) & mask;
        while (table[i] && (nodes[table[i]].parent != p || nodes[table[i]].c != c))
            i = (i + 1) & mask;
        return i;
    }

    void rehash(size_t capacity) {
        vector<int> next(capacity);
        for (int v : table) if (v) {
            size_t i = hash(nodes[v].parent, nodes[v].c) & (capacity - 1);
            while (next[i]) i = (i + 1) & (capacity - 1);
            next[i] = v;
        }
        table.swap(next);
    }

    int add_node(int p, int c) {
        int j = nodes[p].jump, k = nodes[j].jump;
        int up = nodes[p].len - nodes[j].len == nodes[j].len - nodes[k].len ? k : p;
        int v = nodes.size();
        int head = nodes[p].first ? v : nodes[p].head;
        nodes.push_back({p, up, nodes[p].len + 1, c, 0, head});
        return v;
    }

    int at_depth(int v, int depth) const {
        while (nodes[v].len > depth) {
            int j = nodes[v].jump;
            v = nodes[j].len >= depth ? j : nodes[v].parent;
        }
        return v;
    }

    void branch(int& a, int& b) const {
        int x = nodes[a].head, y = nodes[b].head;
        if (x == y) {
            if (nodes[a].len > nodes[b].len) a = b;
            else b = a;
            return;
        }
        if (x && y && nodes[x].parent == nodes[y].parent) {
            a = x;
            b = y;
            return;
        }
        if (nodes[a].len > nodes[b].len) a = at_depth(a, nodes[b].len);
        else if (nodes[b].len > nodes[a].len) b = at_depth(b, nodes[a].len);
        while (nodes[a].parent != nodes[b].parent) {
            int x = nodes[a].jump, y = nodes[b].jump;
            if (x != y) {
                a = x;
                b = y;
            } else {
                a = nodes[a].parent;
                b = nodes[b].parent;
            }
        }
    }

public:
    explicit LexTrie(int capacity = 0) {
        reserve(capacity);
        nodes.push_back({0, 0, 0, 0, 0, 0});
    }

    void reserve(int capacity) {
        assert(capacity >= 0);
        nodes.reserve(max(1, capacity));
    }

    int size() const { return nodes.size(); }
    int length(int v) const { return nodes[v].len; }

    int append(int p, int c) {
        int first = nodes[p].first;
        if (!first) {
            int v = add_node(p, c);
            nodes[p].first = v;
            return v;
        }
        if (nodes[first].c == c) return first;
        if (table.empty()) rehash(8);
        size_t i = slot(p, c);
        if (table[i]) return table[i];
        if ((used + 1) * 2 > table.size()) {
            rehash(table.size() * 2);
            i = slot(p, c);
        }
        int v = add_node(p, c);
        table[i] = v;
        ++used;
        return v;
    }

    int append(int p, char c) { return append(p, int((unsigned char)c)); }

    int append(int p, string_view s) {
        for (unsigned char c : s) p = append(p, int(c));
        return p;
    }

    int insert(string_view s) { return append(0, s); }

    int jump(int v, int k) const {
        if (k < 0 || k > nodes[v].len) return -1;
        return at_depth(v, nodes[v].len - k);
    }

    int lca(int a, int b) const {
        branch(a, b);
        return a == b ? a : nodes[a].parent;
    }

    int lcp(int a, int b) const { return nodes[lca(a, b)].len; }

    int compare(int a, int b) const {
        if (a == b) return 0;
        int order = (nodes[a].len > nodes[b].len) - (nodes[a].len < nodes[b].len);
        branch(a, b);
        if (a == b) return order;
        return (nodes[a].c > nodes[b].c) - (nodes[a].c < nodes[b].c);
    }

    bool less(int a, int b) const { return compare(a, b) < 0; }
};

#endif

/**
 * @brief 辞書順比較付きTrie
 */
