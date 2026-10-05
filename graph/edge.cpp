#ifndef FIRIEXP_LIBRARY_GRAPH_EDGE_CPP
#define FIRIEXP_LIBRARY_GRAPH_EDGE_CPP

template <typename T>
struct edge {
    int from, to;
    T cost;

    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}

    explicit operator int() const { return to; }
};

#endif
