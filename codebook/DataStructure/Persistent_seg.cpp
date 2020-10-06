
struct Seg {
    struct Node {
        int val;
        Node *l, *r;
        Node(int x) : val(x),
            l(nullptr), r(nullptr) {}
    };
    vector<Node*> ver;
    int l, r;
    Node *build(int l, int r) { 
        Node *ret = new Node(0);
        if(l == r) return ret;
        int mid = (l + r) >> 1;
        ret -> l = build(l, mid);
        ret -> r = build(mid + 1, r);
        return ret;
    }
    void init(int _l, int _r) {
        ver.clear(); l = _l, r = _r;
        ver.push_back(build(l, r));
    }
    Node *upd(Node *x, int l, int r, int pos, int val) {
        Node *ret = new Node(x -> val + val);
        ret -> l = x -> l; ret -> r = x -> r;
        if(l == r) {
            return ret;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) ret -> l = upd(x -> l, l, mid, pos, val);
        else ret -> r = upd(x -> r, mid + 1, r, pos, val);
        return ret;
    }
    void upd(int pos, int val) {
        auto ptr = upd(ver.back(), l, r, pos, val);
        ver.push_back(ptr);
    }
    int Get(Node *a, Node *b, int l, int r, int k) {
        if(l == r) return l;
        int mid = (l + r) >> 1;
        int cnt = b -> l -> val - a -> l -> val;
        if(cnt >= k) {
            return Get(a -> l, b -> l, l, mid, k);
        }
        else {
            return Get(a -> r, b -> r, mid + 1, r, k - cnt);
        }
    }
    int ask(int vl, int vr, int k) {
        return Get(ver[vl - 1], ver[vr], l, r, k);
    }
};


