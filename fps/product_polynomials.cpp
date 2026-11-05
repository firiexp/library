#ifndef FIRIEXP_LIBRARY_FPS_PRODUCT_POLYNOMIALS_CPP
#define FIRIEXP_LIBRARY_FPS_PRODUCT_POLYNOMIALS_CPP

#include "ntt.cpp"

poly product_polynomials(vector<poly> factors) {
    mint constant_product = 1;
    long long degree = 0;
    int shift = 0;
    vector<int> heap;
    heap.reserve(factors.size());
    for (int i = 0; i < (int)factors.size(); ++i) {
        auto& factor = factors[i];
        factor.shrink();
        if (factor.size() == 0) return poly();
        degree += factor.size() - 1;
        assert(degree < (1 << 23));
        int first = 0;
        while (factor[first] == mint(0)) ++first;
        shift += first;
        if (first) factor.v.erase(factor.v.begin(), factor.v.begin() + first);
        if (factor.size() == 1) {
            constant_product *= factor[0];
            vector<mint>().swap(factor.v);
        } else {
            heap.push_back(i);
        }
    }
    if (heap.empty()) {
        poly result(shift + 1);
        result[shift] = constant_product;
        return result;
    }
    auto compare = [&](int i, int j) { return factors[i].size() > factors[j].size(); };
    make_heap(heap.begin(), heap.end(), compare);
    auto pop = [&]() {
        pop_heap(heap.begin(), heap.end(), compare);
        int i = heap.back();
        heap.pop_back();
        return i;
    };
    while (heap.size() > 1) {
        int i = pop(), j = pop();
        factors[i] *= factors[j];
        vector<mint>().swap(factors[j].v);
        heap.push_back(i);
        push_heap(heap.begin(), heap.end(), compare);
    }
    auto& result = factors[heap[0]];
    for (auto& x : result.v) x *= constant_product;
    if (shift) result.v.insert(result.v.begin(), shift, mint(0));
    return move(result);
}

#endif

/**
 * @brief 多項式列の積
 */
