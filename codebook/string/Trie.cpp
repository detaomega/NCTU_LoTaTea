
const int ALPHA = 26;// number of the characters

struct Trie {
    vector<vector<int>> T;
    vector<int> cnt;
    Trie() {
        cnt.emplace_back(0);
        T.emplace_back(ALPHA, 0);
    }
    int node() {
        int ret = T.size();
        cnt.emplace_back(0);
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
};

