// 李超线段树 对于 (x1,y1) (x2,y2) -> y=0*x+max(y1,y2) [x1,x1]
#define ls (x<<1)
#define rs (x<<1|1)
typedef long long ll;
typedef double db;
const int N = 100010;
const int M = 40000;
struct line {
    db k, b;
} lin[N];
db val(int id, db X) {return lin[id].k * X + lin[id].b;}
int D[N << 2], n, id;
void modify(int L, int R, int id, int l = 1, int r = M - 1, int x = 1) { // 线 lin[id], 范围 [L, R]
    if (L <= l && r <= R) {
        int mid = (l + r) >> 1, lid = D[x];
        db lst = val(D[x], mid), now = val(id, mid);
        if (l == r) {if (now > lst) D[x] = id; return ;}
        if (lin[id].k > lin[D[x]].k) {
            if (now > lst) D[x] = id, modify(L, R, lid, l, mid, ls); // id->lid
            else modify(L, R, id, mid + 1, r, rs);
        } else if (lin[id].k < lin[D[x]].k) {
            if (now > lst) D[x] = id, modify(L, R, lid, mid + 1, r, rs); // id->lid
            else modify(L, R, id, l, mid, ls);
        } else if (lin[id].b > lin[D[x]].k) D[x] = id;
        return ;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) modify(L, R, id, l, mid, x << 1);
    if (R > mid) modify(L, R, id, mid + 1, r, x << 1 | 1);
}
int gmax(int x, int y, int ps) {
    if (val(x, ps) > val(y, ps)) return x;
    if (val(x, ps) < val(y, ps)) return y;
    return (x < y) ? x : y;
}
int query(int ps, int l = 1, int r = M - 1, int x = 1) { // 查 x=ps
    if (l == r) return D[x];
    int mid = (l + r) >> 1, ret = D[x], t = 0;
    if (ps <= mid)
        t = query(ps, l, mid, ls);

    else
        t = query(ps, mid + 1, r, rs);
    return gmax(ret, t, ps);
}
