#ifndef FIRIEXP_LIBRARY_STRING_DFA_MINIMIZE_CPP
#define FIRIEXP_LIBRARY_STRING_DFA_MINIMIZE_CPP

#include "dfa.cpp"

template<int W>
DFA<W> minimize(const DFA<W>& a) {
    if (a.initial == -1) return {};
    vector<int> index(a.next.size(), -1), states{a.initial};
    index[a.initial] = 0;
    for (size_t i = 0; i < states.size(); ++i) {
        for (int to : a.next[states[i]]) {
            if (to != -1 && index[to] == -1) {
                index[to] = (int)states.size();
                states.push_back(to);
            }
        }
    }
    int sink = (int)states.size();
    assert(sink < numeric_limits<int>::max());
    int n = sink + 1;
    vector<int> order;
    order.reserve(n);
    for (int v = 0; v < sink; ++v) if (a.accept[states[v]]) order.push_back(v);
    int accepted = (int)order.size();
    if (accepted == 0) return {};
    for (int v = 0; v < sink; ++v) if (!a.accept[states[v]]) order.push_back(v);
    order.push_back(sink);
    vector<array<int, W>> head(n), link(n);
    for (auto& row : head) row.fill(-1);
    for (int v = 0; v < n; ++v) {
        for (int c = 0; c < W; ++c) {
            int to = v == sink ? -1 : a.next[states[v]][c];
            to = to == -1 ? sink : index[to];
            link[v][c] = head[to][c];
            head[to][c] = v;
        }
    }
    vector<int> group(n), position(n), begin{0, accepted}, end{accepted, n}, marked{0, accepted};
    for (int i = 0; i < n; ++i) group[order[i]] = i >= accepted, position[order[i]] = i;
    vector<int> pending{accepted <= n - accepted ? 0 : 1}, splitter, touched;
    while (!pending.empty()) {
        int block = pending.back();
        pending.pop_back();
        splitter.assign(order.begin() + begin[block], order.begin() + end[block]);
        for (int c = 0; c < W; ++c) {
            touched.clear();
            for (int to : splitter) {
                for (int v = head[to][c]; v != -1; v = link[v][c]) {
                    int b = group[v];
                    if (marked[b] == begin[b]) touched.push_back(b);
                    int i = position[v], j = marked[b]++;
                    swap(order[i], order[j]);
                    position[order[i]] = i;
                    position[order[j]] = j;
                }
            }
            for (int b : touched) {
                int mid = marked[b], l = begin[b], r = end[b];
                if (mid != r) {
                    int id = (int)begin.size();
                    if (mid - l <= r - mid) {
                        begin.push_back(l);
                        end.push_back(mid);
                        begin[b] = mid;
                    } else {
                        begin.push_back(mid);
                        end.push_back(r);
                        end[b] = mid;
                    }
                    marked.push_back(begin[id]);
                    for (int i = begin[id]; i < end[id]; ++i) group[order[i]] = id;
                    pending.push_back(id);
                }
                marked[b] = begin[b];
            }
        }
    }
    int dead = group[sink];
    if (group[0] == dead) return {};
    vector<int> id(begin.size(), -1), queue{group[0]};
    id[group[0]] = 0;
    DFA<W> result;
    result.initial = 0;
    for (size_t i = 0; i < queue.size(); ++i) {
        int v = states[order[begin[queue[i]]]];
        array<int, W> row;
        for (int c = 0; c < W; ++c) {
            int to = a.next[v][c];
            int b = to == -1 ? dead : group[index[to]];
            if (b == dead) row[c] = -1;
            else {
                if (id[b] == -1) {
                    id[b] = (int)queue.size();
                    queue.push_back(b);
                }
                row[c] = id[b];
            }
        }
        result.next.push_back(row);
        result.accept.push_back(bool(a.accept[v]));
    }
    return result;
}

#endif

/**
 * @brief 有限オートマトンの最小化
 */
