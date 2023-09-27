// 1-based
int fail[M];
void KMP(const char *s, int n) {
    fail[0] = fail[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        fail[i] = 0;
        while (j && s[i] != s[j + 1]) j = fail[j];
        if (s[i] == s[j + 1]) fail[i] = ++j;
    }
}
// match
for (int i = 1, j = 0; i <= la; ++i) {
    while (j && b[j + 1] != a[i]) j = fail[j];
    if (b[j + 1] == a[i]) ++j;
    if (j == lb) {
        printf("%d\n", i - lb + 1);
        j = fail[j];
    }
}
// 0-based
// s 和 s 的每一个后缀的最长公共前缀 (LCP) 长度数组
void exKMP(const char *s, int *z, int n) {// get z
    int l = 0, r = 0;
    z[0] = n;
    for (int i = 1; i <= n; ++i) {
        z[i] = i > r ? 0 : min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) r = i + z[l = i] - 1;
    }
}
// t 与 s 的每一个后缀的 LCP 长度数组
void exKMP(const char *s, const char *t, int *z, int *p, int sn) {// get p
    int l = -1, r = -1;
    for (int i = 0; i <= sn; ++i) {
        p[i] = i > r ? 0 : min(r - i + 1, z[i - l]);
        while (i + p[i] < sn && t[p[i]] == s[i + p[i]]) ++p[i];
        if (i + p[i] - 1 > r) r = i + p[l = i] - 1;
    }
}
