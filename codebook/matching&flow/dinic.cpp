
const int INF = 1 << 30;
//define int long long if needed
struct Dinic {
    struct edge {
        int to, cap, flow;
        edge(int a, int b) :
            to(a), cap(b), flow(0) {}
    };
    vector<vector<int>> G;
    vector<int> dis, cur;
    vector<edge> e;
    int n, s, t;
    Dinic(int sz) : n(sz), G(sz + 1),
        dis(sz + 1), cur(sz + 1) {}
    void add(int u, int v, int f) {
        G[u].emplace_back(e.size());
        e.emplace_back(v, f);
        G[v].emplace_back(e.size());
        e.emplace_back(u, 0);
    }
    int dfs(int x, int f) {
        if(x == t || f == 0) return f;
        for(int &i = cur[x]; i < (int)G[x].size(); i++) {
            int id = G[x][i];
            if(dis[e[id].to] == dis[x] + 1 && e[id].flow != e[id].cap) {
                int df = dfs(e[id].to, min(f, e[id].cap - e[id].flow));
                if(df) {
                    e[id].flow += df;
                    e[id ^ 1].flow -= df;
                    return df;
                }
            }
        }
        dis[x] = -1;
        return 0;
    }
    bool bfs() {
        dis.assign(dis.size(), -1);
        queue<int> que; dis[s] = 0;
        que.push(s);
        while(que.size()) {
            int x = que.front();
            que.pop();
            for(int id : G[x]) {
                if(e[id].cap != e[id].flow && dis[e[id].to] == -1) {
                    que.push(e[id].to); 
                    dis[e[id].to] = dis[x] + 1;
                }
            }
        }
        return dis[t] != -1;
    }
    int solve(int _s, int _t) {
        s = _s;  t = _t;
        int df, flow = 0;
        while(bfs()) {
            cur.assign(cur.size(), 0);
            while((df = dfs(s, INF))) flow += df;
        }
        return flow;
    }
};
