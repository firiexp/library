#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <random>
#include <string>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../string/lyndon_factorization.cpp"

static bool is_lyndon(const string &t) {
    if (t.empty()) return false;
    for (int i = 1; i < (int)t.size(); ++i) {
        if (!(t < t.substr(i))) return false;
    }
    return true;
}

static vector<string> to_words(const string &s, const vector<pair<int, int>> &segs) {
    vector<string> res;
    for (auto &&[l, r] : segs) {
        if (!(0 <= l && l < r && r <= (int)s.size())) return {};
        res.push_back(s.substr(l, r - l));
    }
    return res;
}

static vector<string> brute(const string &s) {
    vector<string> best, cur;
    auto dfs = [&](auto &&self, int pos) -> void {
        if (pos == (int)s.size()) {
            if (best.empty()) best = cur;
            return;
        }
        for (int r = pos + 1; r <= (int)s.size(); ++r) {
            string t = s.substr(pos, r - pos);
            if (!is_lyndon(t)) continue;
            if (!cur.empty() && cur.back() < t) continue;
            cur.push_back(t);
            self(self, r);
            cur.pop_back();
        }
    };
    dfs(dfs, 0);
    return best;
}

int main() {
    {
        mt19937 rng(123456789);
        vector<string> samples = {
            "",
            "a",
            "aaaaa",
            "ababbab",
            "banana",
            "mississippi"
        };
        for (const string &s : samples) {
            auto got = to_words(s, lyndon_factorization(s));
            auto expect = brute(s);
            if (got != expect) return 1;
        }
        for (int n = 0; n <= 11; ++n) {
            for (int trial = 0; trial < 400; ++trial) {
                string s(n, 'a');
                for (int i = 0; i < n; ++i) {
                    s[i] = char('a' + uniform_int_distribution<int>(0, 2)(rng));
                }
                auto got = to_words(s, lyndon_factorization(s));
                auto expect = brute(s);
                if (got != expect) return 1;
            }
        }
        for (int n = 12; n <= 200; n += 17) {
            for (int trial = 0; trial < 120; ++trial) {
                string s(n, 'a');
                for (int i = 0; i < n; ++i) {
                    s[i] = char('a' + uniform_int_distribution<int>(0, 3)(rng));
                }
                auto segs = lyndon_factorization(s);
                auto got = to_words(s, segs);
                int pos = 0;
                for (auto &&[l, r] : segs) {
                    if (l != pos) return 1;
                    pos = r;
                }
                if (pos != n) return 1;
                string restored;
                for (auto &&t : got) {
                    if (!is_lyndon(t)) return 1;
                    restored += t;
                }
                if (restored != s) return 1;
                for (int i = 1; i < (int)got.size(); ++i) {
                    if (got[i - 1] < got[i]) return 1;
                }
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
