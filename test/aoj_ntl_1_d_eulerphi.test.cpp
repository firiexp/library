#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D"

#include <algorithm>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/prime/eulerphi.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    pr.println(eulerphi(n));
    return 0;
}
