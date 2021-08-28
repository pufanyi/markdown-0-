---
title: BZOJ1834 [ZJOI2010]network 网络扩容
tags:
 - BZOJ
 - 网络流
---

#### 题面

​	http://www.lydsy.com/JudgeOnline/problem.php?id=1834

#### 题解

​	相信网上的题解很多。

​	只要先跑最大流，再在残留网络上跑费用流就可以了。

贴一下我的代码（SPFA循环队列写成"<"调了好久）

​	用了$Dinic$ ，多路增广$SPFA$。

<!--more-->

```c++
//Hello Wolrd
//There is Special Pig Jiong in the world.
#include<cstdio>
#include<cstring> 
#include<cstdlib> 
#include<cctype>
#include<algorithm>
#include<bitset> 
#include<vector> 
#include<set> 
#include<map> 
#include<ctime> 
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
#define pc putchar
#define RG register
char __wzp[1<<15|1],*__S=__wzp+32768;
#ifdef LOCAL 
	#define gc() getchar()
#else
	#define gc() (__S>=__wzp+32768?(__wzp[fread(__wzp,sizeof(char),1<<15,stdin)]=EOF),*((__S=__wzp)++):*(__S++))
#endif
inline ll read(){
	RG ll x=0,f=1;RG char c=gc();
	for(;!isdigit(c);c=gc())if(c=='-')f=-1;
	for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
const int oo = 0x3f3f3f3f,inf = oo;
#define mem(x,v) memset(x,v,sizeof(x))
#define pb push_back
#define mp make_pair
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define file(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define writeln(x) printf("%d\n",x);
#define N 10005
#define M 40005+233
struct Edge{
	int to,nxt,cap,cost;
	Edge(){}
	Edge(int to,int nxt,int cap,int cost):to(to),nxt(nxt),cap(cap),cost(cost){}
}edge[M*2];
int first[N],nume,cur[N];
void Addedge(int a,int b,int c,int d){
//	printf("%d,%d,%d,%d\n",a,b,c,d);
	edge[nume] = Edge(b,first[a],c,d);first[a] = nume++;
	edge[nume] = Edge(a,first[b],0,-d);first[b] = nume++;
}
int n,m,k;

namespace Dinic{
	int q[N],dis[N];
	bool bfs(){
		int v,front,rear;mem(dis,-1);
		for(front=rear=0,dis[q[rear++]=n]=1;front<rear;)
			for (int u=q[front++],e=first[u];~e;e=edge[e].nxt)
				if(edge[e^1].cap && !~dis[v=edge[e].to])
                	dis[q[rear++]=v]=dis[u]+1;
		return dis[1]!=-1;
	}
	
	int dfs(int u,int flow){
		if(u==n)return flow;
		int used = 0,d,v;
		for (int &e=cur[u];~e;e=edge[e].nxt){
			if(edge[e].cap && dis[v=edge[e].to]==dis[u]-1 &&
               		(d = dfs(v,min(flow-used,edge[e].cap))))
				edge[e].cap -= d,edge[e^1].cap += d,used += d;
			if(used == flow) break;
		}
		if(!used)dis[u]=-1;
		return used;
	}
	
	int dinic(){
		int ans = 0;
		for(;bfs();ans+=dfs(1,inf))
			rep(i,1,n+1) cur[i] = first[i];
		return ans;
	}
}

void rebuild(){
	int t = nume;
	for (int i=0;i<t;i+=2){
		Addedge(edge[i^1].to,edge[i].to,k,edge[i].cost);
		edge[i].cost = edge[i^1].cost=0;
	}
	Addedge(0,1,k,0);
}
namespace Mcmf{
	bool inq[N];
	bool vis[N];
	int q[N],dis[N];
	int ans = 0;
	bool spfa(){
		int front,rear,u,v;
		mem(dis,0x3f);
		mem(inq,false);
		front=rear=0;
		dis[q[rear++]=n]=0;inq[n]=true;
		while(front!=rear){
			int u = q[front++];if(front==n+5)front=0;
			for (int e=first[u];~e;e=edge[e].nxt){
				int v = edge[e].to;
				if(edge[e^1].cap>0 && dis[u]+edge[e^1].cost < dis[v]){
					dis[v]=dis[u]+edge[e^1].cost;
					if(!inq[v]){
						q[rear++]=v;if(rear==n+5)rear=0;
						inq[v]=true;
					}
				}
			}
			inq[u]=false;
		}
		return dis[0]!=inf;
	}
	
	int dfs(int u,int flow){
		vis[u]=true;
		if(u==n)return flow;
		int used=0;
		for (int &e=cur[u];~e;e=edge[e].nxt){
			int v = edge[e].to;
			if(!vis[v] && edge[e].cap && dis[v]==dis[u]-edge[e].cost){
				int d=dfs(v,min(flow-used,edge[e].cap));
				edge[e].cap-=d;
				edge[e^1].cap+=d;
				used+=d;
				ans+=d*edge[e].cost;
			}
			if(used==flow)break;
		}
//		printf("USED = %d\n",used);
		return used;
	}
	
	int mcmf(){
		ans = 0;
		while(spfa()){
			for(int i=0;i<=n;i++)cur[i]=first[i];
			vis[n]=true;
			while(vis[n]){
				mem(vis,0);
				dfs(0,inf);
			}
		}
		return ans; 
	}
}

int main(){
	n=read(),m=read(),k=read();
	mem(first,-1);nume = 0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read(),c=read();
		Addedge(u,v,w,c);
	}
	printf("%d ",Dinic::dinic());
	rebuild();
	printf("%d\n",Mcmf::mcmf());
}
```

