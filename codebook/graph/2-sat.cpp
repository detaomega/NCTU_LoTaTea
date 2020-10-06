
// i --> false
// i + n --> true;
struct SAT {// 1 - indexed
    vector<vector<int>> G, RG;
    vector<int> stk, scc;
    vector<bool> vis;
    int n;
    SAT(int sz) : G(sz * 2 + 1), RG(sz * 2 + 1),
        n(sz), scc(sz * 2 + 1), vis(sz * 2 + 1) {}
    void dfs(int x) {
        vis[x] = true;
        for(int y : G[x]) {
            if(!vis[y]) dfs(y);
        }
        stk.push_back(x);
    }
    void DFS(int x, int id) {
        scc[x] = id;
        for(int y : RG[x]) {
            if(!scc[y]) DFS(y, id);
        }
    }
    void add(int u, int v) {
        G[u].push_back(v);
        RG[v].push_back(u);
    } 
    vector<int> solve() {
        for(int i = 1; i <= 2 * n; i++) {
            if(!vis[i]) dfs(i);
        }
        reverse(begin(stk), end(stk));
        int cnt = 0;
        for(int x : stk) {
            if(!scc[x]) {
                cnt++; DFS(x, cnt);
            }
        }
        for(int i = 1; i <= n; i++) {
            if(scc[i] == scc[i + n]) { // IMPOSSIBLE
                return vector<int>();
            }
        }
        vector<vector<int>> T(cnt + 1);
        for(int i = 1; i <= 2 * n; i++) {
            T[scc[i]].push_back(i);
        }
        vector<int> ans(n + 1, -1);
        for(int i = cnt; i > 0; i--) {
            for(int x : T[i]) {
                int id = (x > n) ? x - n : x;
                if(ans[id] == -1) {
                    if(x > n) 
                        ans[id] = 1;
                    else
                        ans[id] = 0;
                }
            }
        }
        return ans;
    }
};
