#include <bits/stdc++.h>
using namespace std;
struct edge {
    int x;
    long long w;
    edge(int a, long long b) :
        x(a), w(b) {}
};

const int maxn = 1e5 + 5;
const int lg = 20;

long long dis[maxn][lg], M[maxn], D[maxn], sz[maxn];
int par[maxn], fa[maxn], que[maxn], dep[maxn];
vector<edge> G[maxn];
int n, m;

int get_cent(int x) {
    int tot = 0;
    que[tot++] = x; fa[x] = -1;
    for(int i = 0; i < tot; i++) {
        int cur = que[i];
        for(edge e : G[cur]) {
            if(!dep[e.x] && e.x != fa[cur]) {
                fa[e.x] = cur; que[tot++] = e.x;
            }
        }
    }
    int mi = 1e9, ret;
    for(int i = tot - 1; i >= 0; i--) {
        int cur = que[i];
        int mx = 0; sz[cur] = 1;
        for(edge e : G[cur]) {
            if(!dep[e.x] && e.x != fa[cur]) {
                sz[cur] += sz[e.x];
                mx = max(mx, (int)sz[e.x]);
            }
        }
        mx = max(mx, tot - (int)sz[cur]);
        if(mx < mi) mi = mx, ret = cur;
    }
    return ret;
}

void dfs(int x, int d, int p, long long w) {
    dis[x][d] = w;
    for(edge e : G[x]) {
        if(!dep[e.x] && e.x != p) {
            dfs(e.x, d, x, w + e.w);
        }
    }
}

void CD(int x, int p, int d) {
    x = get_cent(x);
    dfs(x, d, -1, 0);
    par[x] = p; dep[x] = d;
    for(edge e : G[x]) {
        if(!dep[e.x]) CD(e.x, x, d + 1);
    }
}

bool color[maxn] = {};

void upd(int x) {
    if(color[x]) return;
    color[x] = true;
    int p = x;
    while(p != -1) {
        sz[p]++;
        D[p] += dis[x][dep[p]];
        if(par[p] != -1) {
            M[p] += dis[x][dep[par[p]]];
        }
        p = par[p];
    }
}

long long query(int x) {
    int p = par[x], pre = x;
    long long ret = D[x];
    while(p != -1) {
        ret += D[p] - M[pre] + (sz[p] - sz[pre]) * dis[x][dep[p]];
        pre = p; p = par[p];
    }
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    CD(0, -1, 1);
    memset(sz, 0, sizeof(sz));
    int x, y;
    while(m--) {
        cin >> x >> y;
        if(x == 1)
            upd(y);
        else
            cout << query(y) << '\n';
    }
    return 0;
}
