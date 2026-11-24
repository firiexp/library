#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../tree/cartesian_tree.cpp"

void check(const vector<int> &a) {
    auto tree = cartesian_tree(a);
    assert(tree.parent.size() == a.size());
    assert(tree.left.size() == a.size());
    assert(tree.right.size() == a.size());

    int visited = 0;
    auto check_subtree = [&](auto &self, int l, int r, int v, int parent) -> void {
        if (l == r) {
            assert(v == -1);
            return;
        }
        int first_min = min_element(a.begin() + l, a.begin() + r) - a.begin();
        assert(v == first_min && tree.parent[v] == parent);
        self(self, l, v, tree.left[v], v);
        assert(v == visited);
        ++visited;
        self(self, v + 1, r, tree.right[v], v);
    };
    check_subtree(check_subtree, 0, a.size(), tree.root, -1);
    assert(visited == (int)a.size());
}

int main() {
    for (int n = 0, count = 1; n <= 8; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            int code = mask;
            vector<int> a(n);
            for (int &x : a) {
                x = code % 3 - 1;
                code /= 3;
            }
            check(a);
        }
    }
    vector<int> a(100);
    iota(a.begin(), a.end(), 0);
    check(a);
    reverse(a.begin(), a.end());
    check(a);
}
