#include <bits/stdc++.h>
#define int long long
#define maxn  100005
using namespace std;
struct Pt {
  bool type;
  // true --> *
  // false --> +
  int val, idx;
  Pt(bool a, int b, int c) :
  type(a), val(b), idx(c) {}
};

const int mod = 1e9 + 7;

int power(int a, int n) {
  int ret = 1;
  while(n) {
    if(n & 1) {
      ret = ret * a % mod;
    }
    n >>= 1;
    a = a * a % mod;
  }
  return ret;
}

struct loli {
  struct ZKW {
    vector<int> arr; int n;
    ZKW(int sz) : arr(sz * 2, 1), n(sz) {}
    void upd(int x, int v) {
      for(arr[x] = v; x > 1; x >>= 1) {
        arr[x >> 1] = (arr[x] * arr[x ^ 1]) % mod;
      }
    }
    int ask(int l, int r) {// [l, r)
      int ret = 1;
      for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = ret * arr[l++] % mod;
        if(r & 1) ret = ret * arr[--r] % mod;
      }
      return ret;
    }
  };
  set<pair<int, int>> st;
  int Ans;
  ZKW tr;
  loli(int sz) : tr(sz + 5) {
    st.insert({0, 0});
    st.insert({sz + 1, 0});
    Ans = 0;
  }
  void add(int x, int v) {
    auto it = st.upper_bound({x, 0});
    auto l = prev(it), r = it;
    Ans = (Ans - (l -> second * (tr.ask(l -> first, r -> first)) % mod) + mod) % mod;
    Ans = (Ans + (l -> second * (tr.ask(l -> first, x)) % mod) + mod) % mod;
    Ans = (Ans + (v * (tr.ask(x, r -> first)) % mod) + mod) % mod;
    st.insert({x, v});
  }
  void mul(int x, int v) {
      auto it = st.upper_bound({x, 0});
      auto l = prev(it), r = it;
      Ans = (Ans - (l -> second * (tr.ask(l -> first, r -> first)) % mod) + mod) % mod;
      tr.upd(x, v);
      Ans = (Ans + (l -> second * (tr.ask(l -> first, r -> first)) % mod) + mod) % mod;
  }
  void kill(int x) {
    auto it = st.lower_bound({x, 0});
    auto l = prev(it), r = next(it);
    //printf("Get %lld %lld %lld\n", l -> first, it -> first, r -> first);
    Ans = (Ans + (l -> second * (tr.ask(l -> first, r -> first)) % mod) + mod) % mod;
    Ans = (Ans - (l -> second * (tr.ask(l -> first, it -> first)) % mod) + mod) % mod;
    Ans = (Ans - (it-> second * (tr.ask(it -> first, r -> first)) % mod) + mod) % mod;
    st.erase(it);
  }
};

vector<Pt> tr[maxn * 4];

void upd(int x, int L, int R, int l, int r, Pt v) {
  if(l <= L && R <= r) {
    tr[x].push_back(v);
    return;
  }
  int m = (L + R) >> 1;
  if(l <= m) upd(x << 1, L, m, l, r, v);
  if(r > m) upd((x << 1) | 1, m + 1, R, l, r, v);
  return;
}

int Sum = 0;

void dfs(int x, int l, int r, loli &cute) {
  for(auto it : tr[x]) {
    if(it.type) {
      cute.mul(it.idx, it.val);
    }
    else {
      cute.add(it.idx, it.val);
    }
  }
  if(l == r) {
    Sum = (Sum + cute.Ans) % mod;
  }
  else {
    int m = (l + r) >> 1;
    dfs(x << 1, l, m, cute);
    dfs((x << 1) | 1, m + 1, r, cute);
  }
  for(auto it : tr[x]) {
    if(it.type) {
      cute.mul(it.idx, 1);
    }
    else {
      cute.kill(it.idx);
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  loli cute(m);
  for(int i = 1; i <= m; i++) {
    int l, r, v; char op;
    cin >> l >> r >> op >> v;
    bool type = (op == '*' || op == '/');
    if(op == '/') v = power(v, mod - 2);
    if(op == '-') v = mod - v;
    upd(1, 1, n, l, r, Pt(type, v, i));
  }
  dfs(1, 1, n, cute);
  cout << Sum % mod << '\n';
  return 0;
}
