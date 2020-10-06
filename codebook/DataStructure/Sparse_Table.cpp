
struct ST {// 1 - indexed
    vector<vector<int>> T;
    int n;
    ST(int sz) : n(sz), T(__lg(sz) + 1, vector<int>(sz + 1)) {}
    void build(int arr[]) {
        for(int i = 1; i <= n; i++) {
            T[0][i] = arr[i];
        }
        for(int i = 1; i < (int)T.size(); i++) {
            for(int j = 1; j + (1 << i) - 1 <= n; j++) {
                T[i][j] = max(T[i - 1][j], T[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int ask(int l, int r) {
        int k = __lg(r - l + 1);
        return max(T[k][l], T[k][r - (1 << k) + 1]);
    }
};
