#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

#define int long long

typedef pair<int,int> pii;

int solve(pii a, pii b) {
  return max(a.S, b.S) - min(a.F, b.F) - max(0ll, max(a.F, b.F) - min(a.S, b.S));
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  int Q;
  cin >> Q;
  while (Q--) {
    int X;
    cin >> X;
    pii A, B;
    if (X <= x1) {
      A = {x1 - X, y1 - X}, B = {x2 - X, y2 - X};
    }
    else if (x1 < X && X <= y1) {
      int mx = max(X - x1, y1 - X);
      A = {0ll, mx}, B = {x2 - X, y2 - X};

    }
    else if (X <= x2) {
      A = {X - y1, X - x1}, B = {x2 - X, y2 - X};
    }
    else if (x2 <= X && X <= y2) {
      int mx = max(X - x2, y2 - X);
      A = {X - y1, X - x1}, B = {0ll, mx};
    }
    else {
      A = {X - y1, X - x1}, B = {X - y2, X - x2};
    }
    // cout << A.F << " " << A.S << " -- " << B.F << " " << B.S << "\n";
    cout << solve(A, B) << "\n";
  }
}
