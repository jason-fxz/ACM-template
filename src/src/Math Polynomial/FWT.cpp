void OR(int *a, int len, int x) {
	for (int mid = 1; mid < len; mid <<= 1)
		for (int l = 0; l < len; l += mid << 1)
			for (int i = l; i <= l + mid - 1; ++i)
				ADD(a[i + mid], 1ll * a[i] * x % P);
}
void AND(int *a,int len,int x) {
	for (int mid = 1; mid < len; mid <<= 1)
		for (int l = 0; l < len; l += mid << 1)
			for (int i = l; i <= l + mid - 1; ++i)
				ADD(a[i], 1ll * a[i + mid] * x % P);
}
void XOR(int *a,int len,int x) {
	for (int mid = 1; mid < len; mid <<= 1)
		for (int l = 0; l < len; l += mid << 1)
			for (int i = l; i <= l + mid - 1; ++i) {
				int u = a[i], v = a[i + mid];
				a[i] = 1ll * MOD(u + v) * x % P;
				a[i + mid] = 1ll * MOD(u - v) * x % P;
		}
}
int main() {
	...
	for (int i = 0; i < len; ++i) 
		a[i] = A[i], b[i] = B[i];
	OR(a, len, 1);
	OR(b, len, 1);
	for (int i = 0; i < len; ++i) 
		a[i] = 1ll * a[i] * b[i] % P;
	OR(a, len, -1);
	...
	for (int i = 0; i < len; ++i) 
		a[i] = A[i], b[i] = B[i];
	AND(a, len, 1);
	AND(b, len, 1);
	for (int i = 0; i < len; ++i) 
		a[i] = 1ll * a[i] * b[i] % P;
	AND(a, len, -1);
	...
	for (int i = 0; i < len; ++i) 
		a[i] = A[i], b[i] = B[i];
	XOR(a, len, 1);
	XOR(b, len, 1);
	for (int i = 0; i < len; ++i) 
		a[i] = 1ll * a[i] * b[i] % P;
	XOR(a, len, inv);
	...
}
