#ifndef FIRIEXP_LIBRARY_FPS_PRODUCT_POLYNOMIALS_CPP
#define FIRIEXP_LIBRARY_FPS_PRODUCT_POLYNOMIALS_CPP

#include "ntt.cpp"

poly product_polynomials(vector<poly> factors) {
    mint constant_product = 1;
    long long degree = 0;
    vector<int> heap;
    heap.reserve(factors.size());
    for (int i = 0; i < (int)factors.size(); ++i) {
        auto& factor = factors[i];
        factor.shrink();
        if (factor.size() == 0) return poly();
        if (factor.size() == 1) {
            constant_product *= factor[0];
            vector<mint>().swap(factor.v);
        } else {
            degree += factor.size() - 1;
            assert(degree < (1 << 23));
            heap.push_back(i);
        }
    }
    if (heap.empty()) return poly(vector<mint>{constant_product});
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
    return move(result);
}

#endif

/**
 * @brief 多項式列の積
 */
