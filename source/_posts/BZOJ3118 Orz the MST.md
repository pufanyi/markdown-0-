---
title: BZOJ3118 Orz the MST
tags:
 - BZOJ
 - 整体二分
 - 树
 - 分治
 - 网络流
---

[原题戳这里](https://www.lydsy.com/JudgeOnline/problem.php?id=3118)

#### 题意

> 给你一个图，你可以把一条边边权加或者减若干次，有一定的代价。
>
> 问使得其中一些边成为最小生成树之一最小代价是多少。

#### 吐槽

​	第一眼以为是BZOJ1937，爆蛋。网上一搜题解全是单纯形法。省选一试0分的菜鸡OI选手怎么可能会单纯形法？然后用了一个从新疆`shaoxing`第一女选手`共产主义接班人`何`hu`梓`zhao`莹`yang`里学到的一个有理有据的多项式做法。

<!--more-->

#### 题解

首先，问题可以转化为这样一个问题。

一开始有n个数字$A[i]$

让你求一个数组B。

其中有一些限制$B[i] >= B[j]$——然后这个限制大概是一个二分图？？并不知道有什么卵用。

最小化

$$
\large \sum_{i=0}^{n}
\begin{cases}
	(B[i]-A[i]) \times C1[i], & \text{if A[i]<=B[i]}\\
	(A[i]-B[i]) \times C2[i],& \text{if A[i]>B[i]}
\end{cases}
$$
其中C1,C2是给出的数组，分别表示增加1的代价和减少1的代价。



这东西就可以单纯形法了（以后可能会填坑）

然后由于这题优秀的性质，可以用`整体二分`+`最大权闭合子图`

时间复杂度$O(log_2{(maxV)} \times O(\text{网络流}) )$

对B数组进行整体二分。

现在的问题是如何判断哪些点的B值**大于**mid。

把**大于**mid的点的权值设置为$B[i]$，**小于等于**的设置为$-A[i]$

对于$x$大于等于$y$的，连一条$y$到$x$的边。

跑一遍最大权闭合子图。

那么在最大权闭合子图中的点，一定是**大于**mid的。

#### 补充

请允许我**口胡**一下证明：

​	首先，最大权闭合子图是一张闭合子图，也就是如果存在$i$,$j$，满足$i$能够直接或者间接连向$j$（这说明$j$不能小于$i$），那么如果$i$在这个闭合子图中，$j$也一定在，也就是如果$i$大于$mid$，$j$也一定大于$mid$，这是能够满足大于等于那个限制的。

​	然后，这张子图的权值一定是大于等于0的。

​	也就是如果我这个图中的点我要让他所有点的值都减少1，如果原来权值就**小于等于**$mid$，如果它从$mid+1$开始减少，那么减少的时候代价最多减少$A[i]$的代价（也可能不到），也就是得到$-A[i]$，如果它的权值是**大于**$mid$的，那么它从$mid+1$开始减少，他每次减少会使得代价增加$B[i]$，也就是$+B[i]$。所以这个子图中的点如果从mid开始减少，每次会增加的代价至少是
$$
\sum _{U\text{∈最大权闭合子图}}
\begin{cases}
	A[u] &&& W[u]>mid \\
	-B[u] &&& W[u]<=mid
\end{cases}
$$
​	假设这张闭合子图($S$)中存在一个子图为闭合子图($T$)，那么显然$S-T$也是闭合子图。所以如果T可以成为小于mid的，那么T的权值小于0，那么T显然是可以不选的，因为$S-T$也是合法的，而且它的权比$T$大

​	所以可以得到，那些在最大权闭合子图中的点，一定是**大于**$mid$的。

#### 代码

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f,oo = inf;
#define IL inline
#define RG register
#define rep(i,a,b) for(RG int i=(a);i<int(b);++i)
#define Rep(i,a,b) for(RG int i=(a);i<=(b);++i)
#define pc putchar
#define gc getchar
IL ll read(){
    RG ll x=0;char f=0;RG char c=gc();
    for(;!isdigit(c);c=gc())f|=(c=='-');
    for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
    return f?-x:x;
}
IL void write(ll x){if(x<0)x=-x,pc('-');if(x>=10)write(x/10);pc(x%10+'0');}
IL void writeln(ll x){write(x);puts("");}
#define rd() read()
#define mem(x,v) memset(x,v,sizeof(x))
const int maxn = 305;
const int maxm = 1002;
namespace flow{
    struct Edge{
        int to,nxt,cap;
        Edge(){}
        Edge(int to,int nxt,int cap):
            to(to),nxt(nxt),cap(cap){}
    }edge[maxm * maxn * 4 * 2]; 
    int first[maxm],cur[maxm],nume,S,T; 
    void Addedge(int a,int b,int c){
        edge[nume] = Edge(b,first[a],c);first[a] = nume++;
        edge[nume] = Edge(a,first[b],0);first[b] = nume++;
    }
    void init(int SS,int TT){
        S = SS,T = TT; 
        Rep(i,S,T) first[i] = -1;
    }
    int front,rear,q[maxm],dist[maxm];
    bool bfs(){
        Rep(i,S,T) dist[i] = -1;
        front = rear = 0;
        dist[S] = 0;
        q[rear++] = S;
        while(front < rear){
            int u = q[front++];
            for(int e=first[u];~e;e=edge[e].nxt){
                int v = edge[e].to;
                if(edge[e].cap && dist[v]==-1){
                    dist[v] = dist[u] + 1;
                    q[rear++] = v;
                }
            }
        }
        return dist[T] != -1;
    }
    int dfs(int u,int flow){
        if (u == T) return flow;
        int used = 0,v,d;
        for(int &e=cur[u];~e;e=edge[e].nxt){
            int v = edge[e].to;
            if(edge[e].cap && (dist[v]==dist[u]+1) && (d = dfs(v,min(edge[e].cap,flow - used)))){
                edge[e].cap -= d;
                edge[e^1].cap += d;
                used += d;
            }
            if(used == flow) break;
        }
        return used;
    }
    int dinic(){
        int ans = 0;
        while(bfs()){
            Rep(i,S,T) cur[i] = first[i];
            ans += dfs(S,inf);
        }
        return ans;
    }
}
struct Edge{
    int to,nxt;
    Edge(){}
    Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[maxm * 2];
int first[maxm],nume;
int deep[maxn],pre[maxn];
bool E[maxm][maxm];
int X[maxm],Y[maxm],W[maxm],A[maxm],B[maxm],FF[maxm]; 
int cur[maxm];
void Addedge(int a,int b){
    edge[nume] = Edge(b,first[a]);
    first[a] = nume++;
}
void doit(int u,int fa){
    deep[u] = deep[edge[fa].to] + 1;
    pre[u] = fa;
    for(int e=first[u];~e;e=edge[e].nxt){
        if(e!=fa && FF[e/2+1])
            doit(edge[e].to,e^1);
    }
}
ll ans = 0;
int tmp[maxm];
int n,m;
void solve(int L,int R,int l,int r){
    if(l>r)return;
    if(l == r){
        if(W[cur[l]] < L) ans += (L - W[cur[l]]) * A[cur[l]]; else
        if(W[cur[l]] > R) ans += (W[cur[l]] - R) * B[cur[l]];
        return ;
    }
    if(L == R){
        Rep(i,l,r)
            if(W[cur[i]] < L) ans += (L - W[cur[i]]) * A[cur[i]];
            			 else ans += (W[cur[i]] - L) * B[cur[i]];
        return ;
    }
    flow::init(0,r-l+2);
    int mid = (L + R) >> 1;
    Rep(i,l,r){
        if(W[cur[i]] > mid) flow::Addedge(flow::S,i-l+1,B[cur[i]]);
        			   else flow::Addedge(i-l+1,flow::T,A[cur[i]]);
    }
    Rep(i,l,r)
        Rep(j,l,r)
            if(E[cur[i]][cur[j]])
                flow::Addedge(j-l+1,i-l+1,inf);
    flow::dinic();
    int j = l,k = r;
    Rep(i,l,r){
        if(flow::dist[i-l+1] != -1) tmp[j++] = cur[i];
        else tmp[k--] = cur[i];
    }
    Rep(i,l,r) cur[i] = tmp[i];
    solve(L,mid,j,r),solve(mid+1,R,l,k);
}
int main(){
    mem(first,-1);nume = 0;
    n = rd() ,m = rd();
    Rep(i,1,m){
        X[i] = rd(),Y[i] = rd(),W[i] = rd();
        FF[i] = rd();
        A[i] = rd(),B[i] = rd();
        Addedge(X[i],Y[i]);
        Addedge(Y[i],X[i]);
    }
    doit(1,-1);
    Rep(i,1,m){
        if(!FF[i]){
            int x = X[i],y = Y[i];
            while(x!=y){
                if(deep[x] < deep[y]) swap(x,y);
                E[i][pre[x]/2+1] = 1;
                x = edge[pre[x]] . to;
            }
        }
    }
    Rep(i,1,m) cur[i] = i;
    solve(1,inf,1,m);
    writeln(ans);
}
```





​	