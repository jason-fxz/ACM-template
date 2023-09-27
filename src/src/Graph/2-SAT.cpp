int n, m, h[2000001], p, tot, t;
int ans[2000001], cnt, bel[2000001], dfn[2000001], low[2000001], inz[2000001], z[2000001];
char c[2000001];
struct pp {
    int to, ne;
} b[2000001];
void add(int x, int y) {
    b[++p].to = y;
    b[p].ne = h[x];
    h[x] = p;
}
void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    z[++t] = x; inz[x] = 1;
    for (int i = h[x]; i; i = b[i].ne) {
        int v = b[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
        } else if (inz[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (dfn[x] == low[x]) {
        tot++;
        do {
            bel[z[t]] = tot;
            inz[z[t]] = 0;
        } while (z[t--] != x);
    }
}
bool solve() {
    for (int i = 1; i <= 2 * n; i++) 
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (bel[i] == bel[i + n]) return 0;
    return 1;
}
int main() {
    scanf("%d%d", &n, &m); p = 0;
    for (int i = 1; i <= m; i++) {
        int xx, yy, x, y;
        scanf("%d%d%d%d", &xx, &x, &yy, &y);
        add(xx + (x ^ 1)*n, yy + y * n);
        add(yy + (y ^ 1)*n, xx + x * n);
    }
    if (solve()) {
        printf("POSSIBLE\n");
        for (int i = 1; i <= n; i++) {
            if (bel[i] < bel[i + n]) printf("0 ");
            else printf("1 ");
        }
    } else printf("IMPOSSIBLE\n");
    return 0;
}