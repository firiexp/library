#ifndef FIRIEXP_LIBRARY_STRING_DFA_CPP
#define FIRIEXP_LIBRARY_STRING_DFA_CPP

template<int W>
struct DFA {
    vector<array<int, W>> next;
    vector<char> accept;
    int initial = -1;
};

template<int W>
DFA<W> intersect(const DFA<W>& a, const DFA<W>& b) {
    if (a.initial == -1 || b.initial == -1) return {};
    size_t width = b.next.size();
    assert(a.next.size() <= vector<int>().max_size() / width);
    vector<int> id(a.next.size() * width, -1);
    vector<pair<int, int>> states;
    DFA<W> result;
    auto add = [&](int x, int y) {
        int& index = id[size_t(x) * width + y];
        if (index == -1) {
            index = (int)states.size();
            states.emplace_back(x, y);
            result.next.emplace_back();
            result.accept.push_back(a.accept[x] && b.accept[y]);
        }
        return index;
    };
    result.initial = add(a.initial, b.initial);
    for (int i = 0; i < (int)states.size(); ++i) {
        auto [x, y] = states[i];
        for (int c = 0; c < W; ++c) {
            int nx = a.next[x][c], ny = b.next[y][c];
            int to = nx == -1 || ny == -1 ? -1 : add(nx, ny);
            result.next[i][c] = to;
        }
    }
    return result;
}

#endif

/**
 * @brief 有限オートマトンと条件の合成
 */
