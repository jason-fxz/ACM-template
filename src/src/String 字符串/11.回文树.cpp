int len[M], fa[M], son[M][26], lst, cnt, f[M];
char s[M];
int extend(int n) {
	int p = lst, c = s[n] - 'a';
	while (s[n - len[p] - 1] != s[n]) p = fa[p];
	if (!son[p][c]) {
		int now = p;
		len[++cnt] = len[p] + 2;//回文串长度 
		p = fa[p];
		while(s[n - len[p] - 1] != s[n]) p = fa[p];
		fa[cnt] = son[p][c];
		lst = son[now][c] = cnt;
		f[cnt] = f[fa[cnt]] + 1;//回文串数量 
	}
	else lst = son[p][c];
	return f[lst];
}
int main() {
	fa[0] = cnt = 1;
	val[1] = -1;
}
