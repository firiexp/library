#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"

#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../string/lyndon_factorization.cpp"

int main() {
    Scanner sc;
    Printer pr;

    string s;
    sc.read(s);
    auto seg = lyndon_factorization(s);
    pr.write(0);
    for (auto &&p : seg) {
        pr.write(' ');
        pr.write(p.second);
    }
    pr.writeln();
    return 0;
}
