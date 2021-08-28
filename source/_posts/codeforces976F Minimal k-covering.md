---
title: codeforces976F Minimal k-covering
tags:
 - codeforces
 - 网络流
---

[原题戳这里](http://codeforces.com/contest/976/problem/F)

#### 题面

>给你一个二分图，然后定义k最小覆盖为选择一些边，使得每个点的度数大于等于k，使得选的边最小，对于所有k∈[0,mindegree]，求出最小k覆盖的那些边（任意输出一组）

#### 吐槽

​	比赛时候想到一个`上下界最小流`的做法，然后码了一个小时没码出来，又不会做D，导致只做出4题，rank7。

<!--more-->

#### 题解

​	考虑倒着做，一个点如果要求度数大于等于K,而现在它的度数为A，那么说明有A-K个度数是多余的，可以任意分配。

​	然后我们本质上相当于要让所有可以任意分配的度数尽可能不分配，这就相当于是一个减少最多的，可以直接用最大流来做。

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
const int inf = 0x3f3f3f3f,oo = inf;
#define IL inline
#define RG register
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define Rep(i,a,b) for(RG int i=(a);i<=(b);++i)
#define Dep(i,a,b) for(RG int i=(a);i>=(b);--i)
#define pc putchar
#define gc getchar
IL ll read(){
    RG ll x=0;char f=0;RG char c=gc();
    for(;!isdigit(c);c=gc())f|=(c=='-');
    for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
    return f?-x:x;
}
IL double readdb(){
    RG double x=0,p=0.1;RG char f=0,c=gc();
    for(;!isdigit(c);c=gc())f|=(c=='-');
    for(;isdigit(c);c=gc())x=x*10+(c^48);
    if(c=='.')for(c=gc();isdigit(c);c=gc(),p/=10)x=x+(c^48)*p;
    return f?-x:x;
}
IL void write(ll x){if(x<0)x=-x,pc('-');if(x>=10)write(x/10);pc(x%10+'0');}
IL void writeln(ll x){write(x);puts("");}
IL void writeln(ll x,char c,ll y){write(x);pc(c);writeln(y);}
IL void writeln(ll x,char c,ll y,char d,ll z){write(x);pc(c);write(y);pc(d);writeln(z);}
#define rd() read()
#define mem(x,v) memset(x,v,sizeof(x))
const int maxn = 4333;
const int maxm = 23333;
struct Edge{
    int to,nxt,cap;
    Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
    Edge(){}
}edge[maxm*2+maxn*2];
int first[maxn],nume;
int S,T;
int low[maxm],in[maxn];
void Addedge(int a,int b,int cap){
    edge[nume] = Edge(b,first[a],cap);first[a] = nume++;
    edge[nume] = Edge(a,first[b],0);first[b] = nume++;
}
int dis[maxn],q[maxn],cur[maxn];
int front,rear;
bool bfs(){
    front=rear=0;
    Rep(i,S,T) dis[i]=-1;
    q[rear++]=S;dis[S]=0;
    while(front<rear){
        int u = q[front++];
        for(int e=first[u];~e;e=edge[e].nxt){
            int v = edge[e].to;
            if(edge[e].cap && dis[v] == -1)
                dis[q[rear++] = v] = dis[u] + 1;
        }
    }
    return dis[T] != -1;
}
int dfs(int u,int flow){
    int used = 0,v,d;
    if(u==T) return flow;
    for(int &e=cur[u];~e;e=edge[e].nxt){
        int v = edge[e].to;
        if(edge[e].cap && dis[v]==dis[u]+1 && (d=dfs(v,min(edge[e].cap,flow-used))))
            edge[e].cap-=d,edge[e^1].cap+=d,used+=d;
        if(used==flow) break;
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
vector<int> ans[4005];
int n1,n2,m,deg[4005],mindegree;
int main(){
    n1 = rd(),n2 = rd(),m = rd();
    S = 0;
    T = n1 + n2 + 1;
    mem(first,-1);nume = 0;
    Rep(i,1,m){
        int a = rd(),b = rd();
        Addedge(a,n1+b,1);
        deg[a]++;
        deg[n1+b]++;
    }
    mindegree = inf;
    Rep(i,1,n1+n2) mindegree = min(mindegree,deg[i]);
    int tmp = nume;
    Rep(i,1,n1) Addedge(S,i,deg[i] - mindegree);
    Rep(i,n1+1,n1+n2) Addedge(i,T,deg[i] - mindegree);
    Dep(k,mindegree,0){
        m -= dinic();
        ans[k].push_back(m);
        for(int i=0;i<tmp;i+=2){
            if(edge[i].cap == 1){
                ans[k] . push_back((i>>1)+1);
            }
        }
        for(int i=tmp;i<nume;i+=2){edge[i].cap++;}
    }
    Rep(i,0,mindegree){
        for(auto v : ans[i]){
            printf("%d ",v);
        }puts("");
    }
    return 0;
}

```



