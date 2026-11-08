#ifndef FIRIEXP_LIBRARY_STRING_AHOCORASICK_MATCHER_CPP
#define FIRIEXP_LIBRARY_STRING_AHOCORASICK_MATCHER_CPP

#include "ahocorasick.cpp"

template<int W, int start>
class AhoCorasickMatcher {
    AhoCorasick<W, start> aho;
    vector<int> head, next_id, output;
    vector<long long> length;
    int state = 0;
    long long position = 0;
    bool announced = false;

public:
    explicit AhoCorasickMatcher(const vector<string> &patterns)
        : next_id(patterns.size()), length(patterns.size()) {
        vector<int> terminal;
        terminal.reserve(patterns.size());
        for (const auto &pattern : patterns) terminal.push_back(aho.add(pattern));
        aho.build();
        head.assign(aho.v.size(), -1);
        output.assign(aho.v.size(), -1);
        for (int id = (int)patterns.size() - 1; id >= 0; --id) {
            int v = terminal[id];
            next_id[id] = head[v];
            head[v] = id;
            length[id] = patterns[id].size();
        }
        for (int v : aho.ord) {
            if (v == 0) continue;
            int p = aho.v[v].fail;
            output[v] = head[p] == -1 ? output[p] : p;
        }
    }

    void reset() {
        state = 0;
        position = 0;
        announced = false;
    }

    template<class Callback>
    void scan(string_view chunk, Callback callback) {
        auto emit = [&](int state, long long end) {
            for (int v = state; v != -1; v = output[v]) {
                for (int id = head[v]; id != -1; id = next_id[id]) {
                    callback(id, end - length[id]);
                }
            }
        };
        if (!announced) {
            announced = true;
            emit(0, 0);
        }
        int current = state;
        long long end = position;
        for (char c : chunk) {
            current = aho.v[current].to[c - start];
            emit(current, ++end);
        }
        state = current;
        position = end;
    }
};

#endif

/**
 * @brief 文字列のパターン一致位置列挙
 */
