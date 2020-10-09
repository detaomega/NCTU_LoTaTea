#include<bits/stdc++.h>
#define int long long
using namespace std;

typedef pair<int,int> pii;
const int maxn = 1e5 + 7;

void solve(int n) {
	pii Mx = {0, 0}, Mn = {(int)1e9, 0};
	for (int i = 0; i < (1<<n); i++) {
		int m = __builtin_popcount(i);
		int tmp = ((m % 10 + 1) * (((i + 1) % (m + 1) + 1)));
		if (Mx.first < tmp) Mx.first = tmp, Mx.second = i;
		if (Mn.first > tmp) Mn.first = tmp, Mn.second = i;
	}
	for (int i = n - 1 ; i >= 0; i--) {
		if ((1<<i) & Mx.second) cout << 1;
		else cout << 0;
	}
	cout << ": " << Mx.first << "\n";
	for (int i = n - 1 ; i >= 0; i--) {
		if ((1<<i) & Mn.second) cout << 1;
		else cout << 0;
	}
	cout << ": " << Mn.first << "\n";
}

int32_t main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	int n;
	while (cin >> n && n) {
		solve(n);
	}
	
	return 0;
}
