int son[M][26], fail[M], cnt = 0;
void ins(const char *s) {
    int p = 0, n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        int c = s[i] - 'a';
        if (!son[p][c]) son[p][c] = ++cnt;
        p = son[p][c];
    }
}
queue<int> q;
void get_fail() {
    for (int c = 0; c < 26; ++c)
        if (son[0][c]) q.push(son[0][c]);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int c = 0; c < 26; ++c) {
            if (son[x][c]) {
                fail[son[x][c]] = son[fail[x]][c];
                q.push(son[x][c]);
            } else son[x][c] = son[fail[x]][c];
        }
    }
}

