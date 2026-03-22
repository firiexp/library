#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../string/manacher.cpp"

int main() {
    Scanner sc;
    Printer pr;

    string s;
    sc.read(s);
    string t;
    t.reserve(max(0, (int)s.size() * 2 - 1));
    for (char c : s) {
        if (!t.empty()) t.push_back('$');
        t.push_back(c);
    }
    auto ans = manacher(t);
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i & 1) ans[i] = (ans[i] / 2) * 2;
        else ans[i] = ((ans[i] + 1) / 2) * 2 - 1;
    }
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) pr.print(' ');
        pr.print(ans[i]);
    }
    pr.println();
    return 0;
}
