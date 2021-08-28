---
title: hihoCoder1252 Kejin Game
tags: 
 - hihoCoder
 - 网络流
---

#### 题意

​	有一颗技能树，每个技能有一些“先修技能”，必须把这些“先修技能”全部点完才能学习这个技能，这个技能树是个DAG。由于是个氪金游戏，点某个技能需要一些花费，作为rmb玩家，可以把技能树的某条边去掉，也就是说某个技能少了一个先修技能，当然这也需要花费。还可以直接花费金钱学习某个技能而无视其先修技能。 
问：在初始什么技能都没有的情况下，要点某个给定的技能需要多少钱？

<!--more-->

#### 题解

​	用最小割的思想来做。

​	考虑重新构图，把每个点拆成两个点$i$和$i'$，对于直接学习某个技能，我们在$i$到$i'$之间连一条容量为其花费的边。这样只要割去这条边，左边和右边直接断开。

​	我们从源点S向每个点连一条容量为普通学习费用的边。

​	并且我们对于原来的一条边(u->v)，我们从$u'$连到$v$这样一条容量为消灭这条边的费用的边。

​	最后我们从要求的$s'$向T连一条$inf$的边。

​	注意到这里的每一条割都意味着一种学习方法。

​	由于没有从S直接连到$i'$的边，意味着到$i'$，也就是修i的技能，只有前面都断了，那么前面断了可以是这个点直接学习，也可以是之前的边满足都割去，然后再割去S到$i$的普通学习的边。

​	那么只要求最小割（最大流），就可以得到花费最小的学习方法了。

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
#define wait system("pause")
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define file(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define writeln(x) printf("%d\n",x);
#define N 505*2+233
#define M 100990 + N * 2 + 1
#define S 0
#define T n+n+1
struct Edge{
	int to,nxt,cap;
	Edge(){}
	Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
}edge[M*2];
int first[N],nume,cur[N];
void Addedge(int a,int b,int c){
	edge[nume] = Edge(b,first[a],c);first[a] = nume++;
	edge[nume] = Edge(a,first[b],0);first[b] = nume++;
}
int q[N],dis[N],n;
bool bfs(){
	int v,front,rear;mem(dis,-1);
	for(front=rear=0,dis[q[rear++]=T]=1;front<rear;)
		for (int u=q[front++],e=first[u];~e;e=edge[e].nxt)
			if(edge[e^1].cap && !~dis[v=edge[e].to])dis[q[rear++]=v]=dis[u]+1;
	return dis[S]!=-1;
}

int dfs(int u,int flow){
	if(u==T)return flow;
	int used = 0,d,v;
	for (int &e=cur[u];~e;e=edge[e].nxt){
		if(edge[e].cap && dis[v=edge[e].to]==dis[u]-1 && (d = dfs(v,min(flow-used,edge[e].cap))))
			edge[e].cap -= d,edge[e^1].cap += d,used += d;
		if(used == flow) break;
	}
	if(!used)dis[u]=-1;
	return used;
}

int dinic(){
	int ans = 0;
	for(;bfs();ans+=dfs(S,inf))
		rep(i,S,T+1) cur[i] = first[i];
	return ans;
}

int m,s;
int main(){
	int kase = read();
	while(kase--){
		mem(first,-1);nume = 0;
		n = read(),m = read(),s = read();
		while(m--){
			int a = read(),b = read(),c = read();
			Addedge(a+n,b,c);//氪一条边 
		}
		for (int i=1;i<=n;i++){
			int x = read();
			Addedge(S,i,x);
		}
		for (int i=1;i<=n;i++){
			int x = read();
			Addedge(i,n+i,x);
		}
		Addedge(s+n,T,inf);
		printf("%d\n",dinic());
	}
	return 0;
}
```

