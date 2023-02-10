using pii = pair<int,int>;

// 0-indexed
// O(n logn)
vector<int> suffix_array(string &s) {
    int n = s.size();
    vector<int> p(n);
    vector<int> c(n);
    vector<list<int>> keep(max(128, n));
    for (int i = 0; i < n; i++) {
        keep[s[i]].push_back(i);
    }
    int rk = 0;
    for (int i = 0, j = 0; i < 128; i++) {
        if (keep[i].empty())
            continue;
        while (keep[i].size()) {
            int x = keep[i].front();
            keep[i].pop_front();
            c[x] = rk;
            p[j++] = x;
        }
        rk++;
    }

    vector<int> np(n);
    vector<int> nc(n);

    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i++) {
            np[i] = (p[i] - k + n) % n;
        }
        for (auto &x : np) {
            keep[c[x]].push_back(x);
        }
        for (int i = 0, j = 0; i < rk; i++) {
            while (keep[i].size()) {
                int x = keep[i].front();
                keep[i].pop_front();
                p[j++] = x;
            }
        }

        rk = 1;
        for (int i = 1; i < n; i++) {
            int cur = p[i];
            int pre = p[i - 1];
            if (pii(c[cur], c[(cur + k) % n]) != pii(c[pre], c[(pre + k) % n]))
                rk++;
            nc[cur] = rk - 1;
        }
        c.swap(nc);
    }
    return p;
}