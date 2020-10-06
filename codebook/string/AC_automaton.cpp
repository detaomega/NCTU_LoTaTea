
const int ALPHA = 26;// number of characters
//Remember to build before solve
struct AC {
    vector<vector<int>> T;
    vector<int> fail, cnt;
    AC() {
        T.emplace_back(ALPHA, 0);
        fail.emplace_back(0);
        cnt.push_back(0);
    }
    int node() {
        cnt.push_back(0);
        int ret = T.size();
        T.emplace_back(ALPHA, 0);
        return ret;
    }
    void insert(string &s) {
        int p = 0;
        for(char c : s) {
            int nxt = c - 'a';
            if(!T[p][nxt]) {
                T[p][nxt] = node();
            }
            p = T[p][nxt];
        }
        cnt[p]++;
    }
    void build() {
        queue<int> que;
        fail.resize(T.size());
        for(int i = 0; i < ALPHA; i++) {
            if(T[0][i]) {
                fail[T[0][i]] = 0;
                que.push(T[0][i]);
            }
        }
        while(que.size()) {
            int x = que.front();
            que.pop();
            for(int i = 0; i < ALPHA; i++) {
                if(T[x][i]) {
                    que.push(T[x][i]);
                    fail[T[x][i]] = T[fail[x]][i];
                }
                else {
                    T[x][i] = T[fail[x]][i];
                }
            }
        }
    }
    int solve(string &s) {
        int p = 0, ret = 0;
        for(char c : s) {
            p = T[p][c - 'a'];
            for(int cur = p; cur > 0; cur = fail[cur]) {
                ret += cnt[cur];
            }
        }
        return ret;
    }
};

