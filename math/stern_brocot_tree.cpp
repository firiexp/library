using namespace std;

namespace SternBrocotTree {

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
    if (k < 0) return {{Left, -1}};
    vector<Move> ret;
    for (auto move : path) {
        if (k == 0) break;
        ll steps = min(move.steps, k);
        ret.push_back({move.dir, steps});
        k -= steps;
    }
    if (k != 0) return {{Left, -1}};
    return ret;
}

Node ancestor(ll a, ll b, ll k) {
    auto path = ancestor_path(encode_path(a, b), k);
    if (!path.empty() && path[0].steps < 0) return Node(-1, -1, 0, 0);
    return decode_path(path);
}

template<class Pred>
pair<pair<ll, ll>, pair<ll, ll>> binary_search(ll max_num, ll max_den, Pred pred) {
    assert(max_num >= 0 && max_den >= 0);
    pair<ll, ll> left{0, 1}, right{1, 0};
    while (left.first <= max_num - right.first && left.second <= max_den - right.second) {
        bool update_left = pred(left.first + right.first, left.second + right.second);
        auto& from = update_left ? left : right;
        const auto& toward = update_left ? right : left;
        ll limit = max(max_num, max_den);
        if (toward.first) limit = (max_num - from.first) / toward.first;
        if (toward.second) limit = min(limit, (max_den - from.second) / toward.second);
        auto same_side = [&](ll steps) {
            return bool(pred(from.first + steps * toward.first,
                             from.second + steps * toward.second)) == update_left;
        };
        ll steps = 1;
        while (steps <= limit / 2 && same_side(2 * steps)) steps *= 2;
        for (ll bit = steps / 2; bit > 0; bit /= 2) {
            if (bit <= limit - steps && same_side(steps + bit)) steps += bit;
        }
        from.first += steps * toward.first;
        from.second += steps * toward.second;
    }
    return {left, right};
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
