
//0 - indexed
// O(n logn logn)
vector<int> SA(string &s) {
    int n = s.size();
    vector<int> sa(n), rk(n), tmp(n);
    for(int i = 0; i < n; i++) {
        rk[i] = s[i];
        sa[i] = i;
    }
    for(int k = 1; k < n; k <<= 1) {
        auto val = [&](int x) {
            return make_pair(rk[x], (x + k < n) ? rk[x + k] : -1);
        };
        sort(begin(sa), end(sa), [&](int a, int b){
            return val(a) < val(b);
        }); 
        tmp[sa[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(val(sa[i]) == val(sa[i - 1])) {
                tmp[sa[i]] = tmp[sa[i - 1]]; 
            }
            else {
                tmp[sa[i]] = tmp[sa[i - 1]] + 1;
            }
        }
        rk.swap(tmp);
    }
    // cal rank
    for(int i = 0; i < n; i++) {
        rk[sa[i]] = i;
    }
    // cal height
    int k = 0;
    vector<int> height(n);
    for(int i = 0; i < n; i++) {
        if(rk[i]) {
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) k++;
        }
        height[rk[i]] = k;
        k = max(0, k - 1); // height[rk[i + 1]] >= height[rk[i]] - 1
    }
    return sa;
}
