#ifndef FIRIEXP_LIBRARY_STRING_AHOCORASICK_MATCHER_CPP
#define FIRIEXP_LIBRARY_STRING_AHOCORASICK_MATCHER_CPP

#include "ahocorasick.cpp"

template<int W, int start>
class AhoCorasickMatcher {
    AhoCorasick<W, start> aho;
    vector<int> head, next_id, output;
    vector<size_t> length;

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

    template<class Callback>
    void scan(const string &text, Callback callback) const {
        auto emit = [&](int state, size_t end) {
            for (int v = state; v != -1; v = output[v]) {
                for (int id = head[v]; id != -1; id = next_id[id]) {
                    callback(id, end - length[id]);
                }
            }
        };
        int state = 0;
        emit(0, 0);
        for (size_t i = 0; i < text.size(); ++i) {
            state = aho.v[state].to[text[i] - start];
            emit(state, i + 1);
        }
    }
};

#endif

/**
 * @brief 文字列のパターン一致位置列挙
 */
