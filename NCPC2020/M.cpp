#include <bits/stdc++.h>
#define maxn 100005
#define int long long
#define all(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())
#define X first
#define Y second
#define EB emplace_back
#define PB push_back
using namespace std;
struct Pt {
    int x, y, id;
    Pt(int a = 0, int b = 0, int c = 0) :
        x(a), y(b), id(c) {}
    bool operator < (const Pt &a) const {
        return make_pair(x, y) < make_pair(a.x, a.y);
    }    
};


int cross(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x; 
} 

Pt Minus(Pt a, Pt b) {
	return Pt(a.x - b.x, a.y - b.y, 87);
}

int ans[maxn];
Pt arr[maxn];
int n, m;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin >> n >> m and n) {
        for(int i = 0; i < n; i++) {
            cin >> arr[i].x >> arr[i].y;
            arr[i].id = i;
        }
        vector<Pt> Q;
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y;
            if(x >= arr[n - 1].x) {
                ans[i] = n;
            }
            else {
            	Q.EB(x, y, i);
            }
        }
        sort(all(Q));
        vector<Pt> stk;
        //printf("Get %lld\n", SZ(Q));
        for(int j = n - 1, i = SZ(Q) - 1; i >= 0; i--) {
        	while(j >= 0 && arr[j].x >= Q[i].x) {
        		//add to convex
        		while(SZ(stk) > 1 && cross( Minus( *(stk.end()-1), *(stk.end()-2) ), Minus( arr[j], *(stk.end()-2) ) ) <= 0 ) stk.pop_back();
        		stk.push_back(arr[j]); j--;
        	}
        	//binary search
        	//printf("Convex (%lld) : ", SZ(stk));
        	//for(int k = 0; k < SZ(stk); k++) printf("(%lld, %lld) ", stk[k].x, stk[k].y);
        	int l = 0, r = SZ(stk) - 1;
        	while(r - l > 6) {
        		int d = (r - l) / 3;
        		int lm =  l + d, rm = l + 2 * d;
        		double data = atan2(stk[lm].x - Q[i].x, stk[lm].y - Q[i].y);
        		double icetea = atan2(stk[rm].x - Q[i].x, stk[rm].y - Q[i].y);
        		if(data < icetea) 
        			r = rm;
        		else
        			l = lm;
        	} 
        	int Ans = -1;
        	double tmp = 1e9;
        	for(int k = l; k <= r; k++) {
        		double data = atan2(stk[k].x - Q[i].x, stk[k].y - Q[i].y);
        		//printf("Get %f from %lld\n", data, stk[k].id);
        		if(data <= tmp) {
        			tmp = data;
        			Ans = stk[k].id;
        		}
        	}
        	//printf("This %lld\n", Ans);
        	ans[Q[i].id] = Ans;
        }
        for(int i = 0; i < m; i++) {
        	cout << ans[i] + 1 << '\n';
        }
    }
    return 0; 
}
/*
3 4
0 0
0 10
10 0
-1 0
-1 5
-1 11
-1 12
3 1
0 0
1 1
2 0
-2 1
0 0

*/
