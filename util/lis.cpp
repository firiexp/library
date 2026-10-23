template<class T>
int lis_length(const vector<T>& a, bool strict = true) {
    vector<T> tails;
    for (const T& value : a) {
        auto it = strict ? lower_bound(tails.begin(), tails.end(), value)
                         : upper_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return (int)tails.size();
}

template<class T>
vector<int> lis_indices(const vector<T> &a, bool strict = true) {
    vector<int> tails, previous(a.size(), -1);
    for (int i = 0; i < (int)a.size(); ++i) {
        int l = 0, r = tails.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (strict ? a[tails[m]] < a[i] : !(a[i] < a[tails[m]])) l = m + 1;
            else r = m;
        }
        if (l) previous[i] = tails[l - 1];
        if (l == (int)tails.size()) tails.push_back(i);
        else tails[l] = i;
    }
    vector<int> result(tails.size());
    int v = tails.empty() ? -1 : tails.back();
    for (int i = (int)result.size() - 1; i >= 0; --i) {
        result[i] = v;
        v = previous[v];
    }
    return result;
}

/**
 * @brief 最長増加部分列
 */
