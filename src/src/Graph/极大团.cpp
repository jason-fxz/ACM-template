const int maxn = 129;
int n, m, S;
int some[maxn][maxn], all[maxn][maxn], none[maxn][maxn], g[maxn][maxn];
void dfs(int d, int an, int sn, int nn) {
    if (!sn && !nn) ++S;
    if (S > 1000) return; //题意表明S超过1000就输出Impossible
    int u = some[d][0];
    for (int i = 0; i < sn; ++i) {
        int v = some[d][i];
        if (g[u][v]) continue;
        int tsn = 0, tnn = 0;
        //for(int j=0; j<an; ++j) all[d+1][j]=all[d][j];
        //all[d+1][an]=v;  //可以不写这两行
        for (int j = 0; j < sn; ++j) if (g[v][some[d][j]])
                some[d + 1][tsn++] = some[d][j];
        for (int j = 0; j < nn; ++j) if (g[v][none[d][j]])
                none[d + 1][tnn++] = none[d][j];
        dfs(d + 1, an + 1, tsn, tnn);
        some[d][i] = 0, none[d][nn++] = v;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        S = 0;
        memset(g, 0, sizeof(g));
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a][b] = g[b][a] = 1;
        }
        for (int i = 0; i < n; ++i) some[0][i] = i + 1; //some的初始化
        dfs(0, 0, n, 0);
        if (S > 1000) cout << "Too many maximal sets of friends." << endl;
        else cout << S << endl;
    }
}
