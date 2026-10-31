#ifndef FIRIEXP_LIBRARY_STRING_AVOID_PATTERNS_CPP
#define FIRIEXP_LIBRARY_STRING_AVOID_PATTERNS_CPP

#include "dfa.cpp"
#include "ahocorasick.cpp"

template<int W, int start>
DFA<W> avoid_patterns(const vector<string>& patterns) {
    AhoCorasick<W, start> ac;
    for (const string& s : patterns) {
        if (s.empty()) return {};
        int v = ac.add(s);
        ac.v[v].val = 1;
    }
    ac.build();
    for (int v : ac.ord) {
        if (v != 0) ac.v[v].val |= ac.v[ac.v[v].fail].val;
    }
    vector<int> id(ac.v.size(), -1), states{0};
    id[0] = 0;
    DFA<W> result{vector<array<int, W>>(1), vector<char>(1, true), 0};
    for (int i = 0; i < (int)states.size(); ++i) {
        int v = states[i];
        for (int c = 0; c < W; ++c) {
            int to = ac.v[v].to[c];
            if (ac.v[to].val) {
                result.next[i][c] = -1;
                continue;
            }
            if (id[to] == -1) {
                id[to] = (int)states.size();
                states.push_back(to);
                result.next.emplace_back();
                result.accept.push_back(true);
            }
            result.next[i][c] = id[to];
        }
    }
    return result;
}

#endif

/**
 * @brief 禁止部分文字列を避ける有限オートマトン
 */
