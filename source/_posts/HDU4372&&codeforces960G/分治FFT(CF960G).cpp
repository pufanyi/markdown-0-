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

