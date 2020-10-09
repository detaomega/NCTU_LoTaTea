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

struct KM {
    vector<int> ly, lx, match, slack;
    vector<vector<int>> G;
    vector<bool> vx, vy;
    int n;
    KM(int sz) : n(sz), lx(sz + 1), ly(sz + 1), 
 	match(sz + 1), slack(sz + 1), vx(sz + 1), vy(sz + 1),
 	G(sz + 1, vector<int>(sz + 1, -INF)) {}
 	void add(int x, int y, int w) {
 		G[x][y] = w;
 	}       
 	bool dfs(int x) {
 		if(vx[x]) return false;
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
 		fill(all(ly), 0);
 		fill(all(match), -1);
 		for(int i = 1; i <= n; i++) {
 			lx[i] = -INF;
 			for(int j = 1; j <= n; j++) {
 				lx[i] = max(lx[i], G[i][j]);
 			}
 		}
 		for(int i = 1; i <= n; i++) {
 			fill(all(slack), INF);
 			while(true) {
 				vx.assign(vx.size(), false);
 				vy.assign(vy.size(), false);
 				if(dfs(i)) break;
 				int d = INF;
 				for(int j = 1; j <= n; j++) {
 					if(!vy[j]) {
 						d = min(d, slack[j]);
 					}
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


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n && n) {
		KM loli(n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int w; cin >> w;
				loli.add(i, j, -w);
			}
		}
		cout << -loli.solve() << "\n";
	}
	return 0;
}
