---
title: HDU4372&&codeforces960G
tags:
 - HDU
 - codeforces
 - FFT
 - DP
---

#### 题面

> n幢楼高度分别为1到n，问有多少个排列，从左往右看有x幢楼，从右往左看有y幢楼。

​	[cf960G](http://codeforces.com/problemset/problem/960/G)(T=1,n<=100000)

​	本题类似于[HDU4372](http://acm.hdu.edu.cn/showproblem.php?pid=4372)(T<=100000; n<=2000)

<!--more-->

#### Solution

考虑枚举最大的数出现的位置。

然后容易得到左边和右边分别处理（只有一边）

令$f[i][j]$表示前i个数字中当前答案为j的有多少种情况。

容易得到$f[i][j] = f[i-1][j-1] + f[i-1][j]*(i-1)$

观察发现这是无符号第一类斯特林数。

因此问题转化为
$$
\sum ^{n-B}_{i=A} \Large S(i-1,A-1)\Large \times \binom{n-1}{i-1} \times \binom{n-i}{B-1}
$$
其中S是斯特林数，然后一列是求不来的，考虑化简。

我们发现上面式子的含义相当于是在n-1个元素中取出若干的圆排列，再在这若干个排列中取出A-1个放在左边。

----

其实考虑组合意义也一样。

我们把左边的每一个最高的提出来，然后和它的最靠近的右边的看作一个环，右边同理。

那么问题变成在$n-1$个元素中选出$A+B-2$个圆，然后这些圆可以任意排列

如图，下面的黑色是最高的，红色是选中的一些，绿色是要求的。![如图](无标题.png)

综上所述

$$\Huge Ans = S(n-1,A+B-2) \times \binom{A+B-2}{A-1}$$

----

然后HDU那题就可以直接做了，以下核心代码（不能用bits差评）

```c++
const int Mod = 1e9+7;
int s[2005][2005],c[2005][2005];
void init(){
	static int n = 2000;
	s[0][0] = 1;
	c[0][0] = 1;
	Rep(i,1,n){
		s[i][0] = 0;
		c[i][0] = 1;
		Rep(j,1,i){
			s[i][j] = (s[i-1][j-1] + (ll)s[i-1][j] * (i-1))%Mod;
			c[i][j] = (c[i-1][j-1] + c[i-1][j])%Mod;
		}
	}
}
int main(){
	init();
	int T = rd();
	while(T--){
		int n,A,B;
		n = rd(),A =rd(),B = rd();
		if(A+B-2>n){//注意特判
			puts("0");
		} else{
			writeln(1ll*s[n-1][A+B-2]*c[A+B-2][A-1]%Mod);
		}
	}
	return 0;
}
```



---

然后CF这题n比较大。

所以似乎只能分治FFT(或者倍增FFT)来做。

**第一类斯特林数性质**：$\large x^{n↑} = \sum_{i=0}^{n} s_{n,i} \times x^i$

考虑展开：$x\times (x+1)\times (x+2)\times (x+3)$……

这个显然可以分治FFT。

先处理左边和右边，然后FFT合并。

时间复杂度$T(n) = T(\frac{n}{2})\times 2 + O(n log_2n) = O(n log^2_2n)$

```c++
//神仙Wzp已经Ak了IOI2018
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
const int inf = 0x3f3f3f3f,oo = inf;
#define RG register
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define Rep(i,a,b) for(RG int i=(a);i<=(b);++i)
#define Dep(i,a,b) for(RG int i=(a);i>=(b);--i)
#define pc putchar
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
inline void write(ll x){if(x<0)x=-x,pc('-');if(x>=10)write(x/10);pc(x%10+'0');}
inline void writeln(ll x){write(x);puts("");}
#define debug(x) printf(#x" = %d\n",x);
#define rd read
#define mem(x,v) memset(x,v,sizeof(x))
#define pb push_back
#define mp make_pair
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define fin(x) freopen(#x".in","r",stdin)
#define fout(x) freopen(#x".in","w",stdout)
#define y1 ____y1
#define hash __hash
#define union _union
const int maxn = 2662145;
const int Mod = 998244353;
const int g = 3;
int n,A,B;
int fac[maxn],inv[maxn];
int rev[maxn];
int ppow(int a,int b){
	int ans = 1;
	for(;b;b>>=1,a=1ll*a*a%Mod)
		if(b&1) ans=1ll*ans*a%Mod;
	return ans;
}
#define Pow ppow
void NTT(int a[],int nn,int flag){
	int n = 0,logn=0;
	for(n=1;n<nn;n<<=1) logn++;
	rep(i,0,n) rev[i] = (rev[i>>1] >> 1) | ((i&1) << (logn-1));
	rep(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
	
	for(int i=1;i<n;i<<=1){
		int wn = ppow(g,(Mod-1) / (i << 1)),x,y;
		if(flag==-1) wn=ppow(wn,Mod-2);
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0,w=1;k<i;++k,w=1ll*w*wn%Mod){
				x = a[j+k],y = 1ll * w * a[i+j+k] % Mod;
				a[j+k]=(x+y)%Mod;a[j+k+i]=(x-y+Mod)%Mod;
			}
	}
	if(flag==-1){
		int invn = ppow(n,Mod-2);
		rep(i,0,n) a[i] = 1ll*a[i]*invn%Mod;
	}
}

void init(){
	fac[0] = 1;
	Rep(i,1,n) fac[i] = 1ll*fac[i-1] * i % Mod;
	inv[n] = ppow(fac[n],Mod-2);
	Dep(i,n-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%Mod;
}
int C(int n,int m){
	return 1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int x[maxn],y[maxn];
void solve(int A[],int l,int r){
	if(l+2==r) return ;
	int mid = (l+r) >> 1;
	solve(A,l,mid);solve(A,mid,r);
	rep(i,l,mid) x[i-l] = A[i],x[i+mid-l-l] = 0;
	rep(i,mid,r) y[i-mid] = A[i],y[i-l] = 0;
	NTT(x,r-l,1),NTT(y,r-l,1);
	rep(i,0,r-l) x[i]=1ll*x[i]*y[i]%Mod;
	NTT(x,r-l,-1);
	rep(i,l,r) A[i]=x[i-l];
}
void Stirling(int A[],int n){
	rep(i,0,131072) A[i<<1]=1,A[i<<1|1]=0; 
	rep(i,0,n) A[i<<1]=i,A[i<<1|1]=1;
	int e=1;for(;e<2*n;e<<=1);
	solve(A,0,e);
}
int Stir[maxn];
int main(){
	n = rd(),A =rd(),B = rd();
	if(n==1){
		if(A==1&&B==1) puts("1"); else puts("0");
		return 0;
	}
	if(!A||!B||A+B-2>n){
		puts("0");
		return 0;
	}
	init();
	Stirling(Stir,n-1);
	writeln(1ll*Stir[A+B-2]*C(A+B-2,A-1)%Mod);
	return 0;
}
```

跑了$2137ms$

----

还有倍增FFT的做法$O(n log n)$。

$\Large x^{2n↑} = x^{n↑} \times (x+n)^{n↑} $

后者可以由前者得到。

假设前者的系数为($a0,a1,a2,a3,a4……an$)，当然a0=0

容易知道

$b = a_0(x+n)^0 + a_1(x+n)^1 + a_2(x+n)^2 +a_3(x+n)^3 + a_4(x+n)^4 ...a_n(x+n)^n$

考虑用二项式展开

$a_0 + n^1\times a_1\times C(1,0) + n^2\times a_2\times C(2,0) + ……$
 	 $n^0\times a_1\times C(1,1) + n^1\times a_2\times C(2,1) + ……$

​					$ + n^0*a_2\times C(2,2) + ……$

​						$……$

所以可以得到

$\Large b_i =\sum _{j=i} ^{n} a_j \times n^{j-i}\times C(j,i)$

$\Large i!b_i =\sum _{j=i} ^{n} a_j \times n^{j-i}\times \frac{j!}{(j-i)!}$

令$\Large x_i = a_i \times i!,y_i = \frac{n^{i}}{i!}$ 

注意到此时

$$
i! b_i =\sum _{j=i}^{n} x_j\times y_{j-i} \\
{(n-i)!}b_{n-i} = \sum _{j=0}^{i} x_{n-j}y_{j-i}
$$
因此我们可以翻转多项式x，乘好之后再翻转答案多项式，然后乘上相应的系数的逆元。

常数非常不优秀(311ms)，WZP的常数是我的三分之一左右，怒拿运行时间rank1（杜教第二）。
```c++
//神仙Wzp已经Ak了IOI2018
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
const int inf = 0x3f3f3f3f,oo = inf;
#define RG register
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define Rep(i,a,b) for(RG int i=(a);i<=(b);++i)
#define Dep(i,a,b) for(RG int i=(a);i>=(b);--i)
#define pc putchar
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
inline void write(ll x){if(x<0)x=-x,pc('-');if(x>=10)write(x/10);pc(x%10+'0');}
inline void writeln(ll x){write(x);puts("");}
#define debug(x) printf(#x" = %d\n",x);
#define rd read
#define mem(x,v) memset(x,v,sizeof(x))
#define pb push_back
#define mp make_pair
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define fin(x) freopen(#x".in","r",stdin)
#define fout(x) freopen(#x".in","w",stdout)
#define y1 ____y1
#define hash __hash
#define union _union
const int maxn = 2662145;
const int Mod = 998244353;
const int g = 3;
int n,A,B;
int fac[maxn],inv[maxn];
int rev[maxn];
inline int ppow(int a,int b){
	int ans = 1;
	for(;b;b>>=1,a=1ll*a*a%Mod)
		if(b&1) ans=1ll*ans*a%Mod;
	return ans;
}

inline void NTT(int a[],int nn,int flag){
	RG int n = 0,logn=0;
	for(n=1;n<nn;n<<=1) logn++;
	rep(i,0,n) rev[i] = (rev[i>>1] >> 1) | ((i&1) << (logn-1));
	rep(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);

	for(RG int i=1;i<n;i<<=1){
		RG int wn = ppow(g,(Mod-1) / (i << 1)),x,y;
		for(RG int j=0;j<n;j+=(i<<1))
			for(RG int k=0,w=1;k<i;++k,w=1ll*w*wn%Mod){
				x = a[j+k],y = 1ll * w * a[i+j+k] % Mod;
				a[j+k]=(x+y)%Mod;
				a[i+j+k]=(x-y+Mod)%Mod;
			}
	}
	if(flag==-1){
		reverse(a+1,a+n);
		int invn = ppow(n,Mod-2);
		rep(i,0,n) a[i] = 1ll*a[i]*invn%Mod;
	}
}

inline void init(){
	fac[0] = 1;
	Rep(i,1,n) fac[i] = 1ll*fac[i-1] * i % Mod;
	inv[n] = ppow(fac[n],Mod-2);
	Dep(i,n-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%Mod;
}
inline int C(int n,int m){
	return 1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int x[maxn],y[maxn],z[maxn],Pow[maxn];
inline void mul(int x[],int y[],int n){
	int w = 1;
	for(w=1;w<n+n;w<<=1);
	NTT(x,w,1),NTT(y,w,1);
	rep(i,0,w) x[i] = 1ll * x[i] * y[i] % Mod;
	NTT(x,w,-1);
}
inline void solve(int A[],int n){
	if(n==1){
		A[1] = 1;
		return ;
	}
	if(n&1){
		solve(A,n-1);
		Dep(i,n,1) A[i] = (A[i-1] + 1ll * (n-1) * A[i]) % Mod;
		return ;
	}
	solve(A,n/2);
	Pow[0] = 1;rep(i,1,n/2+1) Pow[i] = 1ll * Pow[i-1] * (n/2) % Mod;
	rep(i,0,n/2+1) x[i] = 1ll * A[i] * fac[i] % Mod,
			       y[i] = 1ll * Pow[i] * inv[i] % Mod;
	reverse(x,x+n/2+1);
	mul(x,y,n/2+1);
	reverse(x,x+n/2+1);
	rep(i,0,n/2+1){
		z[i] = 1ll * x[i] * inv[i] % Mod;
		z[i+n/2+1] = 0;//没有清0被续了好久
	}
	mul(A,z,n/2+1);

}
inline void Stirling(int A[],int n){
	solve(A,n);
}
int Stir[maxn];
int main(){
	n = rd(),A =rd(),B = rd();
	if(n==1){
		if(A==1&&B==1) puts("1"); else puts("0");
		return 0;
	}
	if(!A||!B||A+B-2>n){
		puts("0");
		return 0;
	}
	init();
	Stirling(Stir,n-1);
	writeln(1ll*Stir[A+B-2]*C(A+B-2,A-1)%Mod);
	return 0;
}

```

