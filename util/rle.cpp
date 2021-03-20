template<class T>
vector<pair<T, int>> RLE(vector<T> &a){
    vector<pair<int, int>> p;
    p.emplace_back(a[0], 1);
    for (int j = 1; j < a.size(); ++j) {
        if(p.back().first == a[j]) p.back().second++;
        else p.emplace_back(a[j], 1);
    }
    return p;
}
