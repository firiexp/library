#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../tree/dynamic_tree/euler_tour_tree.cpp"
#include "../tree/dynamic_tree/euler_tour_tree.cpp"

vector<int> component(const vector<vector<bool>> &adj, int v, int p = -1) {
    vector<bool> seen(adj.size());
    vector<int> result{v};
    seen[v] = true;
    if (p != -1) seen[p] = true;
    for (int i = 0; i < (int)result.size(); ++i) {
        for (int u = 0; u < (int)adj.size(); ++u) {
            if (!adj[result[i]][u] || seen[u]) continue;
            seen[u] = true;
            result.push_back(u);
        }
    }
    return result;
}

void check_storage(const EulerTourTree &tree) {
    int n = tree.n, size = tree.nodes.size();
    assert(size <= max(n, 3 * n - 2));
    assert(size == n + 2 * (int)tree.edges.size() + (int)tree.free_nodes.size());
    vector<bool> seen(size);
    for (int v : tree.free_nodes) {
        assert(n <= v && v < size && !seen[v]);
        seen[v] = true;
    }
    vector<int> stack;
    for (int v = 0; v < size; ++v) {
        if (!seen[v] && tree.nodes[v].parent == -1) stack.push_back(v);
    }
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        assert(!seen[v]);
        seen[v] = true;
        const auto &node = tree.nodes[v];
        int count = v < n;
        long long sum = node.value;
        if (v >= n) assert(node.value == 0);
        for (int child : {node.left, node.right}) {
            if (child == -1) continue;
            assert(tree.nodes[child].parent == v);
            count += tree.nodes[child].count;
            sum += tree.nodes[child].sum;
            stack.push_back(child);
        }
        assert(count == node.count);
        assert(sum + node.lazy * (count - (v < n)) == node.sum);
    }
    assert(all_of(seen.begin(), seen.end(), [](bool value) { return value; }));
}

void random_forest(int n, mt19937 &rng) {
    vector<long long> value(n);
    for (auto &x : value) x = (int)(rng() % 201) - 100;
    EulerTourTree tree(value);
    vector<vector<bool>> adj(n, vector<bool>(n));
    for (int v = 1; v < n; ++v) {
        int p = rng() % v;
        assert(tree.link(v, p));
        adj[v][p] = adj[p][v] = true;
    }
    auto add_edge = [&](int u, int v) {
        auto side = component(adj, u);
        bool valid = find(side.begin(), side.end(), v) == side.end();
        assert(tree.link(u, v) == valid);
        if (valid) adj[u][v] = adj[v][u] = true;
    };
    auto remove_edge = [&](int u, int v) {
        assert(tree.cut(u, v) == adj[u][v]);
        adj[u][v] = adj[v][u] = false;
    };
    auto check_sum = [&](int v, int p) {
        long long expected = 0;
        auto vertices = component(adj, v, p);
        for (int u : vertices) expected += value[u];
        auto info = tree.subtree_info(v, p);
        assert(info.size == (int)vertices.size() && info.sum == expected);
        assert(tree.subtree_sum(v, p) == expected);
    };
    for (int step = 0; step < 1000; ++step) {
        int v = rng() % n, u = rng() % n, p = -1;
        vector<int> neighbors;
        vector<pair<int, int>> edges;
        for (int a = 0; a < n; ++a) {
            if (adj[v][a]) neighbors.push_back(a);
            for (int b = a + 1; b < n; ++b) {
                if (adj[a][b]) edges.emplace_back(a, b);
            }
        }
        if (!neighbors.empty() && rng() % 4) p = neighbors[rng() % neighbors.size()];
        long long delta = (int)(rng() % 101) - 50;
        int operation = rng() % 10;
        if (operation <= 1) {
            add_edge(u, v);
        } else if (operation == 2) {
            if (!edges.empty() && rng() % 2) tie(u, v) = edges[rng() % edges.size()];
            remove_edge(u, v);
        } else if (operation == 3 && !edges.empty()) {
            tie(u, v) = edges[rng() % edges.size()];
            if (rng() % 2) swap(u, v);
            remove_edge(u, v);
            auto a = component(adj, u), b = component(adj, v);
            add_edge(a[rng() % a.size()], b[rng() % b.size()]);
        } else if (operation <= 5) {
            tree.subtree_add(v, p, delta);
            for (int x : component(adj, v, p)) value[x] += delta;
        } else if (operation == 6) {
            tree.vertex_add(v, delta);
            value[v] += delta;
        } else if (operation == 7) {
            check_sum(v, p);
        } else if (operation == 8) {
            auto side = component(adj, u);
            assert(tree.connected(u, v) == (find(side.begin(), side.end(), v) != side.end()));
        } else {
            assert(tree.get(v) == value[v]);
        }
        if (step % 17 == 0) {
            check_storage(tree);
            for (int x = 0; x < n; ++x) {
                assert(tree.get(x) == value[x]);
                check_sum(x, -1);
            }
            for (auto [a, b] : edges) {
                if (!adj[a][b]) continue;
                check_sum(a, b);
                check_sum(b, a);
            }
        }
    }
    for (int v = 0; v < n; ++v) assert(tree.get(v) == value[v]);
    check_storage(tree);
}

