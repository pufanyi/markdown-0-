//强的人Wzp已经Ak了IOI2018
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctype.h>
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
const int Mod = 1e9+7;
const int maxn = 2005;
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
	//fin(),fout();
	init();
	int T = rd();
	while(T--){
		int n,A,B;
		n = rd(),A =rd(),B = rd();
		if(A+B-2>n){
			puts("0");
		} else{
			writeln(1ll*s[n-1][A+B-2]*c[A+B-2][A-1]%Mod);
		}
	}
	return 0;
}

