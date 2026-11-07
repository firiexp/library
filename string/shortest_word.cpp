#ifndef FIRIEXP_LIBRARY_STRING_SHORTEST_WORD_CPP
#define FIRIEXP_LIBRARY_STRING_SHORTEST_WORD_CPP

#include "dfa.cpp"

template<int W>
optional<string> shortest_word(const DFA<W>& a, string_view alphabet) {
    assert(alphabet.size() == W);
    if (a.initial == -1) return nullopt;
    if (a.accept[a.initial]) return string{};
    vector<int> parent(a.next.size(), -1), letter(a.next.size());
    vector<int> queue{a.initial};
    parent[a.initial] = a.initial;
    for (size_t i = 0; i < queue.size(); ++i) {
        int v = queue[i];
        for (int c = 0; c < W; ++c) {
            int to = a.next[v][c];
            if (to == -1 || parent[to] != -1) continue;
            parent[to] = v;
            letter[to] = c;
            if (a.accept[to]) {
                string result;
                for (int u = to; u != a.initial; u = parent[u]) result.push_back(alphabet[letter[u]]);
                reverse(result.begin(), result.end());
                return result;
            }
            queue.push_back(to);
        }
    }
    return nullopt;
}

#endif

/**
 * @brief 有限オートマトンの最短受理文字列
 */
