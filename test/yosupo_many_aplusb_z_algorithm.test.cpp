#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <random>
#include <string>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../string/z-algorithm.cpp"

vector<int> brute_z(const string &s) {
    int n = (int)s.size();
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        while (i + res[i] < n && s[res[i]] == s[i + res[i]]) ++res[i];
    }
    return res;
}

int main() {
    {
        mt19937 rng(123456789);
        vector<string> samples = {
            "a",
            "aaaaa",
            "ababa",
            "aabcaabxaaaz",
            "abracadabra"
        };
        for (const string &s : samples) {
            if (Z_algorithm(s) != brute_z(s)) return 1;
        }
        for (int n = 1; n <= 120; ++n) {
            for (int trial = 0; trial < 400; ++trial) {
                string s(n, 'a');
                for (int i = 0; i < n; ++i) {
                    s[i] = char('a' + uniform_int_distribution<int>(0, 3)(rng));
                }
                if (Z_algorithm(s) != brute_z(s)) return 1;
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
