struct hashes {
    int b;
    vector<int> mod;
    vector<vector<int>> pre;
    vector<vector<int>> base;
    hashes(int b, vector<int> mod) {
        this->mod = mod;
        this->b = b;
    };

    void build(string s) {
        pre.assign(s.size(), vector<int>(mod.size(), 0));
        base.assign(s.size(), vector<int>(mod.size(), 0));
        for (int i = 0; i < mod.size(); i++) {
            pre[0][i] = s[0];
            base[0][i] = 1;
        }
        for (int i = 1; i < s.size(); i++) {
            for (int j = 0; j < mod.size(); j++) {
                pre[i][j] = (pre[i - 1][j] * b + s[i]) % mod[j];
                base[i][j] = base[i - 1][j] * b % mod[j];
            }
        }
    }

    vector<int> query(int l, int r) {
        vector<int> ret(mod.size());
        for (int i = 0; i < mod.size(); i++) {
            ret[i] = (pre[r][i] - (l == 0 ? 0 : pre[l - 1][i] * base[r - l + 1][i] % mod[i]) + mod[i]) % mod[i];
        }
        return ret;
    }
};
