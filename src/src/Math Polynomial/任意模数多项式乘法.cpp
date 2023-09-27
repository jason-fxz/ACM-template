const int P1 = 469762049, P2 = 998244353, P3 = 1004535809;
int n, m, P, rev[M], a[M], b[M], c[M], d[M], ans[3][M], lmt=1, t;
int PW(int x, int y, int P) {
	int res = 1;
	for (; y; y >>= 1) {
		if(y & 1)res = 1ll * res * x % P;
		x = 1ll * x * x % P;
	}
	return res;
}
LL MUL(LL a, LL b, LL P) {
	a %= P; b %= P;
	return ((a * b - (LL)((LL)((db)a / P * b + 1e-3) * P)) % P + P) % P;
}
void NTT(int *a, int op, int P) {
	for (int i = 0; i < lmt; ++i)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < lmt; mid <<= 1) {
		int wn = PW(3, (P - 1) / (mid << 1), P);
		for (int l = 0; l < lmt; l += mid << 1) {
			int w = 1;
			for (int i = 0; i < mid; ++i) {
				int u = a[l + i];
				int v = 1ll * w * a[l + mid + i]% P;
				a[l + i] = (u + v) % P;
				a[l + mid + i] = (u - v + P) % P;
				w = 1ll * w * wn % P;
			}
		}
	}
	if(!op) {
		int inv = PW(lmt, P - 2, P);
		a[0] = 1ll * a[0] * inv % P;
		for (int i = 1; i <= lmt>>1; ++i) {
			a[i] = 1ll * a[i] * inv % P;
			if (i != lmt - i) {
				a[lmt - i] = 1ll * a[lmt - i] * inv % P;
				swap(a[i], a[lmt - i]);
			}
		}
	}
}
int main() {
	n = rd(); m = rd(); P = rd();
	for (int i = 0; i <= n; ++i) a[i] = rd();
	for (int i = 0; i <= m; ++i) b[i] = rd();
	while (lmt <= n + m) lmt <<= 1, ++t;
	for (int i = 0; i < lmt; ++i) 
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
	copy(a, a + n + 1, c);
	copy(b, b + m + 1, d);
	NTT(c, 1, P1);
	NTT(d, 1, P1);
	for (int i = 0; i < lmt; ++i)
		ans[0][i] = 1ll * c[i] * d[i] % P1;
	NTT(ans[0], 0, P1);
	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	copy(a, a + n + 1, c);
	copy(b, b + m + 1, d);
	NTT(c, 1, P2);
	NTT(d, 1, P2);
	for (int i = 0; i < lmt; ++i)
		ans[1][i] = 1ll * c[i] * d[i] % P2;
	NTT(ans[1], 0, P2);
	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	copy(a, a + n + 1, c);
	copy(b, b + m + 1, d);
	NTT(c, 1, P3);
	NTT(d, 1, P3);
	for (int i = 0; i < lmt; ++i)
		ans[2][i] = 1ll * c[i] * d[i] % P3;
	NTT(ans[2], 0, P3);
	LL f1 = 1ll * P1 * P2;
	int inv1 = PW(P2 % P1, P1 - 2, P1);
	int inv2 = PW(P1 % P2, P2 - 2, P2);
	int inv3 = PW(f1 % P3, P3 - 2, P3);
	for (int i = 0; i <= n + m; ++i) {
		LL A = (MUL(1ll * ans[0][i] * P2 % f1, inv1, f1)+
				MUL(1ll * ans[1][i] * P1 % f1, inv2, f1))%f1;
		LL k = ((ans[2][i] - A) % P3 + P3) % P3 * inv3 % P3;
		printf("%lld ",((k % P) * (f1 % P) % P + A % P) % P);
	}
	return 0;
}
