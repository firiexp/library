#ifndef FIRIEXP_LIBRARY_STRING_ACTIVE_PATTERN_MATCHER_CPP
#define FIRIEXP_LIBRARY_STRING_ACTIVE_PATTERN_MATCHER_CPP

#include "ahocorasick.cpp"
#include "../datastructure/binaryindexedtree.cpp"

template<int W, int start>
class ActivePatternMatcher {
    AhoCorasick<W, start> aho;
    vector<int> terminal, begin, end;
    vector<long long> weight;
    BIT<__int128> bit;

public:
    explicit ActivePatternMatcher(const vector<string> &patterns) : weight(patterns.size()), bit(0) {
        terminal.reserve(patterns.size());
        for (const auto &pattern : patterns) terminal.push_back(aho.add(pattern));
        aho.build();
        int n = aho.v.size();
        begin.resize(n);
        end.resize(n);
        vector<int> size(n, 1), cursor(n);
        for (int i = n - 1; i > 0; --i) {
            int v = aho.ord[i];
            size[aho.v[v].fail] += size[v];
        }
        cursor[0] = 1;
        end[0] = n;
        for (int i = 1; i < n; ++i) {
            int v = aho.ord[i], p = aho.v[v].fail;
            begin[v] = cursor[p];
            cursor[p] += size[v];
            cursor[v] = begin[v] + 1;
            end[v] = begin[v] + size[v];
        }
        bit = BIT<__int128>(n);
    }

    void set_weight(int id, long long value) {
        assert(0 <= id && id < (int)terminal.size());
        __int128 delta = (__int128)value - weight[id];
        weight[id] = value;
        int v = terminal[id];
        bit.add(begin[v], delta);
        bit.add(end[v], -delta);
    }

    long long query(const string &text) {
        int state = 0;
        __int128 answer = bit.sum(begin[0] + 1);
        for (char c : text) {
            state = aho.next(state, c);
            answer += bit.sum(begin[state] + 1);
        }
        assert(numeric_limits<long long>::min() <= answer && answer <= numeric_limits<long long>::max());
        return (long long)answer;
    }
};

#endif

/**
 * @brief 重み更新付きパターン照合
 */
