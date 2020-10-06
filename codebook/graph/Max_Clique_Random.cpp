
const int maxn = 80;
const int T = 4e4; // Test time

struct Max_Clique {
    bitset<maxn> G[maxn];
    int p[maxn], n;
    Max_Clique(int sz) {
        n = sz;
        for(int i = 0; i < n; i++) {
            G[i].reset(); // set to zero
            p[i] = i;
        }
    }
    void add(int u, int v) {
        G[u][v] = G[v][u] = true;
    }
    int solve() {
        int ans = 0;
        bitset<maxn> cur;
        for(int i = 0; i < T; i++) {
            random_shuffle(p, p + n);
            int cnt = 1; cur.reset();
            cur[p[0]] = true;
            for(int j = 1; j < n; j++) {
                if((cur & G[p[j]]) == cur) {
                    cnt++; cur[p[j]] = true;
                }
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};