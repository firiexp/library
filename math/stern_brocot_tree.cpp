using namespace std;

namespace SternBrocotTree {

using ll = long long;

enum Direction {
    Left,
    Right
};

struct Move {
    Direction dir;
    ll steps;
};

struct Node {
    ll p, q, r, s;

    Node() : p(0), q(1), r(1), s(0) {}
    Node(ll p, ll q, ll r, ll s) : p(p), q(q), r(r), s(s) {}

    ll num() const { return p + r; }
    ll den() const { return q + s; }
};

Node apply(Node node, Move move) {
    if (move.steps == 0) return node;
    if (move.dir == Left) {
        node.r += node.p * move.steps;
        node.s += node.q * move.steps;
    } else {
        node.p += node.r * move.steps;
        node.q += node.s * move.steps;
    }
    return node;
}

Node decode_path(const vector<Move>& path) {
    Node node;
    for (auto move : path) node = apply(node, move);
    return node;
}

vector<Move> encode_path(ll a, ll b) {
    assert(a > 0 && b > 0);
    vector<Move> path;
    while (a != b) {
        if (a < b) {
            ll steps = (b - 1) / a;
            path.push_back({Left, steps});
            b -= steps * a;
        } else {
            ll steps = (a - 1) / b;
            path.push_back({Right, steps});
            a -= steps * b;
        }
    }
    return path;
}

ll depth(const vector<Move>& path) {
    ll ret = 0;
    for (auto move : path) ret += move.steps;
    return ret;
}

vector<Move> lca_path(const vector<Move>& a, const vector<Move>& b) {
    vector<Move> ret;
    int i = 0, j = 0;
    ll sa = 0, sb = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (sa == 0) sa = a[i].steps;
        if (sb == 0) sb = b[j].steps;
        if (a[i].dir != b[j].dir) break;
        ll steps = min(sa, sb);
        ret.push_back({a[i].dir, steps});
        sa -= steps;
        sb -= steps;
        if (sa == 0) ++i;
        if (sb == 0) ++j;
    }
    return ret;
}

vector<Move> ancestor_path(const vector<Move>& path, ll k) {
    vector<Move> ret;
    for (auto move : path) {
        if (k == 0) break;
        ll steps = min(move.steps, k);
        ret.push_back({move.dir, steps});
        k -= steps;
    }
    if (k != 0) return {};
    return ret;
}

Node range(ll a, ll b) {
    return decode_path(encode_path(a, b));
}

Node lca(ll a, ll b, ll c, ll d) {
    return decode_path(lca_path(encode_path(a, b), encode_path(c, d)));
}

}  // namespace SternBrocotTree

/**
 * @brief Stern-Brocot木
 */
