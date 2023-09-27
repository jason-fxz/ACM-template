int lst = 1, cnt = 1, len[M], fa[M], son[M][26];
void Extend(int c) { // 结点数要开成串长的两倍
    int p = lst, np = lst = ++cnt;
    len[np] = len[p] + 1;
    for (; p && !son[p][c]; p = fa[p]) son[p][c] = np;
    if (!p) return fa[lst = np] = 1, void();
    int q = son[p][c];
    if (len[q] == len[p] + 1)
        return fa[lst = np] = q, void();
    int nq = ++cnt;
    len[nq] = len[p] + 1;
    fa[nq] = fa[q];
    fa[np] = fa[q] = nq;
    memcpy(son[nq], son[q], sizeof(son[q]));
    for (; p && son[p][c] == q; p = fa[p]) son[p][c] = nq;
    lst = np;
}
int c[M], q[M];
int main() {
    for (int i = 1; i <= n ; ++i) Extend(s[i] - 'a');
    for (int i = 1; i <= cnt; i++) ++c[len[i]];
    for (int i = 1; i <= cnt; i++) c[i] += c[i - 1];
    for (int i = 1; i <= cnt; i++) q[c[len[i]]--] = i;
    return 0;
}
