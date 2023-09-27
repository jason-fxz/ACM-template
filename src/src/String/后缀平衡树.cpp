#include <bits/stdc++.h>
using namespace std;
const int M = 3e6 + 5;
const double INF = 1e18;

void decode(char *s, int len, int mask) {
	for (int i = 0; i < len; ++i) {
		mask = (mask * 131 + i) % len;
		swap(s[i], s[mask]);
	}
}
int q, n, len;
char s[M], t[M];
// 顺序加入，查询时将询问串翻转
// 以i结束的前缀，对应节点的编号为i
// 注意：不能写懒惰删除，否则可能会破坏树的结构
const double alpha = 0.75;
int rt, sz[M], ls[M], rs[M];
double tag[M];
int buffer_size, buffer[M];

bool cmp(int x, int y) {
	if (t[x] != t[y]) return t[x] < t[y];
	return tag[x - 1] < tag[y - 1];
}
void nw(int &rt, int p, double lv, double rv) {
	sz[rt = p] = 1;
	tag[rt] = (lv + rv) / 2;
	ls[rt] = rs[rt] = 0;
}
void Up(int x) {
	if (!x) return;
	sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
}
bool balance(int rt) {
	return alpha * sz[rt] > max(sz[ls[rt]], sz[rs[rt]]);
}
void flatten(int rt) {
	if (!rt) return;
	flatten(ls[rt]);
	buffer[++buffer_size] = rt;
	flatten(rs[rt]);
}
void build(int &rt, int l, int r, double lv, double rv) {
	if (l > r) return rt = 0, void();
	int mid = (l + r) >> 1;
	double mv = (lv + rv) / 2;
	rt = buffer[mid];
	tag[rt] = mv;
	build(ls[rt], l, mid - 1, lv, mv);
	build(rs[rt], mid + 1, r, mv, rv);
	Up(rt);
}
void rebuild(int &rt, double lv, double rv) {
	buffer_size = 0;
	flatten(rt);
	build(rt, 1, buffer_size, lv, rv);
}
void ins(int& rt, int p, double lv = 0, double rv = INF) {
	if (!rt) return nw(rt, p, lv, rv), void();
	if (cmp(p, rt)) ins(ls[rt], p, lv, tag[rt]);
	else ins(rs[rt], p, tag[rt], rv);
	Up(rt);
	if (!balance(rt)) rebuild(rt, lv, rv);
}
void remove(int &rt, int p, double lv = 0, double rv = INF) {
	if (!rt) return;
	if (rt == p) {
		if (!ls[rt] || !rs[rt]) {
			rt = (ls[rt] | rs[rt]);
			rebuild(rt, lv, rv);
		}
		else {
			int nrt = ls[rt];
			while (rs[nrt]) nrt = rs[nrt];
			remove(ls[rt], nrt, lv, tag[rt]);
			ls[nrt] = ls[rt];
			rs[nrt] = rs[rt];
			rt = nrt;
			tag[rt] = (lv + rv) / 2;
		}
	} 
	else {
		double mv = (lv + rv) / 2;
		if (cmp(p, rt)) remove(ls[rt], p, lv, mv);
		else remove(rs[rt], p, mv, rv);
	}
	Up(rt);
	if (!balance(rt)) rebuild(rt, lv, rv);
}
bool qry_cmp(char *s, int len, int p) {
	for (int i = 1; i <= len; ++i, --p)
		if (s[i] != t[p]) return s[i] < t[p];
	return 0;
}
int qry(int rt, char *s, int len) {
	if (!rt) return 0;
	if (qry_cmp(s, len, rt)) return qry(ls[rt], s, len);
	else return sz[ls[rt]] + 1 + qry(rs[rt], s, len);
}
int main() {
	scanf("%d", &q);
	scanf("%s", s + 1); len = strlen(s + 1);
	for (int i = 1; i <= len; ++i) 
		t[++n] = s[i], ins(rt, n);
	int mask = 0;
	char op[10];
	for (int i = 1; i <= q; ++i) {
		scanf("%s", op);
		if (op[0] == 'A') {
			scanf("%s", s + 1); len = strlen(s + 1);
			decode(s + 1, len, mask);
			for (int i = 1; i <= len; ++i) 
				t[++n] = s[i], ins(rt, n);
		} 
		if (op[0] == 'D') {
			int x; scanf("%d", &x);
			while (x--) remove(rt, n), --n;
		} 
		if (op[0] == 'Q') {
			scanf("%s", s + 1); len = strlen(s + 1);
			decode(s + 1, len, mask);
			reverse(s + 1, s + len + 1);
			s[len + 1] = 'Z' + 1;
			s[len + 2] = 0;
			int ans = qry(rt, s, len + 1);
			--s[len];
			ans -= qry(rt, s, len + 1);
			printf("%d\n", ans);
			mask ^= ans;
		}
	}
	return 0;
}

