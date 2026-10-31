#define PROBLEM "https://yukicoder.me/problems/no/2672"

#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <vector>
using namespace std;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/linear_algebra/xor_basis.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    XorBasis<int> xb;
    int total = 0;
    for (int i = 0; i < n; ++i) {
        int a;
        sc.read(a);
        xb.add(a);
        total ^= a;
    }
    pr.println(total == 0 && xb.size() < n - 1 ? "Yes" : "No");
    return 0;
}
