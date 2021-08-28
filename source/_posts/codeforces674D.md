---
title: codeforces674D Bearish Fanpages
tags:
 - codeforces
 - 优先队列
---

#### 题目

>**Description**
>
>一个社交网站有$n$个网页，第ii个公司拥有第$i$个网页，每一个网页有一个父网页，不允许$i$网页是$j$网页的父网页且$j$网页是$i$网页的父网页，也不允许$i$网页是自己的父网页，对于$i$网页，设其父网页是$j0$网页，其子网页为$j1,j2,...,jk$，当用户浏览$i$网页时，他们会看到来自$k+2$家公司$i,j0,j1,...,jk$的广告，有$ti$个用户喜欢第$i$个网页，他们每个人都会点开一个广告看，对于$k+1$家公司$j0,j1,...,jk$，会有$\lfloor \frac{t_{i}}{k+2}\rfloor$个用户点开他们家的广告，对于剩下的$t_{i}-(k+1)\lfloor \frac{t_{i}}{k+2}\rfloor$个用户，他们会点开第$i$家公司的广告。一个公司的总收入等于看他们家广告的用户数量。现在给出第ii个网页的父网页$fi$，有$q$个操作，操作分三种： 
>
>$1 i j$:第$i$个网页的父网页变成$j$，保证之前第$i$个网页的父网页不是$j$。
>
>$2 i$:查询第$i$家公司的总收入
>
>$3$:输出这$n$家公司的最少收入和最多收入
>
><!--more-->
>
>**Input**
>
>第一行两整数$n$和$q$分别表示公司数量和操作数量，之后输入$n$个整数$t1,...,tn$表示喜欢第$i$个网页的用户数量，之后输入$n$个整数$f1,...,fn$表示第$i$个网页的父网页，最后$q$行每行一个操作$(3≤n≤10^5,1≤q≤10^5,1≤ti≤10^{12})
>
>**Output**
>
>对于查询操作，输出查询结果
>
>**Sample Input**
>
>5 12 
>10 20 30 40 50 
>2 3 4 5 2 
>2 1 
>2 2 
>2 3 
>2 4 
>2 5 
>1 4 2 
>2 1 
>2 2 
>2 3 
>2 4 
>2 5 
>3
>
>**Sample Output**
>
>10 
>36 
>28 
>40 
>36 
>9 
>57 
>27 
>28 
>29 
>9 57

#### 题解

​	不考虑3操作。

​	考虑把x的父亲修改，会影响的结果只有原来x的父亲，后来x的父亲，x，以及与原来x的父亲相邻的点，与后来x的父亲相邻的点。

​	考虑如果只是父亲或者父亲的父亲，我们可以直接修改，因为元素并不多。但是可能会存在儿子也要修改，这时候我们发现相当于是所有儿子的权值都减去某个值。

​	显然这东西我们可以直接在他这个点打标记，每次查询的时候加上它的父亲就是真正的权值。

​	考虑3操作。类似于ZJOI捉迷藏的点分治做法，我们对于每个点的儿子维护两个堆，再维护两个总的堆，每次修改的时候只需要把原来大堆中的元素删去，再加上这个堆的最值。

​	出与懒惰，堆我直接用set来代替了，注意可能有重复元素，所以不能只存一个权值。

