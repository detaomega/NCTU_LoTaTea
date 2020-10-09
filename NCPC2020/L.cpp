#include<bits/stdc++.h>
#define int long long
using namespace std;

typedef pair<int,int> pii;
const int maxn = 1e3 + 5;

int room[maxn][maxn];
int dp[maxn][maxn], n, m;

bool chk(int k) {
	dp[1][1] = room[1][1] + k;
	if (dp[1][1] <= 0) return false;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == 1 && j == 1) continue;
			dp[i][j] = 0;
			if (i - 1 >= 1 && dp[i - 1][j] > 0) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j] + room[i][j]);
			}
			if (j - 1 >= 1 && dp[i][j - 1] > 0) {
				dp[i][j] = max(dp[i][j], dp[i][j - 1] + room[i][j]);
			}
			if (room[i][j] == -1001) {
				dp[i][j] = -1;
			}
			if (!dp[i][j]) dp[i][j] = -1;
		}
	}
	return dp[n][m] > 0;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> room[i][j];
		}
	}
	int l = 0, r = 1e9 + 1, ans;
	while (l + 1 < r) {
		int m = (l + r) >> 1;
		if (chk(m)) {
			r = m;
			ans = m;
		}
		else {
			l = m;
			ans = m + 1;
		}
	}
	if (ans == 1000000001) cout << -1 << "\n";
	else cout << ans << "\n";
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		solve();		
	}
}
/*

2 
2 2
-10 -1001
-1001 -10
3 3
-200 -300 -1001
-500 -1000 100
1000 -1001 -500

*/
