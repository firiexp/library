struct Node {
    int val;
    Node *nxt[2];
    Node() : val(0), nxt{nullptr, nullptr} {}
    static int cnt;
    void *operator new(size_t){
        static Node pool[3000000];
        return pool + cnt++;
    }
};
int Node::cnt = 0;

template<class T, size_t X>
struct Binarytrie {
    Node *root;
    Binarytrie() { root = new Node; }

    void add(const T b, T x = 1){
        Node *p = root;
        for (int i = X-1; i >= 0; --i) {
            bool f = (b >> i) & 1;
            if(!p->nxt[f]) p->nxt[f] = new Node;
            p = p->nxt[f];
        }
        p->val += x;
    }

    T xor_min(Node* t, const T &x, int dep = X-1){
        if(dep < 0) return 0;
        T f = (x >> dep) & 1U; f ^= !t->nxt[f];
        return xor_min(t->nxt[f], x, dep-1) | (f << dep);
    }
    T max_element(T x = 0) {
        return xor_min(root, ~x);
    }
    T min_element(T x = 0){
        return xor_min(root, x);
    }
};
