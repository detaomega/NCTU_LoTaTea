const int INF = 1 << 30;
//Maximum Weight Perfect Bipartite Matching
//define int long long if needed
//allow negative weight!
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
    bool dfs(int x) {
        vx[x] = true;
        for(int y = 1; y <= n; y++) {
            if(vy[y]) continue;
            if(lx[x] + ly[y] > G[x][y]) {
                slack[y] = min(slack[y], lx[x] + ly[y] - G[x][y]);
            }
            else {
                vy[y] = true;
                if(match[y] == -1 || dfs(match[y])) {
                    match[y] = x;
                    return true; 
                }
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
            while(true) {
                vx.assign(vx.size(), false);
                vy.assign(vy.size(), false);
                if(dfs(i)) {
                    break;
                }
                int d = INF;
                for(int j = 1; j <= n; j++) {
                    if(!vy[j]) d = min(d, slack[j]);
                }
                for(int j = 1; j <= n; j++) {
                    if(vx[j]) lx[j] -= d;
                    if(vy[j]) ly[j] += d;
                    else slack[j] -= d;
                }
            }
        }
        int ret = 0;
        for(int i = 1; i <= n; i++) {
            ret += G[match[i]][i];
        }
        return ret;
    }
};
