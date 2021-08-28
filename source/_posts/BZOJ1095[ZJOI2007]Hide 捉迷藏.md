---
title: BZOJ1095[ZJOI2007]Hide 捉迷藏
tags:
 - 线段树
 - 贪心
 - BZOJ
 - 树
---

#### 题面

​	http://www.lydsy.com/JudgeOnline/problem.php?id=1095

<!--more-->

#### 题意

​	有黑色和白色两种颜色。

​	给你一棵树，一开始全部是黑色，每次可以把一个点变成相反的颜色，或者询问树上最远的两个黑色点对。

#### 无关扯淡

​	这题做法好像很多。网上能找到的最多的有动态点分治和括号序列的做法。

​	然而：我括号序列看了好久都没看懂（大概半年前？）。

​	动态点分治抄HZWER代码简直一摸一样了还是WA(40ms)（大概几个月前？）

​	然后听说了周YY的好些好理解的做法。

​	真适合我这种智商欠缺码力不足的蒟蒻。

​	顺便奶一口周YY要AK_ZJOI，旺仔怒进省队。

#### 题解

​	~~容易~~发现是求类似于~~虚树的~~直径。

​	如果我们已经求出只考虑端点为L~mid的直径（La和Lb)，以及mid+1~R的直径（Ra和Rb)，考虑如何得到L~R。

​	类比一般图求直径的那个两遍BFS的思想，~~显然~~只考虑端点在L~R的直径的两个端点必然在(La,Lb,Ra,Rb)中选出。

​	那么令单独一个点x的直径的为(x,0)，依次更新非0的答案，最终算到(1~R)就是答案。用上线段树可以支持在线修改。

PS：以下树剖两只log，可以用RMQ求树上距离使得变成一只log

```c++
//Hello Wolrd
//WZP will AK ZJOI 
#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<cstdlib>
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
const int inf = 0x3f3f3f3f,oo = inf;
#define pc putchar
#define RG register
#ifdef LOCAL
char __wzp[1<<15|1],*__S=__wzp+32768;
#define gc() (__S>=__wzp+32768?(__wzp[fread(__wzp,sizeof(char),1<<15,stdin)]=EOF),*((__S=__wzp)++):*(__S++))
#else
#define gc getchar
#endif
inline ll read(){
    RG ll x=0,f=1;RG char c=gc();
    for(;!isdigit(c);c=gc())if(c=='-')f=-1;
    for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
    return x*f;
}
void write(ll x){
    if(x<0)x=-x,pc('-');
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}
#define rd read
#define mem(x,v) memset(x,v,sizeof(x))
#define pb push_back
#define mp make_pair
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define Rep(i,a,b) for(RG int i=(a);i<=(b);++i)
#define Down(i,a,b) for(RG int i=(a);i>=(b);--i)
#define fin(x) {freopen(#x".in","r",stdin);}
#define fout(x) {freopen(#x".in","r",stdin);}
#define y1 ________y1
#define union Union
const int maxn = 100005;
struct Edge{int to,nxt;}edge[maxn*2];
int nume,first[maxn];
int deep[maxn],size[maxn],son[maxn],fa[maxn],top[maxn];//pos[maxn];
int n,m;
void Addedge(int a,int b){
    edge[nume] . to = b;edge[nume] . nxt = first[a];
    first[a] = nume++;
    edge[nume] . to = a;edge[nume] . nxt = first[b];
    first[b] = nume++;
}
 
void dfs(int u){
    size[u] = 1;
    son[u] = 0;
    for (int e=first[u];~e;e=edge[e].nxt){
        int v = edge[e].to;
        if (v==fa[u]) continue;
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dfs(v);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
  
int dfsclk;
void divide(int u,int chain){
    top[u] = chain;
//  pos[u] = ++dfsclk;
    if (son[u]==0) return ;
    divide(son[u],chain);
    for (int e=first[u];~e;e=edge[e].nxt)
        if (deep[edge[e].to] == deep[u] + 1 && edge[e].to != son[u])
            divide(edge[e].to,edge[e].to);
}
 
int LCA(int x,int y){
    while(top[x]!=top[y]){
//      printf("%d %d\n",x,y);
        if(deep[top[x]] > deep[top[y]])
            x = fa[top[x]];
        else
            y = fa[top[y]];
    }
    return deep[x] > deep[y] ? y : x;
}
 
int dist(int a,int b){
    if(a==0||b==0) return 0;
    return deep[a] + deep[b] - 2 * deep[LCA(a,b)];
}
#define mid ((l+r) >> 1)
#define lson (o << 1)
#define rson (o << 1 | 1)
struct Node{
    int a,b;
    Node(){}
    Node(int x,int y){a = x,b = y;}
}T[maxn<<2];
void update(Node &x,Node y){
    if(x.a==0) x=y; else
    if(dist(x.a,x.b) < dist(y.a,y.b)){
        x.a = y.a;
        x.b = y.b;
    }
}
void pushup(int o){
    T[o] = T[lson];update(T[o],T[rson]);
    update(T[o],Node(T[lson].a,T[rson].a));
    update(T[o],Node(T[lson].a,T[rson].b));
    update(T[o],Node(T[lson].b,T[rson].a));
    update(T[o],Node(T[lson].b,T[rson].b));
}
int TOT;
void change(int o,int l,int r,int x){
    if(l==r){
        T[o].a = x - T[o].a;
        if(T[o].a != 0) TOT++; else TOT--;
        T[o].b = 0;
        return ;
    }
    if(x<=mid)   change(lson,l,mid,x); else
                change(rson,mid+1,r,x);
    pushup(o);
}
int color[maxn];
int main(){
    mem(first,-1);nume = 0;
    n = rd();
    Rep(i,1,n-1) Addedge(rd(),rd());
    deep[0]=0;dfsclk=0;
    dfs(1);
    divide(1,1);
    TOT = 0;
    Rep(i,1,n){
        change(1,1,n,i);
    }
    m = rd();
    Rep(i,1,m){
        char op = gc();
        while(op!='G'&&op!='C') op=gc();
        if(op=='G'){
            if(TOT == 0) puts("-1"); else
            if(TOT == 1) puts("0"); else
            printf("%d\n",dist(T[1].a,T[1].b));
        } else{
            int x = rd();
            change(1,1,n,x);
        }
    }
    return 0;
}
```

