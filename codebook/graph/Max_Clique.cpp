
//if this didn't pass, try random
struct Max_Clique {// 0 - indexed
    vector<vector<bool>> G;
    vector<int> cnt, vis;
    int n, ans;
    Max_Clique(int sz) : n(sz), cnt(sz), vis(sz),
        G(sz, vector<bool>(sz, false)) {}
    void add(int u, int v) {
        G[u][v] = G[v][u] = true;
    }
    bool dfs(int x, int dep) {
        for(int i = x + 1; i < n; i++) {
            if(cnt[i] + dep <= ans) return false;
            if(G[x][i]) {
                int j;
                for(j = 0; j < dep; j++) {
                    if(!G[i][vis[j]]) break;
                }
                if(j == dep) {
                    vis[dep] = i;
                    if(dfs(i, dep + 1)) return true;                 
                }
            }
        }
        if(dep > ans) {
            ans = dep;
            return true;
        }
        return false;
    }
    int solve() {
        ans = -1e9;
        for(int i = n - 1; i >= 0; i--) {
            vis[0] = i;
            dfs(i, 1);
            cnt[i] = ans;
        }
        return ans;
    }
};
