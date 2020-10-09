#include <bits/stdc++.h>
#define maxn 100005
#define all(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())
#define F first
#define S second
#define EB emplace_back
#define PB push_back
using namespace std;

const int INF = 1 << 30;

struct Dinic {
	struct Edge {
		int to, flow;
		Edge(int a, int b) :
			to(a), flow(b) {}
	};
	vector<vector<int>> G;
	vector<int> dis, cur;
	vector<Edge> e;
	int s, t, n;
	Dinic(int sz) : n(sz), G(sz + 1), dis(sz + 1), cur(sz + 1) {}
	void add(int x, int y, int f) {
		G[x].PB(e.size());
		e.EB(y, f);
		G[y].PB(e.size());
		e.EB(x, 0);		
	}
	bool bfs() {
		fill(all(dis), -1);
		queue<int> que;
		que.push(s);
		dis[s] = 0;
		while(que.size()) {
			int x = que.front();
			que.pop();
			for(int id : G[x]) {
				int y = e[id].to;
				if(dis[y] == -1 && e[id].flow > 0) {
					dis[y] = dis[x] + 1;
					que.push(y);		
				}
			}
		}
		return dis[t] != -1; 
	}
	int dfs(int x, int f = INF) {
		if(x == t || f == 0) return f;
		int a, flow = 0;
		for(int &i = cur[x]; i < SZ(G[x]); i++) {
			int id = G[x][i];
			int y = e[id].to;
			if(dis[y] == dis[x] + 1 && e[id].flow > 0) {
				a = dfs(y, min(f, e[id].flow));
				e[id ^ 1].flow += a;
				e[id].flow -= a;
				flow += a;
				f -= a;
				if(f == 0) return flow;
			}			
		}
		return flow;
	}
	int solve(int _s, int _t) {
		s = _s; t = _t;
		int df, ret = 0;
		while(bfs()) {
			fill(begin(cur), end(cur), 0);
			while((df = dfs(s))) ret += df;
		}
		return ret;
	}
};

vector<int> G[maxn];
int color[maxn] = {};

void dfs(int x, int c) {
	color[x] = c;
	for(int y : G[x]) {
		if(!color[y]) {
			dfs(y, c == 1 ? 2 : 1);
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		u++, v++;
		G[u].PB(v);
		G[v].PB(u);
	}
	for(int i = 1; i <= n; i++) {
		if(!color[i]) dfs(i, 1);
	}
	Dinic loli(n + 1);
	for(int i = 1; i <= n; i++) {
		if(color[i] == 1) {
			loli.add(0, i, 1);
			for(int j : G[i]) {
				loli.add(i, j, 1);
			}
		}
		else {
			loli.add(i, n + 1, 1);
		}
	}
	assert(loli.solve(0, n + 1) == (n / 2));
	for(int i = 1; i <= n; i++) {
		if(color[i] == 1) {
			int m = -1;
			for(int id : loli.G[i]) {
				if(loli.e[id].flow == 0) {
					m = loli.e[id].to;
				}
			}
			cout << i - 1 << ' ' << m - 1 << '\n';
		}
	}
	return 0;
}
/*
10
20
9 0
9 2
9 8
9 3
1 2
1 8
3 1
4 1
8 6
6 3
6 4
0 6
5 3
5 4
5 0
5 2
7 4
0 7
2 7
8 7

*/
