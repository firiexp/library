#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../string/z-algorithm.cpp"

int main() {
    Scanner sc;
    Printer pr;

    string s;
    sc.read(s);
    auto z = Z_algorithm(s);
    for (int i = 0; i < (int)z.size(); ++i) {
        if (i) pr.write(' ');
        pr.write(z[i]);
    }
    pr.writeln();
    return 0;
}
