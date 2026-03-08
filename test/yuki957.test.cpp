#define PROBLEM "https://yukicoder.me/problems/no/957"

#include <algorithm>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

using ll = long long;
template<class T>
constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

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

    ProjectSelectionProblem<ll> psp(h * w);
    vector<int> row_id(h), col_id(w);
    for (int i = 0; i < h; ++i) row_id[i] = psp.add_vertex();
    for (int j = 0; j < w; ++j) col_id[j] = psp.add_vertex();

    auto cell = [&](int i, int j) {
        return i * w + j;
    };

    for (int i = 0; i < h; ++i) {
        psp.add_true_profit(row_id[i], row[i]);
        for (int j = 0; j < w; ++j) {
            psp.add_if_then(row_id[i], cell(i, j));
        }
    }
    for (int j = 0; j < w; ++j) {
        psp.add_true_profit(col_id[j], col[j]);
        for (int i = 0; i < h; ++i) {
            psp.add_if_then(col_id[j], cell(i, j));
        }
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            psp.add_false_profit(cell(i, j), g[i][j]);
        }
    }

    out.writeln(psp.solve());
    return 0;
}
