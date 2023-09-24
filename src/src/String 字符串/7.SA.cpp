// rnk:排名，sa:位置
// height[i] = lcp(sa[i], sa[i - 1])
// M开两倍 
void get_sa(char *s, int n, int *sa, int *rnk, int *height) { // 1-based
	static int c[M], p[M], t[M];
	int m = 300;
	for (int i = 1; i <= n; ++i) ++c[p[i] = s[i]];
	for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i; --i) sa[c[p[i]]--] = i;
	for (int k = 1; k < n ; k <<= 1) {
		int cnt = 0;
		for (int i = n - k + 1; i <= n; ++i) t[++cnt] = i;
		for (int i = 1; i <= n; ++i) if (sa[i] > k) t[++cnt] = sa[i] - k;
		for (int i = 1; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[p[i]];
		for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i; --i) sa[c[p[t[i]]]--] = t[i], t[i] = 0;
		swap(p,t);
		p[sa[1]] = cnt = 1;
		for (int i = 2; i <= n; ++i) {
			if (t[sa[i]] != t[sa[i - 1]] || t[sa[i] + k] != t[sa[i - 1] + k]) ++cnt;
			p[sa[i]] = cnt;
		}
		if(cnt == n) break;
		m = cnt;
	}
	for (int i = 1; i <= n; i++) rnk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; i++) {
		if (k) k--;
		while (s[i + k] == s[sa[rnk[i] - 1] + k]) k++;
		height[rnk[i]] = k;
	}
}
char s[M];
int sa[M], rnk[M], height[M];
int main() {
	cin >> (s + 1);
	int n = strlen(s + 1);
	get_sa(s, n, sa, rnk, height);
	for (int i = 1; i <= n; i++)
		cout << sa[i] << (i < n ? ' ' : '\n');
	for (int i = 2; i <= n; i++)
		cout << height[i] << (i < n ? ' ' : '\n');
	return 0;
}
