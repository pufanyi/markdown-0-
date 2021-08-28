---
title: BZOJ1050 [HAOI2006]旅行comf
tags:
 - BZOJ
 - 并查集
---

#### 题面

​	求S到T的路径最大边比最小边的最小值。——可以重复走呐

<!--more-->

#### 题解

​	排序之后，考虑暴力枚举最小边，最大边直接加进去，到S和T联通了，那么就update答案。

```c++
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
namespace IO{
	#define getch getchar
	int read(){int T = 0,f = 1;char c = getch();while ((c<'0'||c>'9')&&c!='-') c=getch();if(c=='-')f=-1,c=getch();while (c>='0'&&c<='9'){T=((T<<1)+(T<<3))+c-48;c=getch();}return T*f;}
	inline void write(int x){if(x < 0) putchar('0'),x = -x;if (x>=10) write(x / 10);putchar((x % 10)+'0');}
};
#define pc putchar
using namespace IO;
const int maxn = 505;
const int maxm = 5005;
struct Edge{
	int x,y,v;
	bool operator < (const Edge &a) const{
		return v < a.v;
	}
}edge[maxm];
int Max,Min,n,m,fa[maxn],rank[maxn];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void UNION(int x,int y){
	if (rank[x] > rank[y]) swap(x,y);
	fa[x] = y;
	if (rank[x]==rank[y]) rank[y]++;
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int s,t;
int main(){
	n = read(); m = read();
	for (int i=1;i<=m;i++)
		edge[i].x = read(),edge[i].y = read(),edge[i].v = read();
	s=read(),t=read();
	sort(edge+1,edge+1+m);
	Max = Min = -1;
	for (int i=1;i<=m;i++){
		for (int j=1;j<=n;j++) fa[j] = j;
		for (int j=i;j<=m;j++){
			int x = find(edge[j].x),y = find(edge[j].y);
			if (x==y) continue;
			UNION(x,y);
			if (find(s)==find(t)){
				if (Max==-1 || (double)edge[j].v / edge[i].v < (double)Max / Min){
					Max = edge[j].v;
					Min = edge[i].v;
				}
			}
		}
	}
	if (Max==-1) puts("IMPOSSIBLE"); else{
		int g = gcd(Max,Min);
		if (Min == g) write(Max/g); else
			write(Max / g),pc('/'),write(Min / g);
	}
	return 0;
}
```

