
struct LCA {
    vector<int> top, heavy, dep, sz, par;
    vector<vector<int>> G;
    int n;
    LCA(int _sz) : n(_sz), G(_sz + 1), top(_sz + 1), dep(_sz + 1), 
        sz(_sz + 1), par(_sz + 1),  heavy(_sz + 1) {} 
    void add(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void dfs(int x, int p) {
        dep[x] = (p == -1) ? 1 : dep[p] + 1;
        sz[x] = 1; heavy[x] = -1; par[x] = p;
        for(int y : G[x]) {
            if(y == p) continue;
            dfs(y, x);
            sz[x] += sz[y];
            if(heavy[x] == -1 || sz[y] > sz[heavy[x]]) {
                heavy[x] = y;
            }
        }
    }
    void build(int root = 1) {
        dfs(root, -1);
        for(int i = 1; i <= n; i++) {
            if(heavy[i] == -1 || heavy[par[i]] != i) {
                for(int p = i; p != -1; p = heavy[p]) {
                    top[p] = i;
                }
            }
        }
    }
    int lca(int x, int y) {
        while(top[x] != top[y]) {
            if(dep[top[x]] > dep[top[y]])
                x = par[top[x]];
            else
                y = par[top[y]];
        }
        return dep[x] < dep[y] ? x : y;
    }
};
