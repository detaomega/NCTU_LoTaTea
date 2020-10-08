#include <bits/stdc++.h>
#define int long long
#define F first
#define S second
using namespace std;

const int maxn = 2005;
const double pi = acos(-1);
typedef pair<int,int> pii;

pair<int,int> arr[maxn];

struct Node {
  int i, j;
  double dist;
  bool operator < (const Node &a) const {
    return tie(dist, i, j) < tie(a.dist, a.i, a.j);
  }
};

set<Node> st;

double dist[maxn][maxn];
bool Mark[maxn];

double dis(pii a,pii b) {
  return sqrt((a.F - b.F) * (a.F - b.F) + (a.S - b.S) * (a.S - b.S));
}
int32_t main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i].first >> arr[i].second;
  }
  double ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      dist[i][j] = dis(arr[i], arr[j]) / 2.0;
      st.insert({i, j, dist[i][j]});
    }
  }
  for (int i = 1; i < n; i++) {
    Node now = *st.begin();
    // cout << now.dist << " " << now.i << " " << now.j << "\n";
    if (!Mark[now.i]) {
      Mark[now.i] = 1;
      ans = ans + now.dist * now.dist * pi;
    }
    if (!Mark[now.j]) {
        Mark[now.j] = 1;
        ans = ans + now.dist * now.dist * pi;
    }
    st.erase(st.begin());
    for (int j = 1; j <= n; j++) {
        if (j == now.i) continue;
        int u = min(j, now.i), v = max(j, now.i);
        auto it = st.find({u, v, dist[u][v]});
        if (it != st.end()) {
            st.erase(it);
        }
        if (!Mark[j]) {
            st.insert({u, v, dis(arr[u], arr[v]) - now.dist});
            dist[u][v] = dis(arr[u], arr[v]) - now.dist;
        }
    }
    for (int j = 1; j <= n; j++) {
        if (j == now.j) continue;
        int u = min(j, now.j), v = max(j, now.j);
        auto it = st.find({u, v, dist[u][v]});
        if (it != st.end()) {
            st.erase(it);
        }
        if (!Mark[j]) {
            st.insert({u, v, dis(arr[u], arr[v]) - now.dist});
            dist[u][v] = dis(arr[u], arr[v]) - now.dist;
        }
    }
  }
  printf("%.10f",  ans);
}