```c++
#include<bits/stdc++.h>
#define int ll
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const ll inf = 1ll << 60;
#define Rep(i,a,b) for(register int i=(a);i<=int(b);++i)
#define Dep(i,a,b) for(register int i=(a);i>=int(b);--i)
#define rep(i,a,b) for(register int i=(a);i<int(b);++i)
#define mem(x,v) memset(x,v,sizeof(x))
#define pc putchar
#define gc getchar
#define fi first
#define se second
inline ll read(){
    register ll x=0,f=1;register char c=gc();
    for(;!isdigit(c);c=gc())if(c=='-')f=-1;
    for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
    return x*f;
}
#define rd read
void write(ll x){if(x<0)x=-x,pc('-');if(x>=10)write(x/10);putchar(x%10+'0');}
void writeln(ll x){write(x);puts("");}
const int maxn = 1e5+233;
int A[maxn],D[maxn],n,Q;
ll B[maxn],E[maxn],C[maxn],F[maxn];
set<pair<ll,int> > s[maxn],mn,mx;
void del(int x){
    ll w = F[A[x]];
    bool flag1=false,flag2=false;
    if(s[A[x]].begin() -> se == x){
	    mn . erase({s[A[x]].begin() -> fi + w,s[A[x]].begin() -> se});
	    flag1 = true;
	}
    if(s[A[x]].rbegin() -> se == x){
	    mx . erase({s[A[x]].rbegin() -> fi + w,s[A[x]].rbegin() -> se});
	    flag2 = true;
	}
    s[A[x]] . erase({C[x],x});
    if(s[A[x]].size()){
	    if(flag1) mn . insert({s[A[x]].begin() -> fi+w,s[A[x]].begin()->se});
	    if(flag2) mx . insert({s[A[x]].rbegin() -> fi+w,s[A[x]].rbegin()->se});
	}
}
void add(int x){
    ll w = F[A[x]];
    int flag1 = -1,flag2 = -1;
    if(s[A[x]].size()){
	    flag1 = s[A[x]] . begin() -> se;
	    flag2 = s[A[x]] . rbegin() -> se;
	}
    s[A[x]] . insert({C[x],x});
    if(flag1==-1){
	    mn . insert({s[A[x]].begin() -> fi+w,s[A[x]].begin()->se});
	    mx . insert({s[A[x]].rbegin() -> fi+w,s[A[x]].rbegin()->se});
	} else{
	    if(flag1 != s[A[x]] . begin() -> se){
		    mn . erase({C[flag1] + w,flag1});
		    mn . insert({s[A[x]].begin()->fi + w,s[A[x]].begin()->se});
		}
	    if(flag2 != s[A[x]] . rbegin() -> se){
		    mx . erase({C[flag2] + w,flag2});
		    mx . insert({s[A[x]].rbegin()->fi + w,s[A[x]].rbegin()->se});
		}
	}
}
void addF(int x,int det){
    int w = F[x];
    if(s[x].size()){
	    mn . erase({s[x].begin() -> fi + w,s[x].begin() -> se});
	    mx . erase({s[x].rbegin() -> fi + w,s[x].rbegin() -> se});
	    w += det;
	    mn . insert({s[x].begin()->fi + w,s[x].begin()->se});
	    mx . insert({s[x].rbegin()->fi + w,s[x].rbegin()->se});	   
	}
}
void solve1(int x,int y){
    ll det;
    int w = A[x];
    del(x),del(w),del(A[w]);
    C[x] += F[w],C[x] -= (B[w] / D[w]),C[w] -= (B[x] / D[x]);
    C[w] -= B[w] - D[w] * (B[w] / D[w]);
    C[w] += B[w] - (D[w]-1) * (B[w] / (D[w] - 1)); 
    det = (B[w] / (D[w]-1)) - (B[w] / D[w]);
    D[w]--,C[A[w]] += det,C[w] += det;
    addF(w,det),F[w] += det,add(w),add(A[w]);
    A[x] = y,w = y,del(w),del(A[w]); 
    C[w] -= B[w] - D[w] * (B[w] / D[w]);
    C[w] += B[w] - (D[w] + 1) * (B[w] / (D[w] + 1));
    det = (B[w] / (D[w] + 1)) - (B[w] / D[w]);
    D[w]++,C[A[w]] += det,C[w] += det,addF(w,det);
    F[w] += det,C[w] += B[x] / D[x],C[x] += B[w] / D[w];
    C[x] -= F[w],add(w),add(A[w]),add(x);
}
signed main(){
    n = rd(),Q = rd();
    Rep(i,1,n) B[i] = rd();
    Rep(i,1,n){
	    A[i] = rd();
	    D[A[i]]++;D[i]++;
	}
    Rep(i,1,n) D[i] = 0;Rep(i,1,n) D[A[i]]++,D[i]++,D[i]++;
    Rep(i,1,n) E[i] = B[i] / D[i]; Rep(i,1,n) C[i] = B[i] - D[i] * E[i];
    Rep(i,1,n) C[A[i]] += E[i],C[i] += E[A[i]],C[i] += E[i];
    Rep(i,1,n) s[A[i]] . insert({C[i],i});
    Rep(i,1,n){
	    if(s[i].size()){
		    mn . insert(*s[i].begin());
		    mx . insert(*s[i].rbegin());
		}
	}
    while(Q--){
	    int opt = rd();
	    if(opt == 1){
		    int x = rd(),y = rd();
		    solve1(x,y);
		} else
	    if(opt == 2){
		    int x = rd();
		    writeln(C[x] + F[A[x]]);
		} else
	    if(opt == 3){
		    write(mn.begin() -> fi);
		    pc(' ');
		    writeln(mx.rbegin() -> fi);
		}
	}
	 
    return 0;
}

```