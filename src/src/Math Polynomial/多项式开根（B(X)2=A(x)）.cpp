void NTT(int *a, int op) {
	for (int i = 1; i < len; ++i)
		if(rev[i] < i) swap(a[rev[i]], a[i]);
	for (int mid = 1; mid < len; mid <<= 1) {
		int wn = POW(op ? gi : g, (P - 1) / (mid << 1));
		for (int l = 0; l < len; l += mid << 1) {
			int w = 1;
			for (int i = l; i < l + mid; ++i) {
				int u = a[i];
				int v = 1ll * w * a[i + mid] % P;
				a[i] = MOD(u + v);
				a[i + mid] = MOD(u - v);
				w = 1ll * w * wn % P;
			}
		}
	}
	if(op) {
		int w = POW(len);
		for (int i = 0; i < len; ++i)
			a[i] = 1ll * a[i] * w % P;
	}
}
void Inv(int *a, int *b, int n) {
	if(n == 1)return b[0] = POW(a[0]), void();
	Inv(a, b, (n + 1) >> 1);
	for (len = 1, t = 0; len < n << 1; len <<= 1) ++t;
	for (int i = 1; i < len; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
	for (int i = 0; i < n; ++i) A[i] = a[i];
	for (int i = n; i <= len; ++i) A[i] = 0;
	for (int i = n; i <= len; ++i) b[i] = 0;
	NTT(A, 0);
	NTT(b, 0);
	for (int i = 0; i < len; ++i)
		b[i] = 1ll * MOD(2 - 1ll * A[i] * b[i] % P) * b[i] % P;
	NTT(b, 1);
	for (int i = n; i <= len; ++i) b[i] = 0;
}
void Sqrt(int *a, int *b, int n) {
	if(n == 1)return b[0] = 1, void();
	Sqrt(a, b, (n + 1) >> 1);
	Inv(b, D, n);
	for (len = 1,t = 0; len < n << 1; len <<= 1) ++t;
	for (int i = 1; i < len; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
	for (int i = 0; i < n; ++i) C[i] = a[i];
	for (int i = n; i <= len; ++i) C[i] = 0;
	NTT(C, 0);
	NTT(D, 0);
	for (int i = 0; i < len; ++i)
		C[i] = 1ll * C[i] * D[i] % P;
	NTT(C, 1);
	for (int i = 0; i < n; ++i)
		b[i] = 1ll * MOD(b[i] + C[i]) * inv2 % P;
	for (int i = n; i <= len; ++i) b[i] = 0;
}
