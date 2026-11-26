template<class TopK>
void check_top_k_value_semantics() {
    TopK original(2);
    for (int x : {7, 4, 7, -2, 3}) original.insert(x);
    bool erased = original.erase_one(3);
    assert(erased);

    TopK copied = original;
    TopK assigned(5);
    assigned.insert(1);
    assigned = original;
    copied.insert(6);
    assigned.set_k(1);
    erased = assigned.erase_one(7);
    assert(erased);
    verify_one({7, 4, 7, -2}, original);
    verify_one({7, 4, 7, -2, 6}, copied);
    verify_one({7, 4, -2}, assigned);

    vector<TopK> groups;
    groups.emplace_back(1);
    groups.front() = std::move(original);
    assert(original.k() == 0);
    verify_one({}, original);
    original.set_k(1);
    original.insert(5);
    verify_one({5}, original);

    groups.resize(groups.capacity());
    groups.emplace_back(std::move(copied));
    assert(copied.k() == 0);
    verify_one({}, copied);
    assert(groups.front().k() == 2 && groups.back().k() == 2);
    verify_one({7, 4, 7, -2}, groups.front());
    verify_one({7, 4, 7, -2, 6}, groups.back());

    groups.front() = std::move(assigned);
    assert(assigned.k() == 0);
    verify_one({}, assigned);
    assigned.insert(-1);
    verify_one({-1}, assigned);
    std::swap(groups.front(), groups.back());
    assert(groups.front().k() == 2 && groups.back().k() == 1);
    verify_one({7, 4, 7, -2, 6}, groups.front());
    groups.back().insert(8);
    verify_one({7, 4, -2, 8}, groups.back());

    auto last = groups.size() - 1;
    groups.resize(groups.capacity() + 1);
    verify_one({7, 4, 7, -2, 6}, groups.front());
    verify_one({7, 4, -2, 8}, groups[last]);
    assert(groups.back().k() == 0);
    verify_one({}, groups.back());
}
