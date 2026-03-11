#define PROBLEM "https://yukicoder.me/problems/no/957"

#include <algorithm>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

using ll = long long;
template<class T>
constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../flow/project_selection_problem.cpp"

int main() {
    Scanner in;
    Printer out;

    int h, w;
    in.read(h, w);

    vector<vector<ll>> g(h, vector<ll>(w));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            in.read(g[i][j]);
        }
    }
    vector<ll> row(h), col(w);
    for (int i = 0; i < h; ++i) in.read(row[i]);
    for (int j = 0; j < w; ++j) in.read(col[j]);

    ProjectSelectionProblem<ll> psp(h + w);
    for (int i = 0; i < h; ++i) {
        ll sum = 0;
        for (int j = 0; j < w; ++j) {
            sum += g[i][j];
            psp.add_penalty(h + j, i, g[i][j]);
        }
        psp.add_true_profit(i, row[i] - sum);
    }
    for (int j = 0; j < w; ++j) {
        psp.add_true_profit(h + j, col[j]);
    }

    out.writeln(psp.solve());
    return 0;
}
