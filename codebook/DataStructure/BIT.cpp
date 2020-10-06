// define int long long if needed
struct BIT {// 1 - indexed
  vector<int> bit; 
  int n;
  BIT(int sz) : bit(sz + 1), n(sz) {}
  void add(int x, int v) {
    for(int i = x; i <= n; i += i & (-i)) {
      bit[i] += v;
    }
  }
  int ask(int x) {
    int ret = 0;
    for(int i = x; i > 0; i -= i & (-i)) {
      ret += bit[i];
    }
    return ret;
  }
  int ask(int l, int r) {// [l, r]
    if(l > r) return 0;
    return ask(r) - ask(l - 1);
  }
  int kth(int k) {
    int ret = 0;
    for(int i = 1 << __lg(n); i > 0; i >>= 1) {
      if(ret + i <= n && bit[ret + i] < k)
        ret -= bit[ret += i];
    }
    return ret + 1;
  }
};
