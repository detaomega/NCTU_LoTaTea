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
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      dist[i][j] = sqrt((arr[i].F - arr[j].F) * (arr[i].F - arr[j].F) +  (arr[i].S - arr[j].S) * (arr[i].S - arr[j].S));
      st.insert({i, j, dist[i][j]});
    }
  }
  for (int i = 1; i < n; i++) {
    auto now = *st.begin();
    cout << now.dist << " " << now.i << " " << now.j << "\n";
    if (!Mark[now.i]) {
      Mark[now.i] = 1;
      ans = ans + now.dist * now.dist / 4.0 * pi;
      for (int j = 1; j <= n; j++) {
        if (!Mark[j] && j != now.j) {
          auto it = st.find(Node{now.i, j, dist[now.i][j]});
          st.erase(it);
        }
      }
      for (int j = 1; j <= n; j++) {
        if (!Mark[j]) {
          st.insert({now.i, j, dis(arr[now.i], arr[j]) - now.dist});
        }
      }
    }
    if (!Mark[now.j]) {
      Mark[now.j] = 1;
      ans = ans + now.dist * now.dist / 4.0 * pi;
      for (int j = 1; j <= n; j++) {
        if (!Mark[j] && j != now.i) {
          auto it = st.find(Node{now.j, j, dist[now.j][j]});
          st.erase(it);
        }
      }
      for (int j = 1; j <= n; j++) {
        if (!Mark[j]) {
          st.insert({now.j, j, dis(arr[now.j], arr[j]) - now.dist});
        }
      }
    }
  }

  printf("%.10lf",  ans);
}
