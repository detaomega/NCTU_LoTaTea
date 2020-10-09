#include <bits/stdc++.h>
#define maxn 100005
#define F first
#define S second
using namespace std;

pair<double, int> arr[maxn];
int pre[maxn], suf[maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n && n) {
		for(int i = 1; i <= n; i++) {
				cin >> arr[i].F >> arr[i].S;		
		}	
		sort(arr + 1, arr + n + 1);
		pre[0] = 0;
		for(int i = 1; i <= n; i++) {
			if(arr[i].S == 0) pre[i] = 1;
			else pre[i] = 0;
			pre[i] += pre[i - 1];
		}
		suf[n + 1] = 0;
		for(int i = n; i > 0; i--) {
			if(arr[i].S == 1) suf[i] = 1;
			else suf[i] = 0;
			suf[i] += suf[i + 1];
		}
		int ans = 0;
		for(int i = 0; i <= n; i++) {
			ans = max(ans, pre[i] + suf[i + 1]);
			ans = max(ans, n - pre[i] - suf[i + 1]);
		} 
		cout << ans << '\n';
	}	

	return 0;
}
/*
4
80.5 1
90.5 0
100.5 0
110.5 0
10
125 1
100 1
70 0
120 1
95 1
60 0
220 1
85 0
75 1
90 0
0
*/
