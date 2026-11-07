template<class Sequence>
vector<int> kmp_table(const Sequence &s) {
    int n = s.size();
    vector<int> table(n + 1);
    table[0] = -1;
    for (int i = 0, j = -1; i < n;) {
        while (j >= 0 && !(s[i] == s[j])) j = table[j];
        i++, j++;
        table[i] = j;
    }
    return table;
}

inline vector<int> kmp_table(const char *s) {
    return kmp_table(string_view(s));
}

template<class Text, class Pattern>
auto kmp_search(const Text &text, const Pattern &pattern)
    -> decltype(text.size(), pattern.size(), vector<int>()) {
    int n = text.size(), m = pattern.size();
    vector<int> res;
    if(pattern.empty()){
        res.resize(n + 1);
        iota(res.begin(), res.end(), 0);
        return res;
    }
    auto table = kmp_table(pattern);
    for (int i = 0, j = 0; i < n;) {
        while (j >= 0 && !(text[i] == pattern[j])) j = table[j];
        i++, j++;
        if(j == m){
            res.emplace_back(i - j);
            j = table[j];
        }
    }
    return res;
}

inline vector<int> kmp_search(string_view text, string_view pattern) {
    return kmp_search<string_view, string_view>(text, pattern);
}

template<class T = char>
class KMPMatcher {
    vector<T> pattern;
    vector<int> table;
    int matched = 0;
    long long position = 0;
    bool announced = false;

public:
    explicit KMPMatcher(vector<T> input): pattern(move(input)), table(kmp_table(pattern)) {}

    explicit KMPMatcher(string_view input): pattern(input.begin(), input.end()), table(kmp_table(pattern)) {}

    void reset() {
        matched = 0;
        position = 0;
        announced = false;
    }

    template<class Iterator, class Emit>
    void scan(Iterator first, Iterator last, Emit &&emit) {
        if (pattern.empty()) {
            if (!announced) {
                announced = true;
                emit(position);
            }
            for (; first != last; ++first) emit(++position);
            return;
        }
        for (; first != last; ++first) {
            while (matched >= 0 && !(*first == pattern[matched])) matched = table[matched];
            ++matched;
            ++position;
            if (matched == (int)pattern.size()) {
                matched = table[matched];
                emit(position - (long long)pattern.size());
            }
        }
    }

    template<class Emit>
    void scan(string_view chunk, Emit &&emit) {
        scan(chunk.begin(), chunk.end(), forward<Emit>(emit));
    }

    template<class Emit>
    void scan(const vector<T> &chunk, Emit &&emit) {
        scan(chunk.begin(), chunk.end(), forward<Emit>(emit));
    }
};

KMPMatcher(string_view) -> KMPMatcher<char>;

/**
 * @brief KMP法
 */
