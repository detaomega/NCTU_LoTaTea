#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1e5 + 7;

int a[maxn] = {};

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--) {
	    int N;
	    cin >> N;
	    int sum = 0;
	    int x=0,y=0,z=0;
	    int zero = 0;
	    for (int i=1; i<=N; i++) {
	    	cin >> a[i];
	    	if (a[i] == 3)
	    		x++;
	    	else if (a[i] == 6)
	    		y++;
	    	else if (a[i] == 9)
	    		z++;
	    	else if (a[i] == 0)
	    		zero++;
	    	sum += a[i];
	    }
	    
	    if (sum % 9 == 3) {
	    	if (x >= 1) {
	    		x--;
	    	} else if (y >= 2) {
	    		y-=2;
	    	} else {
	    		printf("-1\n");
	    		continue;
	    	}	
	    	
	    } else if (sum % 9 == 6) {
			
			if (y >= 1) {
				y--;
			} else if (x >= 2) {
				x-=2;
			} else {
				printf("-1\n");
				continue;
			}
	    }
	    
	    
	    
	    vector<int> ans;
	    for (int i=1; i<=z; i++) {
	    	ans.push_back(9);
	    }
	    for (int i=1; i<=y; i++) {
	    	ans.push_back(6);
	    }
	    for (int i=1; i<=x; i++) {
	    	ans.push_back(3);
	    }
	    for (int i=1; i<=zero; i++) {
	    	ans.push_back(0);
	    }
	    
	    if (ans.empty()) {
	    	printf("-1\n");
	    	continue;
	    }
	    
	    for (int i=0; i<ans.size(); i++) {
	    	printf("%lld%c", ans[i], i == ans.size()-1 ? '\n' : ' ');
	    }
	}
	
	return 0;
}
