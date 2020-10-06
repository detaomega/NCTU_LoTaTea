

//Remember to define int long long
const int INF = 1e9;

struct Li_Chao {
    struct Line {
        // y = mx + k
        int m, k;
        Line(int a = -INF, int b = -INF) :
            m(a), k(b) {}
        int val(int x) {
            return m * x + k;
        }
    };
    vector<Line> arr;   
    vector<int> pos;
    int n;
    Li_Chao(vector<int> &p) {
        pos = p;
        n = pos.size();
        arr.resize(n * 4);
    } 
    void upd(int x, int l, int r, Line v) {
        if(l == r) {
            if(arr[x].val(pos[l]) < v.val(pos[l])) {
                arr[x] = v;
            }
            return;
        }
        int m = (l + r) >> 1;
        if(arr[x].m < v.m) swap(arr[x], v);
        if(arr[x].val(pos[m]) > v.val(pos[m])) {
            upd(x << 1, l, m, v);
        }
        else {
            swap(arr[x], v);
            upd((x << 1) | 1, m + 1, r, v);
        }
    }
    int ask(int x, int l, int r, int p) {
        if(l == r) {
            return arr[x].val(pos[p]);
        }
        int m = (l + r) >> 1;
        int ret = arr[x].val(pos[p]);
        if(p <= m) {
            ret = max(ret, ask(x << 1, l, m, p));
        }
        else {
            ret = max(ret, ask((x << 1) | 1, m + 1, r, p));
        }
        return ret;
    }
};
