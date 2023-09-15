//给定一个带边权的无向连通图G,再给定包含k个结点的点集S,选出G的子图G'，使得G'包含S，G'为连通图，且G'边权和最小
#include<bits/stdc++.h>
#define mp make_pair
#define zjx printf("%d",
#define AK dp[c[1]][(1<<k)-1]
#define IOI );
using namespace std;
int n,m,k,p,h[101],dp[101][1024],c[11],vis[101];
struct tree
{
	int to,ne,v;
}a[1001];
void add(int x,int y,int z)
{
	a[++p].to=y;
	a[p].ne=h[x];
	a[p].v=z;
	h[x]=p;
}
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
void dijkstra(int s)
{
	memset(vis,0,sizeof(vis));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=h[x];i;i=a[i].ne)
		{
			if(dp[a[i].to][s]>dp[x][s]+a[i].v)
			{
				dp[a[i].to][s]=dp[x][s]+a[i].v;
				q.push(mp(dp[a[i].to][s],a[i].to));
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=k;i++)scanf("%d",&c[i]),dp[c[i]][1<<(i-1)]=0;
	for(int s=1;s<(1<<k);s++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int ss=s&(s-1);ss;ss=(ss-1)&s)
			dp[i][s]=min(dp[i][s],dp[i][ss]+dp[i][ss^s]);
			if(dp[i][s]!=0x3f3f3f3f)q.push(mp(dp[i][s],i));
		}
		dijkstra(s);
	}
	zjx AK IOI
	return 0;
}