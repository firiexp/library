template<class T>
pair<vector<vector<int>>, int> CartesianTree(const vector<T> &a) {
    int n = a.size();
    vector<vector<int>> g(n);
    vector<int> parent(n, -1), st;
    st.reserve(n);
    for (int i = 0; i < n; ++i) {
        int last = -1;
        while (!st.empty() && a[i] < a[st.back()]) {
            last = st.back();
            st.pop_back();
        }
        if (last != -1) parent[last] = i;
        if (!st.empty()) parent[i] = st.back();
        st.push_back(i);
    }
    int root = -1;
    for (int i = 0; i < n; ++i) {
        if (parent[i] == -1) root = i;
        else g[parent[i]].push_back(i);
    }
    return {g, root};
}

/**
 * @brief Cartesian Tree
 */
