const int g = 3, gi = 332748118;
void NTT(int *a, int op) {
	for (int i = 1; i < len; ++i) 
		if (rev[i] < i) swap(a[rev[i]], a[i]);
	for (int mid = 1; mid < len; mid <<= 1) {
		int wn = POW(op ? gi : g, (P - 1) / (mid << 1));
		for (int l = 0; l < len; l += mid << 1) {
			int w = 1;
			for (int i = l; i < l + mid; ++i) {
				int u = a[i],v = 1ll * w * a[i + mid] % P;
				a[i] = MOD(u + v);
				a[i + mid] = MOD(u - v);
				w = 1ll * w * wn % P;
			}
		}
	}
	if (op) {
		int w = POW(len);
		for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * w % P;
	}
}
void solve(int n, int *a, int *b) {
	if (n == 1) return b[0] = POW(a[0]), void();
	solve((n + 1) >> 1, a, b);
	for (len = 1, t = 0; len < n << 1; len <<= 1) ++t;
	for (int i = 1; i < len; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
	for (int i = 0; i < n; ++i) c[i] = a[i];
	for (int i = n; i < len; ++i) c[i] = 0;
	NTT(c, 0);
	NTT(b, 0);
	for (int i = 0; i < len; ++i) b[i] = (2 - 1ll * c[i] * b[i] % P) * b[i] % P;
	NTT(b, 1);
	for (int i = n; i < len; ++i) b[i] = 0;
}
