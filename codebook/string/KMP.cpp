
const int maxn = 1e4 + 5;

char s[maxn], t[maxn];
int fail[maxn];
int n, m;

int kmp(char *s, char *t) {
    n = strlen(s);
    m = strlen(t);
    if(m > n) return 0;
    fail[0] = -1; // build fail
    for(int i = 1; i < m; i++) {
        int j = fail[i - 1];
        while(j >= 0 && t[j + 1] != t[i]) j = fail[j];
        if(t[i] == t[j + 1]) j++;
        fail[i] = j;
    }
    int ret = 0; // kmp
    for(int i = 0, j = -1; i < n; i++) {
        while(j >= 0 && s[i] != t[j + 1]) {
            j = fail[j];
        }
        if(s[i] == t[j + 1]) j++;
        if(j == m - 1) {
            ret++; j = fail[j];
        }
    }
    return ret;
}
