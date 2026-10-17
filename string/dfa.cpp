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

template<int W>
DFA<W> unite(const DFA<W>& a, const DFA<W>& b) {
    if (a.initial == -1 && b.initial == -1) return {};
    size_t width = b.next.size() + 1;
    assert(a.next.size() + 1 <= vector<int>().max_size() / width);
    vector<int> id((a.next.size() + 1) * width, -1);
    vector<pair<int, int>> states;
    DFA<W> result;
    auto add = [&](int x, int y) {
        if (x == -1 && y == -1) return -1;
        int& index = id[size_t(x + 1) * width + (y + 1)];
        if (index == -1) {
            index = (int)states.size();
            states.emplace_back(x, y);
            result.next.emplace_back();
            result.accept.push_back((x != -1 && a.accept[x]) || (y != -1 && b.accept[y]));
        }
        return index;
    };
    result.initial = add(a.initial, b.initial);
    for (int i = 0; i < (int)states.size(); ++i) {
        auto [x, y] = states[i];
        for (int c = 0; c < W; ++c) {
            int nx = x == -1 ? -1 : a.next[x][c];
            int ny = y == -1 ? -1 : b.next[y][c];
            int to = add(nx, ny);
            result.next[i][c] = to;
        }
    }
    return result;
}

template<int W>
DFA<W> complement(const DFA<W>& a) {
    if (a.initial == -1) {
        DFA<W> result{vector<array<int, W>>(1), {true}, 0};
        result.next[0].fill(0);
        return result;
    }
    DFA<W> result = a;
    for (auto& accept : result.accept) accept = !accept;
    int sink = (int)result.next.size();
    bool needed = false;
    for (auto& row : result.next) {
        for (int& to : row) if (to == -1) {
            to = sink;
            needed = true;
        }
    }
    if (needed) {
        result.next.emplace_back();
        result.next.back().fill(sink);
        result.accept.push_back(true);
    }
    return result;
}

#endif

/**
 * @brief 有限オートマトンと条件の合成
 */
