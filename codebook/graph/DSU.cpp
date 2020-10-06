
struct DSU {
    vector<int> s, p;
    DSU(int sz) : s(sz + 1, 1), p(sz + 1, -1) {}
    int find(int x) {
        return p[x] == -1 ? x : (p[x] = find(p[x]));
    }
    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(s[x] < s[y]) swap(x, y);
        s[x] += s[y]; p[y] = x;
        return true;
    }
};
