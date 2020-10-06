
struct Graph {//1 - indexed
    vector<int> par, match, st, s, vis;
    vector<vector<int>> G;
    int n, t;
    Graph(int sz) : n(sz), G(sz + 1), match(sz + 1),
        par(sz + 1), vis(sz + 1), st(sz + 1), s(sz + 1) {} 
    void add(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int lca(int x, int y) {
        for( t++; ; swap(x, y)) {
            if(x == 0) continue;
            if(vis[x] == t) return x;
            vis[x] = t;
            x = st[par[match[x]]];
        }
    }
    void flower(int x, int y,  int l, queue<int> &que) {
        while(st[x] != l) {
            par[x] = y;
            if(s[y = match[x]] == 1) {
                s[y] = 0;
                que.push(y);
            }
            st[x] = st[y] = l;
            x = par[y];
        }
    }
    bool bfs(int x) {
        for(int i = 1; i <= n; i++) {
            st[i] = i;
        }
        fill(begin(s), end(s), -1);
        queue<int> que;
        que.push(x);
        s[x] = 0;
        while(que.size()) {
            x = que.front();
            que.pop();
            for(int y : G[x]) {
                if(s[y] == -1) {
                    par[y] = x;
                    s[y] = 1;
                    if(!match[y]) {
                        for(int lst; x; y = lst, x = par[y]) {
                            lst = match[x];
                            match[x] = y;
                            match[y] = x;
                        }
                        return true;
                    }
                    que.push(match[y]);
                    s[match[y]] = 0;
                } else if(!s[y] && st[y] != st[x]) {
                    int l = lca(st[x], st[y]);
                    flower(x, y, l, que);
                    flower(y, x, l, que);
                }
            }
        }
        return false;
    }
    int solve() {
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(!match[i] && bfs(i)) ans++;
        }
        return ans;
    }
};