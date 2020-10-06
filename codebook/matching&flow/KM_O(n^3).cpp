const int INF = 1 << 30;
//Maximum Weight Perfect Bipartite Matching
// define int long long if  needed
//allow negative weight! 
// O(n^3)
struct KM {// 1 - indexed
    vector<int> lx, ly, match, slack;
    vector<vector<int>> G;
    vector<bool> vx, vy;
    int n;
    KM(int sz) : n(sz), lx(sz + 1), ly(sz + 1), 
    match(sz + 1), slack(sz + 1), vx(sz + 1), vy(sz + 1),  
    G(sz + 1, vector<int>(sz + 1, -INF)) {}
    void clear() {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                G[i][j] = -INF;
            }
        }
    }
    void add(int x, int y, int w) {
        G[x][y] = w;
    }
    bool dfs(int x, bool adj = true) {
        if(vx[x]) return false;
        vx[x] = true;
        for(int y = 1; y <= n; y++) {
            if(vy[y]) continue;
            int t = lx[x] + ly[y] - G[x][y];
            if(t == 0) {
                vy[y] = true;
                if(match[y] == -1 || dfs(match[y], adj)) {
                    if(adj) match[y] = x;
                    return true;
                }
            }
            else {
                slack[y] = min(slack[y], t);
            }
        }
        return false;
    }
    int solve() {
        fill(begin(ly), end(ly), 0);
        fill(begin(match), end(match), -1);
        for(int i = 1; i <= n; i++) {
            lx[i] = -INF;
            for(int j = 1; j <= n; j++) {
                lx[i] = max(lx[i], G[i][j]);
            }
        }
        for(int i = 1; i <= n; i++) {
            fill(begin(slack), end(slack), INF);
            vx.assign(vx.size(), false);
            vy.assign(vy.size(), false);
            if(dfs(i)) continue; 
            bool flag = true;
            while(flag) {
                int cut = INF;
                for(int j = 1; j <= n; j++) {
                    if(!vy[j]) cut = min(cut, slack[j]);
                }    
                for(int j = 1; j <= n; j++) {
                    if(vx[j]) lx[j] -= cut;
                    if(vy[j]) ly[j] += cut;
                    else slack[j] -= cut;
                }
                for(int j = 1; j <= n; j++) {
                    if(!vy[j] && slack[j] == 0) {
                        vy[j] = true;
                        if(match[j] == -1 || dfs(match[j], false)) {
                            flag = 0;// find path
                            break;
                        }
                    }
                }
            }
            vx.assign(vx.size(), false);
            vy.assign(vy.size(), false);
            dfs(i);// add path
        }
        int ret = 0;
        for(int i = 1; i <= n; i++) {
            if(G[match[i]][i] != -INF) 
                ret += G[match[i]][i];
        }
        return ret;
    }
};
