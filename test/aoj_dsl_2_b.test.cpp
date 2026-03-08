#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/binaryindexedtree.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, q;
    in.read(n, q);
    BIT<int> s(n);
    for (int i = 0; i < q; ++i) {
        int c, x, y;
        in.read(c, x, y);
        x--;
        if (c == 0) s.add(x, y);
        else out.writeln(s.sum(y) - s.sum(x));
    }
    return 0;
}
