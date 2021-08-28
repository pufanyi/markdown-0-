---
title: BZOJ3438 小M的作物
tags:
 - BZOJ
 - 网络流
---

#### 题面

​	http://www.lydsy.com/JudgeOnline/problem.php?id=3438

<!--more-->

#### 题解

​	先贴一个**错误**的做法，也是我一开始想到的做法。

```
假设与S相连表示在A集合，与T相连表示在B集 
一开始得到所有点的贡献(sum)
S向所有作物连一条容量为Ai的边
所有作物向T连一条容量为Bi的边
PS：在不考虑组合的情况下，sum-最小割已经是答案了。
对于一种组合X
S向X连一条容量为c1的边，X向T连一条容量为C2的边
对于X相关的所有作物，互相连一条容量为inf的边
对于所有组合，只有某一边全部被割去才能计算，所以也可以得到结果。
这样就满足了组合的需求。
```

​	但是事实上，我们无意间强制要求两个本不不相干的点在同一个割集了。

数据：

```
2
1 7 
9 2 
1
2 5 2 1 2
```

![反例](BZOJ3438 小M的作物\反例.png)	注意红色的边，它的边权是$inf$，那么强制X和Y在同一个割集了。

​	所以要改变思路，不能用一个组合

​	我们可以把组合拆成两个点，S向组合1连一条c1的边，组合1向对应种子连边(inf)，对应种子向组合2连边(inf)，组合2向点T连边。

​	这样就不会导致强制同一个割集了。

```c++
//Hello Wolrd
//There is Special Pig Jiong in the world.
#include<cstdio>
#include<cstring> 
#include<cstdlib> 
#include<algorithm>
#include<bitset> 
using namespace std;
#define gc getchar
#define pc putchar
inline int read(){int x=0,f=1;char c=gc();for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;for(;c>='0'&&c<='9';c=gc())x=x*10+c-48;return x*f;}
inline void write(int x){if(x < 0) putchar('-'),x = -x;if (x>=10) write(x / 10);putchar((x % 10)+'0');}
inline void writeln(int x){write(x);puts("");}
const int oo = 0x3f3f3f3f;const int inf = oo;
#define mem(x,v) memset(x,v,sizeof(x))
typedef unsigned long long ull;
typedef long long ll;
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define file(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define N 3005
#define M 1009*1009*2+1005+1005
#define S 0
#define T n+2*m+1
struct Edge{
	int to,nxt,cap;
	Edge() {}
	Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
}edge[M*2];
int first[N],cur[N],q[N],dis[N],nume,n,m;
void Addedge(int a,int b,int c,int d = 0){
//	printf("%d->%d:%d\n",a,b,c);
	edge[nume] = Edge(b,first[a],c);first[a] = nume++;
	edge[nume] = Edge(a,first[b],d);first[b] = nume++;
}
int front,rear;
bool bfs(){
	mem(dis,-1);
	front = rear = 0;
	q[rear++] = T;
	dis[T] = 0;
	while(front<rear){
		int u = q[front++];
		for (int e=first[u];~e;e=edge[e].nxt){
			int v = edge[e].to;
			if (edge[e^1].cap && dis[v]==-1)
				dis[v] = dis[u] + 1,q[rear++] = v;
		}
	}
	return dis[S]!=-1;
}
int dfs(int u,int flow){
	if(u==T)return flow;
	int used = 0,d;
	for (int &e=cur[u];~e;e=edge[e].nxt){
		int v = edge[e].to;
		if(edge[e].cap && dis[v]==dis[u]-1 && (d = dfs(v,min(flow-used,edge[e].cap))))
			edge[e].cap-=d,edge[e^1].cap += d,used+=d;
		if (used == flow) break;
	}
	return used;
}
int dinic(){
	int ans = 0,flow;
	while(bfs()){
		rep(i,S,T+1) cur[i]=first[i];
		while(flow=dfs(S,inf))ans+=flow;
	}
	return ans;
}
int a[1005],b[1005],ans;
int main(){
	freopen("1.in","r",stdin);
	freopen("AC.out","w",stdout); 
	ans = 0;
	n = read();
	rep(i,0,n)a[i]=read(),ans+=a[i];
	rep(i,0,n)b[i]=read(),ans+=b[i];
	m = read();
	mem(first,-1);nume = 0;
	rep(i,0,n)Addedge(S,i+1,a[i]);
	rep(i,0,n)Addedge(i+1,T,b[i]);
	rep(i,1,m+1){
		int k = read();
		int c1=read(),c2=read();
		ans+=c1+c2;
		Addedge(S,n+i*2,c1);
		Addedge(n+i*2-1,T,c2);
		while(k--){
			int x = read();
			Addedge(x,n+i*2-1,inf);
			Addedge(n+i*2,x,inf);
		}
	}
	writeln(ans - dinic());
}
```

