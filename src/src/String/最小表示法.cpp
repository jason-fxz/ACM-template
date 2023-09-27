//n为串长，a下标从0开始
int Min_show(int *a, int n) {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        auto u = a[(i + k) % n];
        auto v = a[(j + k) % n];
        if (u == v) ++k;
        else {
            if (u > v) i += k + 1;
            else j += k + 1;
            if (i == j) ++j;
            k = 0;
        }
    }
    return min(i, j);
}
