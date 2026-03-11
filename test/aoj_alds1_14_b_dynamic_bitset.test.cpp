#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/dynamic_bitset.cpp"

int main() {
    Scanner sc;
    Printer pr;

    string text, pattern;
    sc.read(text, pattern);

    int m = pattern.size();
    if (m == 0) {
        for (int i = 0; i <= (int)text.size(); ++i) pr.writeln(i);
        return 0;
    }

    vector<DynamicBitset> mask(256, DynamicBitset(m));
    for (int i = 0; i < m; ++i) mask[(unsigned char)pattern[i]].set(i);

    DynamicBitset cur(m), head(m);
    head.set(0);
    for (int i = 0; i < (int)text.size(); ++i) {
        cur <<= 1;
        cur |= head;
        cur &= mask[(unsigned char)text[i]];
        if (cur.test(m - 1)) pr.writeln(i - m + 1);
    }
    return 0;
}
