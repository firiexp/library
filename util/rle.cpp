namespace rle_detail {

template<class Sequence>
vector<pair<typename Sequence::value_type, int>> encode(const Sequence& a) {
    vector<pair<typename Sequence::value_type, int>> p;
    if(a.empty()) return p;
    p.emplace_back(a[0], 1);
    for (int j = 1; j < (int)a.size(); ++j) {
        if(p.back().first == a[j]) p.back().second++;
        else p.emplace_back(a[j], 1);
    }
    return p;
}

}

template<class T>
vector<pair<T, int>> RLE(const vector<T>& a) {
    return rle_detail::encode(a);
}

vector<pair<char, int>> RLE(string_view s) {
    return rle_detail::encode(s);
}

/**
 * @brief ランレングス圧縮(RLE)
 */
