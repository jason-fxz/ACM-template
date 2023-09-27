const int M=1e5;
bool vis[M << 1];
char s[M];
int id[M << 1], ch[M << 1][26], height[M], tim = 0;
void dfs(int x) {
	if (id[x]) {
		height[tim++] = val[lst];
		sa[tim] = id[x];
		lst = x;
	}
	for (int c = 0; c < 26; ++c)
		if (son[x][c]) dfs(son[x][c]);
	lst = fa[x];
}
int main() {
	lst = ++cnt;
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = n; i; --i) {
		expand(s[i] - 'a');
		id[lst] = i;
	}
	vis[1] = 1;
	for (int i = 1; i <= cnt; ++i) if (id[i])
			for (int x = i,pos = n; x && !vis[x]; x = fa[x]) {
				vis[x] = 1;
				pos -= val[x] - val[fa[x]];
				son[fa[x]][s[pos + 1] - 'a'] = x;
			}
	dfs(1);
	for (int i = 1; i <= n; ++i) printf("%d",sa[i]); puts("");
	for (int i = 1; i < n; ++i) printf("%d",height[i]); puts("");
	return 0;
}
