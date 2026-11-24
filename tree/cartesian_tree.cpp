#ifndef FIRIEXP_LIBRARY_TREE_CARTESIAN_TREE_CPP
#define FIRIEXP_LIBRARY_TREE_CARTESIAN_TREE_CPP

struct CartesianTree {
    int root;
    vector<int> parent, left, right;
};

template<class T>
CartesianTree cartesian_tree(const vector<T> &a) {
    int n = a.size();
    CartesianTree tree{-1, vector<int>(n, -1), vector<int>(n, -1), vector<int>(n, -1)};
    for (int i = 0; i < n; ++i) {
        int p = i - 1, last = -1;
        while (p != -1 && a[i] < a[p]) {
            last = p;
            p = tree.parent[p];
        }
        tree.left[i] = last;
        if (last != -1) tree.parent[last] = i;
        tree.parent[i] = p;
        if (p == -1) tree.root = i;
        else tree.right[p] = i;
    }
    return tree;
}

#endif

/**
 * @brief Cartesian Tree
 */
