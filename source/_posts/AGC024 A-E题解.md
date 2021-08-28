---
title: AGC024 A-E题解
tags:
 - atcoder
 - 树
 - 贪心
---

[比赛链接](https://agc024.contest.atcoder.jp)

A题想太慢，B题看错题目，被C题续了好久，D题看错范围，不会做E题，天天被wzp吊打。

<!--more-->

### [A - Fairness](https://agc024.contest.atcoder.jp/tasks/agc024_a) 

应该还是比较simple的。

```c++
ll a,b,c,k;
int main(){
	a=rd(),b=rd(),c=rd(),k=rd();
	writeln(!(k&1)?(a-b):(b-a));
	return 0;
}
```



### [B - Backfront](https://agc024.contest.atcoder.jp/tasks/agc024_b) 

​	显然是一段前缀和一段后缀被使用，相当于用n减去最长的连续的一段，比如说

`43125`里面最长的连续一段是`12`，或者`45`,`35`，而`41253`里面最长的连续的一段是`123`

```C++
int a[200005],pos[200005],ans = 0,n;
int f[200005];
int main(){
	n = rd();
	Rep(i,1,n) a[i] = rd(),pos[a[i]]=i;
	int x = n-1;
	f[1] = 1;
	Rep(i,2,n){
		if(pos[i] > pos[i-1]) f[i] = f[i-1] + 1; else f[i] = 1;
		x = min(x,n-f[i]);
	}
	writeln(x);
	return 0;
}
```



### [C - Sequence Growing Easy](https://agc024.contest.atcoder.jp/tasks/agc024_c) 

有一个显然的贪心，就是如果连续的直接加上去，否则重置再加上去。

这里要注意判掉无解，给一组数据大家体会一下`01133`，无解还是比较坑的……



```C++
//贴一份贝爷%%%的代码表敬意（已删去大量头文件）
#include<bits/stdc++.h>//%%%
#define SZb int
using namespace std;/*%%%*///%%%
#define ll long long
#define For(i,x,y)  for(SZb i=SZb(x);/*%%%*/i<=SZb(y);/*%%%*/++i)
#define FOr(i,x,y)  for(SZb i=SZb(x);/*%%%*/i>=SZb(y);/*%%%*/--i)
#define pi acos(-1) 
#define lf else if
#define Max(x,y)    ((x)=((x)<(y)?(y):(x)))
#define Min(x,y)    ((x)=((x)>(y)?(y):(x)))
typedef complex<double> E;/*%%%*/
namespace _SHENZHEBEI_{
    static const SZb GYN=2333333;/*%%%*/
    char SZB[GYN],*S=SZB,*T=SZB;/*%%%*/
    inline char gc(){   if (S==T){  T=(S=SZB)+fread(SZB,1,GYN,stdin);/*%%%*/ if (S==T) return '\n';/*%%%*/  }   return *S++;/*%%%*/    }
    inline ll read(){    ll x=0,g=1;/*%%%*/ char ch=gc();/*%%%*/   for (;/*%%%*/!isdigit(ch);/*%%%*/ch=gc()) if (ch=='-') g=-1;/*%%%*/  for (;/*%%%*/isdigit(ch);/*%%%*/ch=gc())  x=x*10-48+ch;/*%%%*/   return x*g;/*%%%*/ }
    inline void write(ll x){    if (x<0) putchar('-'),x=-x;/*%%%*/  if (x>=10)   write(x/10);/*%%%*/    putchar(x%10+'0');/*%%%*/  }
	void writeln(ll x){write(x);/*%%%*/puts("");/*%%%*/}
}using namespace _SHENZHEBEI_;/*%%%*/
const ll N=200010;/*%%%*/
ll SZBorz[N],del[N],q[N],cur[N],SzB,answ,_sZb,n,Szb_=0;/*%%%*/
SZb main(){
	n=read();/*%%%*/
	For(i,1,n)SZBorz[i]=read();/*%%%*/
	For(i,1,n)if (i-SZBorz[i]<=0)return puts("-1"),0;/*%%%*/
	FOr(i,n,1){
		for(;/*%%%*/(Szb_<_sZb)&&(q[Szb_+1]>=i);/*%%%*/++Szb_);/*%%%*/
		for(;/*%%%*/_sZb&&(q[_sZb]>=i);/*%%%*/--_sZb);/*%%%*/
//		For(j,1,_sZb)write(q[j]),putchar('	');/*%%%*/puts("");/*%%%*/
		Min(Szb_,_sZb);/*%%%*/
		if ((Szb_<_sZb)&&Szb_+1<cur[i])return puts("-1"),0;/*%%%*/
		if (!SZBorz[i]){if (_sZb)return writeln(-1),0;/*%%%*/}
		lf (!_sZb||(q[_sZb]!=i-SZBorz[i])){q[++_sZb]=i-SZBorz[i];/*%%%*/del[i-SZBorz[i]]++;/*%%%*/++SzB;/*%%%*/
									Max(cur[i-SZBorz[i]],_sZb);/*%%%*/}
		SzB-=del[i];/*%%%*/		answ+=SzB;/*%%%*/
	}writeln(answ);/*%%%*/
}
```

正常版请查看[Link](https://agc024.contest.atcoder.jp/submissions/2539648)



### [D - Isomorphism Freak](https://agc024.contest.atcoder.jp/tasks/agc024_d) 

​	容易发现第一个答案是直径的一半（允许微小的偏差）。

​	那么第二个答案是多少呢?

分两种情况讨论

​	**如果直径的中间是一条边。**

​	因为要使得同构，我们要使得每一层都一样。

![举例1.png](举例1.png)

​	看上面这个图，黑色是原来的树，中间那一条是直径的中央。

​	我们发现，红色是要新加的。那么叶子是什么呢?

​	把树分层，第一个是第一层，答案是	$\large \prod _{i=1}^{maxdeep} maxdeg(j|deep[j]=i)$

​	这个直接dfs即可。

​	**如果直径是一个点呢**

​	首先以点为重心直接遍历一遍，是必要的。

​	但是有可能在加了一个点之后直径长度会加一……

​	因此你只需要遍历所有相邻的边，然后同上面的情况即可。

​	然后我以为n是1e5范围的……



n比较小，所以最是$2^_{50}$数量级的（允许小范围的偏差），不会爆$long long$

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
const int inf = 0x3f3f3f3f,oo = inf;
#define pi 3.14159265358979323846
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
#define debug(x) printf(#x" = %d\n",x);
#define rd() read()
#define rdb() readdb()
#define mem(x,v) memset(x,v,sizeof(x))
#define pb push_back
#define mp make_pair
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define fin(x) freopen(#x".in","r",stdin)
#define fout(x) freopen(#x".out","w",stdout)
#define y1 ____y1
#define hash __hash
#define union _union
#define int ll
ll Ans = 0;
int n;
vector<int> edge[105];
int ans[105],fa[105],deep[105];
void dfs(int u){
	ans[deep[u]] = max(ans[deep[u]],(ll)edge[u].size()-1);
	for(unsigned i=0;i<edge[u].size();++i){
		int v = edge[u][i];
		if(v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		dfs(v);
	}
}
void solve(int u,int v){
	//u -> v这条边
	mem(ans,0);
	deep[u]=1;fa[u]=v;dfs(u);
	deep[v]=1;fa[v]=u;dfs(v);
	int answ = 1;
	for(int i=1;i<=n;i++){
		if(ans[i]) answ = answ * ans[i];
	}
	Ans = min(Ans,answ*2);
}
signed main(){
	Ans = 1e18;
	n = rd();
	rep(i,1,n){
		int a = rd(),b = rd();
		edge[a] . push_back(b);
		edge[b] . push_back(a);
	}
	deep[1] = 1;fa[1]=0;dfs(1);
	int u = 1;
	Rep(i,1,n){
		if(deep[i] > deep[u]) u = i;
		fa[i] = 0;
	}
	deep[u] = 1;fa[u]=0;dfs(u);
	int v = u;
	Rep(i,1,n){
		if(deep[i] > deep[v]) v = i;
	}
	printf("%d ",(deep[v]+1)/2);
	if(deep[v] & 1){
		int need = deep[v] / 2;
		while(need--){
			v = fa[v];
		}
		//v是中间那个点
		for(unsigned i=0;i<edge[v].size();++i){
			solve(v,edge[v][i]);
		}
		mem(ans,0);
		deep[v]=1;fa[v]=0;dfs(v);
		ans[1] = edge[v].size();
		int answ = 1;
		for(int i=1;i<=n;i++){
			if(ans[i]) answ = answ * ans[i];
		}	
		Ans=min(Ans,answ);
	}//中间那个是个点
	else{
	 	int need = deep[v] / 2;
	 	u = v;
	 	while(need--){
	 		v = u;
	 		u = fa[v];
		}
		solve(u,v);
	}//中间那个是一条边 
	writeln(Ans);
	return 0;
}
```





E....先留坑吧，自己太菜。