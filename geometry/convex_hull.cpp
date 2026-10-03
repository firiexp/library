using IntPoint = pair<ll, ll>;

__int128 cross(IntPoint a, IntPoint b, IntPoint c) {
    __int128 bx = static_cast<__int128>(b.first) - a.first;
    __int128 by = static_cast<__int128>(b.second) - a.second;
    __int128 cx = static_cast<__int128>(c.first) - a.first;
    __int128 cy = static_cast<__int128>(c.second) - a.second;
    return bx * cy - by * cx;
}

vector<IntPoint> convex_hull(vector<IntPoint> ps) {
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    int n = ps.size();
    if (n <= 2) return ps;

    vector<IntPoint> ch(2 * n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
        ch[k++] = ps[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
        ch[k++] = ps[i];
    }
    ch.resize(k - 1);
    return ch;
}

/**
 * @brief 凸包(Convex Hull)
 */
