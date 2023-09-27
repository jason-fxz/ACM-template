struct com {
	db a,b;
	com operator + (const com &x)const {
		return (com) {a + x.a, b + x.b};
	}
	com operator - (const com &x)const {
		return (com) {a - x.a, b - x.b};
	}
	com operator * (const com &x)const {
		return (com) {a * x.a - b * x.b, a * x.b + b * x.a};
	}
} a[T], b[T];
void FFT(com *a, int p) {
	for (int i = 0; i < lmt; ++i)
		if(i < rev[i])swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < lmt; mid <<= 1) {
		com Xn;
		Xn = (com){cos(pi / mid), sin(pi * p / mid)};
		for (int l = 0; l < lmt; l += mid << 1) {
			com x; x = (com){1,0};
			for (int i = 0; i < mid; ++i) {
				com u = a[l + i],v = x * a[l + mid + i];
				a[l + i] = u + v;
				a[l + mid + i] = u - v;
				x = x * Xn;
			}
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i = 0; i <= n; ++i) scanf("%lf",&a[i].a);
	for (int i = 0; i <= m; ++i) scanf("%lf",&b[i].a);
	lmt = 1;
	while (lmt <= n + m)lmt <<= 1, ++t;
	for (int i = 0; i < lmt; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i &1 ) << (t - 1));
	FFT(a, 1);
	FFT(b, 1);
	for (int i = 0; i < lmt; ++i) a[i] = a[i] * b[i];
	FFT(a, -1);
	for (int i = 0; i <= n + m; ++i) printf("%d ",(int)(a[i].a / lmt + 0.5));
	return 0;
}
