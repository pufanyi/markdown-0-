---
title: BZOJ1937 [Shoi2004]Mst 最小生成树
tags:
 - BZOJ
 - 二分图
 - 树
---

#### 题面

​	http://www.lydsy.com/JudgeOnline/problem.php?id=1497

<!--more-->

#### 题解

​	注意到树边只会减少，而非树边只会增加。

​	对于每一条非树边，我们可以找出与它有关的树边，也就是它的两端在那个生成树上路径的所有边，那么这些边的边权必须都小于等于这条边的边权——这个可以暴力跳father得到。

> 对于一条非树边$j$连接着两个点$x$、$y$，则对于$xy$这条路径上的所有树边$i$，都要满足：$wi−di≤wj+dj$移项可得$wi−wj≤di+dj$

​	然后我们注意到KM算法的顶标就是求最小的顶标和，使得一条边两端的顶标大于等于这条边的边权。

​	那么这题可以用KM的思想去做。

```c++
//省略一堆头文件
#define N 819
#define M 819

int n,nm,m;

int map[N][N],pa[M],pb[M],pc[M],len[M];
struct Edge{
	int to,nxt,val;
}edge[N*2];
int first[N],nume;
int fa[N],deep[N],Belong[N];
void dfs(int u){
	link(e,u){
		int v = edge[e].to;
		if(v == fa[u]) continue;
		fa[v]=u;
		deep[v]=deep[u]+1;
		Belong[v]=edge[e].val;
		dfs(v);
	}
}


int Link[M],slack[M];
int lx[N],ly[M],A[M][M],vx[N],vy[M];

void build(int a,int b,int c){
	if(deep[a]<deep[b])swap(a,b);
	while(deep[a]>deep[b]) A[Belong[a]][nm]=max(0,len[Belong[a]]-c),a=fa[a];
	while(a!=b)A[Belong[a]][nm]=max(0,len[Belong[a]]-c),A[Belong[b]][nm]=max(0,len[Belong[b]]-c),a=fa[a],b=fa[b];
}

int find(int u){
	vx[u]=true;
	rep(v,0,nm){
		if(vy[v]) continue;
		int tmp = lx[u]+ly[v]-A[u][v];
		if(tmp==0){
			vy[v]=true;
			if(Link[v]==-1||find(Link[v])){
				Link[v]=u;
				return true;
			}
		}else slack[v]=min(slack[v],tmp);
	}
	return false;
}

void Addedge(int a,int b,int c){
	edge[nume] . to = b;
	edge[nume] . nxt = first[a];
	edge[nume] . val = c;
	first[a] = nume++;
}

int main(){
	n =read(),m = read();
	int i,j,k,a,b;
	rep(i,0,m){
		pa[i]=read()-1,pb[i]=read()-1;pc[i]=read();
		map[pa[i]][pb[i]]=map[pb[i]][pa[i]]=i+1;
	}
	mem(first,-1);nume = 0;
	rep(i,0,n-1){
		a = read()-1,b=read()-1;
		Addedge(a,b,i);
		Addedge(b,a,i);
		len[i]=pc[map[a][b]-1];
		map[a][b]=map[b][a]=0;
	}
	deep[0]=0;dfs(0);
	nm = 0;
	rep(i,0,m)
	if (map[pa[i]][pb[i]]){
		build(pa[i],pb[i],pc[i]);
		nm++;
	}
	if(n>nm){
		rep(i,0,n)rep(j,0,nm)if(i>j)swap(A[i][j],A[j][i]);
		swap(n,nm);
	}
	mem(Link,-1),mem(lx,0xc0),mem(ly,0);
	rep(i,0,n)rep(j,0,nm)lx[i]=max(lx[i],A[i][j]);
	rep(i,0,n){
		mem(slack,0x3f);
		for(;;){
			mem(vx,0),mem(vy,0);
			if(find(i))break;
			int low=inf;
			rep(j,0,nm)if(!vy[j])low=min(low,slack[j]);
			rep(j,0,n)if(vx[j])lx[j]-=low;
			rep(j,0,nm)if(vy[j])ly[j]+=low;else slack[j]-=low;
		}
	}
	int ans = 0;
	rep(i,0,n)ans+=lx[i];
	rep(i,0,nm)ans+=ly[i];
    writeln(ans);
    return 0;
}
```

