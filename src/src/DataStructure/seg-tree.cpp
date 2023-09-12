/*
 * seg-beats 吉司机线段树
 * 区间最值操作
 * 支持 区间取min，区间取max，区间加减，区间求和，区间最小/大
 * 复杂度 O(m log n)
 */
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
typedef long long ll;
const int N = 500010;
const int inf = 0x3f3f3f3f;
struct datmn {
    int fi, se, cnt; // 最小值，次小值，最小值个数
    datmn() {fi = se = inf; cnt = 0;}
    void ins(int x, int c) {
        if (x < fi) se = fi, cnt = c, fi = x;
        else if (x == fi) cnt += c;
        else if (x < se) se = x;
    }
    friend datmn operator+(const datmn &a, const datmn &b) {
        datmn r = a; r.ins(b.fi, b.cnt); r.ins(b.se, 0); return r;
    }
};
struct datmx {
    int fi, se, cnt;
    datmx() {fi = se = -inf; cnt = 0;}
    void ins(int x, int c) {
        if (x > fi) se = fi, cnt = c, fi = x;
        else if (x == fi) cnt += c;
        else if (x > se) se = x;
    }
    friend datmx operator+(const datmx &a, const datmx &b) {
        datmx r = a; r.ins(b.fi, b.cnt); r.ins(b.se, 0); return r;
    }
};

struct node {
    datmn mn; datmx mx;
    ll sum; int addmn, addmx, add, len; 
} t[N << 2];
int n, m, a[N];
void pushup(int x) {
    t[x].mx = t[ls].mx + t[rs].mx;
    t[x].mn = t[ls].mn + t[rs].mn;
    t[x].sum = t[ls].sum + t[rs].sum;
}
void build(int l = 1, int r = n, int x = 1) {
    t[x].add = t[x].addmn = t[x].addmx = 0;
    t[x].len = r - l + 1;
    if (l == r) {
        t[x].mx = datmx(); t[x].mx.ins(a[l], 1);
        t[x].mn = datmn(); t[x].mn.ins(a[l], 1);
        t[x].sum = a[l];
        return;
    }
    build(l, mid, ls); build(mid + 1, r, rs);
    pushup(x);
}
void update(int x, int vn, int vx, int v) { // vn: addmn, vx: addmx, v: add
    // 所有数相同特判，此时最大值 tag 和最小值 tag 应该相同且不等于其他值 tag
    if (t[x].mn.fi == t[x].mx.fi) { 
        if (vn == v) vn = vx;
        else vx = vn;
        t[x].sum += (ll)vn * t[x].mn.cnt;
    } else t[x].sum += (ll)vn * t[x].mn.cnt + (ll) vx * t[x].mx.cnt + (ll)v * (t[x].len - t[x].mn.cnt - t[x].mx.cnt);
    if (t[x].mn.se == t[x].mx.fi) t[x].mn.se += vx; // 次小值 = 最大值，应该用最大值 tag 处理
    else if (t[x].mn.se != inf) t[x].mn.se += v;
    if (t[x].mx.se == t[x].mn.fi) t[x].mx.se += vn; // 次大值同理
    else if (t[x].mx.se != -inf) t[x].mx.se += v;
    t[x].mn.fi += vn; t[x].mx.fi += vx;
    t[x].addmn += vn; t[x].addmx += vx; t[x].add += v;
}
void pushdown(int x) {
    int mn = min(t[ls].mn.fi, t[rs].mn.fi);
    int mx = max(t[ls].mx.fi, t[rs].mx.fi);
    update(ls, (mn == t[ls].mn.fi) ? t[x].addmn : t[x].add, (mx == t[ls].mx.fi) ? t[x].addmx : t[x].add, t[x].add);
    update(rs, (mn == t[rs].mn.fi) ? t[x].addmn : t[x].add, (mx == t[rs].mx.fi) ? t[x].addmx : t[x].add, t[x].add);
    t[x].add = t[x].addmn = t[x].addmx = 0;
}
void modifyadd(int L, int R, int v, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return ;
    if (L <= l && r <= R) return update(x, v, v, v);
    pushdown(x);
    modifyadd(L, R, v, l, mid, ls);
    modifyadd(L, R, v, mid + 1, r, rs);
    pushup(x);
}
void modifymin(int L, int R, int v, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return ;
    if (L <= l && r <= R && v > t[x].mx.se) {
        if (v >= t[x].mx.fi) return ;
        update(x, 0, v - t[x].mx.fi, 0);
        return;
    }
    pushdown(x);
    modifymin(L, R, v, l, mid, ls);
    modifymin(L, R, v, mid + 1, r, rs);
    pushup(x);
}
void modifymax(int L, int R, int v, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return ;
    if (L <= l && r <= R && v < t[x].mn.se) {
        if (v <= t[x].mn.fi) return;
        update(x, v - t[x].mn.fi, 0, 0);
        return;
    }
    pushdown(x);
    modifymax(L, R, v, l, mid, ls);
    modifymax(L, R, v, mid + 1, r, rs);
    pushup(x);
}
int querymax(int L, int R, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return -inf;
    if (L <= l && r <= R) return t[x].mx.fi;
    pushdown(x);
    return max(querymax(L, R, l, mid, ls), querymax(L, R, mid + 1, r, rs));
}
int querymin(int L, int R, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return inf;
    if (L <= l && r <= R) return t[x].mn.fi;
    pushdown(x);
    return min(querymin(L, R, l, mid, ls), querymin(L, R, mid + 1, r, rs));
}
ll querysum(int L, int R, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return 0;
    if (L <= l && r <= R) return t[x].sum;
    pushdown(x);
    return querysum(L, R, l, mid, ls) + querysum(L, R, mid + 1, r, rs);
}