int len[M], fa[M], son[M][26], lst, cnt, f[M], val[M];
char s[M];
int extend(int n){
	int p = lst, c = s[n] - 'a';
	while (s[n - len[p] - 1] != s[n]) p = fa[p];
	if (!son[p][c]){
		int now = p;
		len[++cnt] = len[p] + 2; // 回文串长度
		p = fa[p];
		while (s[n - len[p] - 1] != s[n]) p = fa[p];
		fa[cnt] = son[p][c];
		lst = son[now][c] = cnt;
		f[cnt] = f[fa[cnt]] + 1;
	}
	else lst = son[p][c];
	++val[lst];
	return f[lst]; // 返回原串以第i个字符结尾的回文子串个数
}
int main(){
	fa[0] = cnt = 1;
	len[1] = -1;

	for (int i = cnt; i; --i) val[fa[i]] += val[i];
		// 统计回文串出现的次数
}
