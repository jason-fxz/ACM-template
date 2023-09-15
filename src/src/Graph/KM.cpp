#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
int n,N,M,k,d[501][501],match[501],ka[501],kb[501],visb[501],visa[501],p[501];
long long c[501],delta;
void bfs(int x)
{
	int a,y=0,yy=0;
	for(int i=1;i<=n;i++)p[i]=0,c[i]=1e18;
	match[y]=x;
	do
	{
		a=match[y],delta=1e18,visb[y]=1;
		for(int b=1;b<=n;b++)
		{
			if(!visb[b])
			{
				if(c[b]>ka[a]+kb[b]-d[a][b])
				c[b]=ka[a]+kb[b]-d[a][b],p[b]=y;
				if(c[b]<delta)
				delta=c[b],yy=b;
			}
		}
		for(int b=0;b<=n;b++)
		{
			if(visb[b])
			{
				ka[match[b]]-=delta,kb[b]+=delta;
			}
			else c[b]-=delta;
		}
		y=yy;
	}while(match[y]);
	while(y)match[y]=match[p[y]],y=p[y];
}
long long KM()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			visb[j]=0;
		}
		bfs(i);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=d[match[i]][i];
	}
	return ans;
}
int main()
{
//	freopen("escape.in","r",stdin);
//	freopen("escape.out","w",stdout);
	scanf("%d%d%d",&N,&M,&k);
	n=max(N,M);
	while(k--)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		d[y][x]=z;
	}
	printf("%lld\n",KM());
	for(int i=1;i<=N;i++)
	printf("%d ",(d[match[i]][i]==0)?0:match[i]);
	return 0;
}