void subtree_info_regression() {
    EulerTourTree tree(vector<long long>{1, 2, 3, 4, 5});
    auto check = [&](int v, int p, int size, long long sum) {
        auto info = tree.subtree_info(v, p);
        assert(info.size == size && info.sum == sum);
        assert(tree.subtree_sum(v, p) == sum);
        check_storage(tree);
    };
    check(4, -1, 1, 5);
    assert(tree.link(0, 1) && tree.link(1, 2) && tree.link(1, 3));
    check(1, 0, 3, 9);
    check(0, 1, 1, 1);
    tree.subtree_add(1, 0, 10);
    check(1, 0, 3, 39);
    check(0, -1, 4, 40);
    size_t storage = tree.nodes.size();
    assert(tree.cut(2, 1));
    check(2, -1, 1, 13);
    assert(tree.link(4, 2));
    assert(tree.nodes.size() == storage && tree.free_nodes.empty());
    check(4, -1, 2, 18);
    tree.subtree_add(2, 4, -3);
    tree.vertex_add(4, 7);
    check(2, 4, 1, 10);
    check(4, 2, 1, 12);
    assert(tree.get(2) == 10 && tree.get(4) == 12);
    assert(!tree.connected(0, 2) && tree.connected(2, 4));
    assert(tree.link(1, 2));
    check(1, 0, 4, 48);
    check(4, -1, 5, 49);
}

void long_path() {
    int n = 200000, k = n / 2;
    EulerTourTree tree(vector<long long>(n, 1));
    for (int v = 1; v < n; ++v) assert(tree.link(v - 1, v));
    size_t size = tree.nodes.size();
    assert(size == 3 * (size_t)n - 2);
    long long left = 1, right = 1;
    for (int step = 0; step < 100000; ++step) {
        if (step % 2) {
            tree.subtree_add(k - 1, k, 2);
            left += 2;
        } else {
            tree.subtree_add(k, k - 1, 1);
            ++right;
        }
        if (step % 2) assert(tree.cut(k - 1, k));
        else assert(tree.cut(k, k - 1));
        assert(!tree.connected(0, n - 1));
        auto left_info = tree.subtree_info(0, -1);
        auto right_info = tree.subtree_info(n - 1, -1);
        assert(left_info.size == k && left_info.sum == k * left);
        assert(right_info.size == n - k && right_info.sum == (n - k) * right);
        assert(tree.subtree_sum(0, -1) == k * left);
        assert(tree.subtree_sum(n - 1, -1) == (n - k) * right);
        assert(tree.free_nodes.size() == 2);
        if (step % 2) assert(tree.link(k, k - 1));
        else assert(tree.link(k - 1, k));
        assert(tree.nodes.size() == size && tree.free_nodes.empty());
    }
    assert(tree.subtree_sum(k, k - 1) == (n - k) * right);
    assert(tree.subtree_sum(k - 1, k) == k * left);
    check_storage(tree);
}

int main() {
    EulerTourTree empty(vector<long long>{});
    check_storage(empty);
    subtree_info_regression();
    for (unsigned seed : {1u, 314159u, 271828u}) {
        mt19937 rng(seed);
        for (int n : {1, 2, 3, 8, 17, 32}) {
            for (int repeat = 0; repeat < 5; ++repeat) random_forest(n, rng);
        }
    }
    long_path();
}
