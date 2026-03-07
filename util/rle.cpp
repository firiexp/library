template<class T>
vector<pair<T, int>> RLE(const vector<T> &a){
    vector<pair<T, int>> p;
    if(a.empty()) return p;
    p.emplace_back(a[0], 1);
    for (int j = 1; j < (int)a.size(); ++j) {
        if(p.back().first == a[j]) p.back().second++;
        else p.emplace_back(a[j], 1);
    }
    return p;
}
