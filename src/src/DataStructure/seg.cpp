int merge(int p, int q, int l = 1, int r = totval) {
    if (!p || !q) return p + q;
    if (l == r) {
        t[p].cnt += t[q].cnt;
        return p;
    }
    int mid = (l + r) >> 1;
    ls(p)= merge(ls(p), ls(q), l, mid);
    rs(p) = merge(rs(p), rs(q), mid + 1, r);
    pushup(p);
    pushup(q);
    return p;
}
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = s + t >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  pushup(p);
  pushup(q);
}
void split(int p, int &q, int k, int l = 1, int r = totval) {
    // printf("split: %d %d %d [%d,%d]\n", p, q, k, l, r);
    if (l == r) {
        q = newnode();
        t[q].cnt = t[p].cnt - k;
        t[p].cnt = k;
        return ;
    }
    int mid = (l + r) >> 1;
    q = newnode();
    if (k <= t[ls(p)].cnt) {
        rs(q) = rs(p); rs(p) = 0;
        split(ls(p), ls(q), k, l, mid);
    } else {
        k -= t[ls(p)].cnt;
        split(rs(p), rs(q), k, mid + 1, r);
    }
    pushup(p); pushup(q);
}