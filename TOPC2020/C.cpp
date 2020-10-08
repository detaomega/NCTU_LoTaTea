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
    return tie(dist, i, j) > tie(a.dist, a.i, a.j);
  }
};

priority_queue<Node> st;

double dist[maxn][maxn], ans[maxn];
bool Mark[maxn];

double dis(pii a,pii b) {
  return sqrt((a.F - b.F) * (a.F - b.F) + (a.S - b.S) * (a.S - b.S));
}

int32_t main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i].first >> arr[i].second;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      dist[i][j] = dis(arr[i], arr[j]) / 2.0;
      if (i != j)
      st.push({min(i, j), max(i, j), dist[i][j]});
    }
  }
  int cnt = 0;
  while (cnt < n) {
    Node now = st.top();
    st.pop();

    // cout << now.dist << "" << now.i << " " << now.j << "\n";
    if (Mark[now.i] + Mark[now.j] == 0) {
      Mark[now.i] = 1;
      Mark[now.j] = 1;
      ans[now.i] = now.dist;
      ans[now.j] = now.dist;
      cnt += 2;
      for (int j = 1; j <= n; j++) {
        if (j == now.i) continue;
        int u = min(j, now.i), v = max(j, now.i);
        if (!Mark[j]) {
            dist[u][v] = dis(arr[u], arr[v]) - now.dist;
            st.push({u, v, dist[u][v]});
        }
      }
      for (int j = 1; j <= n; j++) {
         if (j == now.j) continue;
            int u = min(j, now.j), v = max(j, now.j);
            if (!Mark[j]) {
                dist[u][v] = dis(arr[u], arr[v]) - now.dist;
                st.push({u, v, dist[u][v]});
            }
        }
    }
    if (Mark[now.j] + Mark[now.i] == 1) {

        if (!Mark[now.j]) swap(now.i, now.j);

        if (abs(now.dist - (dis(arr[now.i], arr[now.j]) - ans[now.j])) < 1e-9) {
            ans[now.i] = now.dist;
            for (int j = 1; j <= n; j++) {
            if (j == now.i) continue;
            int u = min(j, now.i), v = max(j, now.i);
                if (!Mark[j]) {
                    dist[u][v] = dis(arr[u], arr[v]) - now.dist;
                    st.push({u, v, dist[u][v]});
                }
            }
            cnt++;
            Mark[now.i] = 1;
        }
    }
  }
  double lst = 0;
  for (int i = 1; i <= n; i++) {
    lst = lst + ans[i] * ans[i] * pi;
  }
  printf("%.8f\n",  lst);
}
