---
title: HDU4685 Prince and Princess
tags: 
 - HDU
 - 二分图
 - 强连通缩点
---

#### 题意

​	有n个王子和m个公主，每个王子都会喜欢若干个公主，也就是王子只跟自己喜欢的公主结婚公主就比较悲惨， 跟谁结婚都行。

​	然后求对于每一个王子，可以和那个公主结婚，使得其余的匹配数不变。（输出所有可能的情况）

<!--more-->

#### 做法

​	第一步，对于这个二分图，我们求一遍最大匹配。比如这是样例：

![A](HDU4685 Prince and Princess\TIM截图20180107224255.png)

对于样例而言，1显然可以和5，2和6，3和7，4和8，因为这样是满足条件的，剩下的情况还是最大匹配。

当然，我们注意到1和6是可以连的，因为另一种可能的最大匹配是

![TIM截图20180107211419](HDU4685 Prince and Princess\TIM截图20180107211419.png)

这样的。——绿色的边。

​	那么什么情况下$i$可以和$j'$连呢？当且仅当对于$j'$

​	1、本来两个就是匹配。可以。

​	2、删除$j'$之后，j可以找到一条新的增广路（说明匹配数量可以不变）。

​			为什么是j？——因为增广路不可能从别的地方找。

​	而最后一步一定是空节点或者$i'$



考虑完美匹配的情况：

​	我们记得增广路是顺着未匹配边和匹配边找的。考虑对于匹配边建立反向边（正边依旧保留）。

​	我们对图进行强连通分量缩点。

​	那么如果对于节点$j'$和$i'$在同一个强连通分量里面。说明有环：

​	那么只需要把增广路轮换一下，匹配边和非匹配边交换一下，又可以形成新的一种匹配。



考虑没有完美匹配的情况：

​	对于未匹配的，我们制造一个假点，让它变成完美匹配。这些假点向其它所有边连边。

```c++
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector> 
using namespace std;
#define gc getchar
namespace IO{
	const int __buffsize = 1000000;char __buff[__buffsize];char *__buffS, *__buffT;
	char getch(){if (__buffS == __buffT){__buffT = (__buffS = __buff) + fread(__buff,1,__buffsize,stdin);if (__buffS == __buffT) return EOF;}return *__buffS++;}
	#define getch getchar
	int read(){int T = 0,f = 1;char c = getch();while ((c<'0'||c>'9')&&c!='-') c=getch();if(c=='-')f=-1,c=getch();while (c>='0'&&c<='9'){T=((T<<1)+(T<<3))+c-48;c=getch();}return T*f;}
	void write(int x){if(x < 0) putchar('0'),x = -x;if (x>=10) write(x / 10);putchar((x % 10)+'0');}
	void writeln(int x){write(x);puts("");}
};
#define N 2005
int n,m,k,BW,link[N],_link[N],vis[N];
using namespace IO;
int s[N],Instack[N],DFN[N],low[N],top,Belong[N];
struct Edge{
	int to,nxt;
	Edge(){}
	Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[N*N];
int first[N],nume;
void Addedge(int a,int b){
//	printf("%d->%d\n",a,b);
	edge[nume] = Edge(b,first[a]);
	first[a] = nume++;
}
int cnt,Time;
void Tarjan(int u){
	Instack[u] = true;
	s[++top] = u;
	DFN[u]=low[u]=++Time;
	for (int e=first[u];~e;e=edge[e].nxt){
		int v = edge[e].to;
		if (DFN[v] == -1){
			Tarjan(v);
			low[u] = min(low[u],low[v]);
		} else
		if (Instack[v])
			low[u] = min(low[u],low[v]);
	}
	if (DFN[u]==low[u]){
		cnt++;
		while(s[top]!= u){
			Belong[s[top]] = cnt;
			Instack[s[top]] = false;
			top--;
		}
		Belong[u] = cnt;
		Instack[s[top]] = false;
		top--;
	}
}

int find(int u){
	for (int e=first[u];~e;e=edge[e].nxt){
		int v = edge[e].to - BW;
		if (vis[v]) continue;
		vis[v] = true;
		if (link[v]==-1 || find(link[v])){
			link[v] = u;
			return true;
		}
	}
	return false;
}

int KM(int n){
	int res = 0;
	memset(link,-1,sizeof(link));
	for (int i=1;i<=n;i++){
		memset(vis,false,sizeof(vis));
		if (find(i)) res++;
	}
	return res;
}

int tmp[N];
void solve(int Case){
	n = read(),m = read();
	BW = n + m;
	memset(first,-1,sizeof(first));nume = 0;
	for (int i=1;i<=n;i++){
		int p = read();
		for (int j=1;j<=p;j++)
			Addedge(i,read() + BW);
	}
	k = KM(n);
//	printf("k = %d\n",k);
	for (int i=1;i<=m-k;i++)
		for (int j=1;j<=m;j++) Addedge(n+i,j+BW);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n-k;j++) Addedge(i,m+j+BW);
	int QQQ = KM(n+m-k);
	for (int i=1;i<=n+m-k;i++){
		Addedge(i+BW,link[i]);
	}
	memset(DFN,-1,sizeof(DFN));
	Time = 0,cnt = 0;
	for (int i=1;i<=n+m-k;i++){
		if (DFN[i] == -1) Tarjan(i);
		if (DFN[i+BW] == -1) Tarjan(i+BW);
	}
	printf("Case #%d:\n",Case);
	for (int i=1;i<=n;i++){
		tmp[0] = 0;
		for (int e = first[i];~e;e=edge[e].nxt){
			int v = edge[e].to;
			if (v - BW > m) continue;
			if (Belong[v] == Belong[i]) tmp[++tmp[0]] = v - BW;
		}
		sort(tmp+1,tmp+1+tmp[0]);
		write(tmp[0]);
		#define pc putchar
		for (int j=1;j<=tmp[0];j++) pc(' '),write(tmp[j]);
		pc('\n');
		#undef pc
	}
}

int main(){
	int T = read();
	for (int Case=1;Case<=T;Case++){
		solve(Case);
	}
	return 0;
}
```

