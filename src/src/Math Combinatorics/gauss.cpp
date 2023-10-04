// 系数零场数非零：无解；系数零常数零：无穷解。
void gauss() {
    for (int j = 1; j <= n; j++) {
        int mxp = j;
        for (int i = j + 1; i <= n; i++)
            if (fabs(a[i][j]) > fabs(a[mxp][j])) mxp = i;
        for (int i = 1; i <= n + 1; i++)
            swap(a[j][i], a[mxp][i]);
        if (a[j][j] == 0) continue;
        for (int i = 1; i <= n; i++) {
            if (i == j) continue;
            double tmp = a[i][j] / a[j][j];
            for (int k = 1; k <= n + 1; k++)
                a[i][k] -= a[j][k] * tmp;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%.6lf\n", a[i][n + 1] / a[i][i]);
}