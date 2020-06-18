#include "./bipartite_matching.cpp"
class Bipartite_Matching_LexMin : public Bipartite_Matching {
public:
    using Bipartite_Matching::Bipartite_Matching;

    int solve_LexMin() { // check sorted edge no
        int res = matching();
        for (int i = 0; i < l; ++i) {
            if(!~match[i]) continue;
            match[match[i]] = -1;
            match[i] = -1;
            ++t;
            dfs(i);
            alive[match[i]] = 0;
            alive[i] = 0;
        }
        return res;
    }
};