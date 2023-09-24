char s[M << 1];
int p[M];
//nΪ������a�±��1��ʼ��pΪ���Ĵ��뾶(0~2n+1) 
void Manacher(const char *a, int n) {
	int r = 0, mid;
	for (int i = 1; i <= n; ++i) s[i << 1] = a[i];
	for (int i = 0; i <= n; ++i) s[i * 2 + 1] = '#';
	s[0] = '#'; n = n << 1 | 1;
	
	for (int i = 1; i <= n; ++i) {
		p[i] = (i <= r ? min(p[mid * 2 - i], p[mid] + mid - i) : 1);
		while (s[i - p[i] - 1] == s[i + p[i] + 1]) ++p[i];
		if (i + p[i] > r) r = i + p[i] , mid = i;
	}
}
