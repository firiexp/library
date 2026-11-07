#ifndef FIRIEXP_LIBRARY_STRING_LONGEST_COMMON_SUBSTRING_CPP
#define FIRIEXP_LIBRARY_STRING_LONGEST_COMMON_SUBSTRING_CPP

#include "suffix_automaton.cpp"

template<int W, char start = 'a'>
optional<string> longest_common_substring(const vector<string>& strings) {
    if (strings.empty()) return nullopt;
    int base = 0;
    for (int i = 1; i < (int)strings.size(); ++i)
        if (strings[i].size() < strings[base].size()) base = i;
    if (strings[base].empty() || strings.size() == 1)
        return strings[base];
    SuffixAutomaton<W, start> sam(strings[base]);
    auto order = sam.order_by_length();
    int states = sam.nodes.size();
    vector<int> common(states), best(states);
    for (int v = 0; v < states; ++v) common[v] = sam.nodes[v].len;
    for (int i = 0; i < (int)strings.size(); ++i) {
        if (i == base) continue;
        fill(best.begin(), best.end(), 0);
        int v = 0, length = 0;
        for (char c : strings[i]) {
            int k = sam.ord(c);
            if (k < 0 || k >= W) {
                v = length = 0;
                continue;
            }
            while (v && sam.nodes[v].next[k] == -1) {
                v = sam.nodes[v].link;
                length = sam.nodes[v].len;
            }
            if (sam.nodes[v].next[k] == -1) length = 0;
            else {
                v = sam.nodes[v].next[k];
                ++length;
                best[v] = max(best[v], length);
            }
        }
        for (int j = states - 1; j > 0; --j) {
            int v = order[j], p = sam.nodes[v].link;
            best[p] = max(best[p], min(best[v], sam.nodes[p].len));
        }
        for (int v = 0; v < states; ++v) common[v] = min(common[v], best[v]);
    }
    int left = 0, length = 0;
    for (int v = 1; v < states; ++v) {
        if (common[v] > length) {
            length = common[v];
            left = sam.nodes[v].first_pos + 1 - length;
        }
    }
    return strings[base].substr(left, length);
}

#endif

/**
 * @brief 複数文字列の最長共通部分文字列
 */
