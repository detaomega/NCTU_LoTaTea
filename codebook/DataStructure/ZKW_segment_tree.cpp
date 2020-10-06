
const int INF = 1 << 30;
// RMQ with ZKW segment tree 
struct ZKW {// 0 - indexed
    vector<int> arr; int n;
    ZKW(int sz) : arr(sz * 2, -INF), n(sz) {}
    void build(int inp[]) {
        for(int i = 0; i < n; i++) {
            arr[i + n] = inp[i]; 
        }
        for(int i = n - 1; i > 0; i--) {
            arr[i] = max(arr[i << 1], arr[(i << 1) | 1]);
        }
    }
    void upd(int x, int v) { 
        // set the value at position x
        // modify this part if needed
        for(arr[x += n] = v; x > 1; x >>= 1) {
            arr[x >> 1] = max(arr[x], arr[x ^ 1]); 
        }
    }
    int ask(int l, int r) {// [l, r)
        int ret = -INF;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret = max(ret, arr[l++]);
            if(r & 1) ret = max(ret, arr[--r]);
        }
        return ret;
    }
};
