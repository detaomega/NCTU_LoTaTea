
struct Treap {
    struct Node {
        Node *l, *r;
        int key, pri, sz;
        Node(int x) : l(nullptr), r(nullptr),
            key(x), pri(rand()), sz(1) {}
    };
    Node *T;
    Treap() {
        T = nullptr;
    }
    int size(Node *x) {
        return x ? x -> sz : 0;
    }
    void pull(Node *x) {
        x -> sz = size(x -> l) + size(x -> r) + 1;
    }
    Node *merge(Node *a, Node *b) {
        if(!a) return b;
        if(!b) return a;
        if(a -> pri > b -> pri) {
            a -> r = merge(a -> r, b);
            pull(a); return a;
        }
        else {
            b -> l = merge(a, b -> l);
            pull(b); return b;
        }
    }
    void split(Node *s, int k, Node *&a, Node *&b) {// split by size
        if(!s) {
            a = b = nullptr;
            return;
        }
        if(size(s -> l) >= k) {
            split(s -> l, k, a, b);
            s -> l = b; 
            pull(s); b = s;
        }
        else {
            split(s -> r, k - size(s -> l) - 1, a, b);
            s -> r = a;
            pull(s); a = s;
        }
    }
    int Find(Node *x, int v) {
        if(!x) return 0;
        if(x -> key >= v) {
            return Find(x -> l, v);
        }       
        return size(x -> l) + 1 + Find(x -> r, v);
    }
    int Find(int x) {// number of elements smaller than x
        return Find(T, x);
    }
    int Kth(int x) {// the value of the kth element
        Node *a, *b, *c;
        split(T, x, b, c);
        split(b, x - 1, a, b);
        int ret = b -> key;
        T = merge(a, b);
        T = merge(T, c);
        return ret;
    }
    void insert(int x) {
        int cnt = Find(x);
        Node *a, *b, *c;
        split(T, cnt, a, c);
        b = new Node(x);
        T = merge(a, b);
        T = merge(T, c);
    }
    void erase(int x) {// erase one x
        int cnt = Find(x);
        Node *a, *b, *c;
        split(T, cnt, a, b);
        split(b, 1, b, c);
        delete b;
        T = merge(a, c);
    }
};
