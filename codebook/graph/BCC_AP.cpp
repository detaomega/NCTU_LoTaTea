
struct BCC { // 1 - indexed
    vector<vector<int>> G;
    vector<int> vis, low;
    vector<bool> ap;
    int n, t;
    BCC(int sz) : n(sz), t(0), G(sz + 1),  
        ap(sz + 1), vis(sz + 1), low(sz + 1) {}
    void add(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }  
    void dfs(int x, int p) {
        int cnt = 0;
        bool flag = false;
        vis[x] = low[x] = ++t;
        for(int y : G[x]) {
            if(y == p) continue;
            if(!vis[y]) {//tree edge
                cnt++; dfs(y, x);
                low[x] = min(low[x], low[y]);
                if(low[y] >= vis[x]) {
                    flag = true;
                }
            }
            else {// back edge
                low[x] = min(low[x], vis[y]);
            }
        }
        if((p == -1 && cnt > 1) || (p != -1 && flag)) {
            ap[x] = true;
        }
    }
    void solve() {
        //the graph is not necessarily connected
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) dfs(i, -1);
        }
        vector<int> ans;
        for(int i = 1; i <= n; i++) {
            if(ap[i]) {
                ans.push_back(i);
            }
        }
        //output ap
        cout << ans.size() << '\n';
        for(int i = 0; i < (int)ans.size(); i++) {
            cout << ans[i] << " \n"[i == (int)ans.size() - 1];
        }
    }
};
