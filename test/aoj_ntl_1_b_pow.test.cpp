#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/modular/pow.cpp"

int main() {
    Scanner sc;
    Printer pr;
    long long a, n;
    sc.read(a, n);
    pr.println(pow_(a, n, 1000000007LL));
}
