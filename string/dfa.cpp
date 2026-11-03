#ifndef FIRIEXP_LIBRARY_STRING_DFA_CPP
#define FIRIEXP_LIBRARY_STRING_DFA_CPP

template<int W>
struct DFA {
    vector<array<int, W>> next;
    vector<char> accept;
    int initial = -1;
};

namespace dfa_detail {

template<bool Union, bool Sparse, int W>
DFA<W> product(const DFA<W>& a, const DFA<W>& b) {
    if constexpr (Union) {
        if (a.initial == -1 && b.initial == -1) return {};
    } else {
        if (a.initial == -1 || b.initial == -1) return {};
    }
    size_t width = b.next.size() + Union;
    conditional_t<Sparse, unordered_map<unsigned long long, int>, vector<int>> id;
    if constexpr (!Sparse) {
        assert(a.next.size() + Union <= vector<int>().max_size() / width);
        id.assign((a.next.size() + Union) * width, -1);
    }
    vector<pair<int, int>> states;
    DFA<W> result;
    auto add = [&](int x, int y) {
        if constexpr (Union) {
            if (x == -1 && y == -1) return -1;
        } else {
            if (x == -1 || y == -1) return -1;
        }
        int index = states.size();
        if constexpr (Sparse) {
            auto key = (static_cast<unsigned long long>(x + 1) << 32) | unsigned(y + 1);
            auto [it, inserted] = id.try_emplace(key, index);
            if (!inserted) return it->second;
        } else {
            int& entry = id[size_t(x + Union) * width + (y + Union)];
            if (entry != -1) return entry;
            entry = index;
        }
        states.emplace_back(x, y);
        result.next.emplace_back();
        if constexpr (Union) {
            result.accept.push_back((x != -1 && a.accept[x]) || (y != -1 && b.accept[y]));
        } else {
            result.accept.push_back(a.accept[x] && b.accept[y]);
        }
        return index;
    };
    result.initial = add(a.initial, b.initial);
    for (int i = 0; i < (int)states.size(); ++i) {
        auto [x, y] = states[i];
        for (int c = 0; c < W; ++c) {
            int nx, ny;
            if constexpr (Union) {
                nx = x == -1 ? -1 : a.next[x][c];
                ny = y == -1 ? -1 : b.next[y][c];
            } else {
                nx = a.next[x][c];
                ny = b.next[y][c];
            }
            int to = add(nx, ny);
            result.next[i][c] = to;
        }
    }
    return result;
}

}

template<int W>
DFA<W> intersect(const DFA<W>& a, const DFA<W>& b) {
    return dfa_detail::product<false, false>(a, b);
}

template<int W>
DFA<W> unite(const DFA<W>& a, const DFA<W>& b) {
    return dfa_detail::product<true, false>(a, b);
}

template<int W>
DFA<W> intersect_sparse(const DFA<W>& a, const DFA<W>& b) {
    return dfa_detail::product<false, true>(a, b);
}

template<int W>
DFA<W> unite_sparse(const DFA<W>& a, const DFA<W>& b) {
    return dfa_detail::product<true, true>(a, b);
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
