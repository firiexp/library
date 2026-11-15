template<class T>
class UndoableLiChaoTree {
    struct Line {
        T a = 0, b = 0;
        int id = -1;

        T get(T x) const { return a * x + b; }
        bool better(const Line &other, T x) const {
            return make_pair(get(x), id) < make_pair(other.get(x), other.id);
        }
    };

    vector<T> xs;
    vector<Line> seg;
    vector<pair<int, Line>> history;

public:
    using Snapshot = size_t;

    explicit UndoableLiChaoTree(vector<T> coordinates) : xs(move(coordinates)) {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        seg.resize(max(size_t(1), 4 * xs.size()));
    }

    Snapshot snapshot() const { return history.size(); }

    void rollback(Snapshot state) {
        assert(state <= history.size());
        while (history.size() > state) {
            auto [k, line] = history.back();
            seg[k] = line;
            history.pop_back();
        }
    }

    void add_line(T a, T b, int id) {
        assert(id >= 0);
        Line line{a, b, id};
        int k = 1, l = 0, r = (int)xs.size();
        while (l < r) {
            if (seg[k].id == -1) {
                history.emplace_back(k, seg[k]);
                seg[k] = line;
                return;
            }
            int m = l + (r - l) / 2;
            bool left = line.better(seg[k], xs[l]);
            bool mid = line.better(seg[k], xs[m]);
            if (mid) {
                history.emplace_back(k, seg[k]);
                swap(seg[k], line);
            }
            if (r - l == 1) return;
            if (left != mid) {
                k *= 2;
                r = m;
            } else if (line.better(seg[k], xs[r - 1])) {
                k = k * 2 + 1;
                l = m;
            } else return;
        }
    }

    optional<pair<T, int>> query_with_id(T x) const {
        int n = (int)xs.size();
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        if (i == n || xs[i] != x) return nullopt;
        optional<pair<T, int>> result;
        int k = 1, l = 0, r = n;
        while (l < r) {
            if (seg[k].id == -1) break;
            auto value = make_pair(seg[k].get(x), seg[k].id);
            if (!result || value < *result) result = value;
            if (r - l == 1) break;
            int m = l + (r - l) / 2;
            if (i < m) {
                k *= 2;
                r = m;
            } else {
                k = k * 2 + 1;
                l = m;
            }
        }
        return result;
    }
};

/**
 * @brief ロールバック可能な Li Chao Tree
 */
