
const int INF = 1e8;
//define int long long if needed
struct MC {// 1 - indexed
    vector<vector<int>> G, dp;
    int n;
    MC(int sz) : n(sz), G(sz + 1, vector<int>(sz + 1, INF)) {} 
    void add(int u, int v, int w) {
        G[u][v] = G[v][u] = min(G[u][v], w);
    }
    int solve() {
        dp = G; 
        int ret = INF;
        for(int k = 1; k <= n; k++) {
            for(int i = 1; i < k; i++) {
                for(int j = i + 1; j < k; j++) {
                    ret = min(ret, G[k][i] + dp[i][j] + G[j][k]);
                }
            }
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
        return ret;
    }
};
