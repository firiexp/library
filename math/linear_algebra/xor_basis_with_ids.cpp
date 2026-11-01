template<class T>
struct XorBasisWithIds {
    static_assert(is_integral_v<T> && !is_same_v<T, bool>, "XorBasisWithIds requires integral T other than bool");
    using U = make_unsigned_t<T>;
    static constexpr int B = numeric_limits<U>::digits;
    static_assert(B <= 64, "XorBasisWithIds supports up to 64 bits");

    XorBasisWithIds() : basis(B, 0), masks(B, 0) {}

    int size() const { return ids.size(); }
    bool empty() const { return ids.empty(); }

    bool add(T value, int id) {
        U x = static_cast<U>(value), mask = 0;
        for (int i = B - 1; i >= 0; --i) {
            if (((x >> i) & 1) == 0) continue;
            if (basis[i] != 0) {
                x ^= basis[i];
                mask ^= masks[i];
            } else {
                basis[i] = x;
                masks[i] = mask ^ (U(1) << ids.size());
                ids.push_back(id);
                return true;
            }
        }
        return false;
    }

    optional<vector<int>> representation(T value) const {
        U x = static_cast<U>(value), mask = 0;
        for (int i = B - 1; i >= 0; --i) {
            if (((x >> i) & 1) == 0) continue;
            if (basis[i] == 0) return nullopt;
            x ^= basis[i];
            mask ^= masks[i];
        }
        vector<int> result;
        for (int i = 0; i < (int)ids.size(); ++i) if ((mask >> i) & 1) result.push_back(ids[i]);
        return result;
    }

private:
    vector<U> basis, masks;
    vector<int> ids;
};

/**
 * @brief 入力IDの復元付きXOR基底
 */
