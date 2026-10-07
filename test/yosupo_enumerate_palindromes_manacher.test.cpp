#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../string/manacher.cpp"

int main() {
    Scanner sc;
    Printer pr;

    string s;
    sc.read(s);
    PalindromeRadii radii(s);
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i) {
            pr.print(' ');
            pr.print(2 * radii.even[i]);
            pr.print(' ');
        }
        pr.print(2 * radii.odd[i] - 1);
    }
    pr.println();
    return 0;
}
