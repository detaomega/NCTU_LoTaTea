
struct BCC {
    vector<vector<pair<int, int>>> G;
    vector<int> vis, low;
    set<int> ans;
    int n, t;
    BCC(int sz) : G(sz + 1), n(sz), t(0),
        vis(sz + 1), low(sz + 1) {} 
    void add(int u, int v, int id) {
        G[u].emplace_back(v, id);
        G[v].emplace_back(u, id);
    }
    void dfs(int x, int id) {
        vis[x] = low[x] = ++t;
        for(auto e : G[x]) {
            if(e.second == id) continue;
            int y = e.first;
            if(!vis[y]) {
                dfs(y, e.second);
                low[x] = min(low[x], low[y]);
                if(low[y] > vis[x]) { // bridge
                    ans.insert(e.second);
                }
            }
            else {
                low[x] = min(low[x], vis[y]);
            }
        }
    } 
    void solve() {
        // the graph is not necessarily connected
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) dfs(i, -1);
        }
        //the ans is in the set
    }
};


