// 强连通分量
void tarjan(int x){
	dfn[x]=low[x]=++tot;
	s[++len]=x;
	instack[x]=1;
    for(int i=head[x];i;i=e[i].next){
    	int y=e[i].to;
    	if(!dfn[y]){
    		tarjan(y);
    		low[x]=min(low[x],low[y]);
		}else{
		    if(instack[y])low[x]=min(low[x],low[y]);
		}
	}
	if(dfn[x]==low[x]){
	    cnt++;
	    ans[cnt].push_back(x);
	    while(s[len]!=x){
	    	belong[s[len]]=cnt;
	    	instack[s[len]]=0;
	    	ans[cnt].push_back(s[len]);
	    	len--;
		}
		len--;
		instack[x]=0;
		belong[x]=cnt;
	}
}
// 边双
void tarjan(int x, int las){
	low[x] = dfn[x] = ++cnt;
	st.push(x);
	for (auto i: e[x]){
		if (i == las) continue;
		if (!dfn[i]){
			tarjan(i, x);
			low[x] = min(low[x], low[i]);
		}else low[x] = min(low[x], dfn[i]);
	}
	if (dfn[x] == low[x]){
		vector<int> vec;
		vec.push_back(x);
		while (st.top() != x){
			vec.push_back(st.top());
			st.pop();
		}
		st.pop();
		ans.push_back(vec);
	}
}
// 点双
void tarjan(int x,int root)//求割点的改版（其实不需要root）
{
	dfn[x]=low[x]=++cnt;
	if(x==root&&!head[x])//孤立点判定
	{
		dcc[++ans].push_back(x);
	}
	sta.push(x);
	for(int i=head[x];i;i=nxt[i])
	{
		int g=go[i];
		if(!dfn[g])
		{
			tarjan(g,root);
			low[x]=min(low[x],low[g]);
			if(low[g]>=dfn[x])
			{
				ans++;
				int p;
				do{//弹栈
					p=sta.top();
					sta.pop();
					dcc[ans].push_back(p);
				}while(p!=g);//注意此处，因为要求是不到达出点
				dcc[ans].push_back(x);//别忘了加入源点！
			}
		}
		else
		low[x]=min(low[x],dfn[g]);
	}
}