//Hello Wolrd
//There is Special Pig Jiong in the world.
#include<cstdio>
#include<cstring> 
#include<cstdlib> 
#include<cctype>
#include<algorithm>
#include<bitset> 
#include<vector> 
#include<set> 
#include<map> 
#include<ctime> 
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
#define pc putchar
#define RG register
char __wzp[1<<15|1],*__S=__wzp+32768;
#ifdef LOCAL 
	#define gc() getchar()
#else
	#define gc() (__S>=__wzp+32768?(__wzp[fread(__wzp,sizeof(char),1<<15,stdin)]=EOF),*((__S=__wzp)++):*(__S++))
#endif
inline ll read(){
	RG ll x=0,f=1;RG char c=gc();
	for(;!isdigit(c);c=gc())if(c=='-')f=-1;
	for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
const int oo = 0x3f3f3f3f,inf = oo;
#define mem(x,v) memset(x,v,sizeof(x))
#define pb push_back
#define mp make_pair
#define wait system("pause")
#define rep(i,a,b) for(RG int i=(a);i<(b);++i)
#define file(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define writeln(x) printf("%d\n",x);
#define N 505*2+233
#define M 100990 + N * 2 + 1
#define S 0
#define T n+n+1
struct Edge{
	int to,nxt,cap;
	Edge(){}
	Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
}edge[M*2];
int first[N],nume,cur[N];
void Addedge(int a,int b,int c){
	edge[nume] = Edge(b,first[a],c);first[a] = nume++;
	edge[nume] = Edge(a,first[b],0);first[b] = nume++;
}
int q[N],dis[N],n;
bool bfs(){
	int v,front,rear;mem(dis,-1);
	for(front=rear=0,dis[q[rear++]=T]=1;front<rear;)
		for (int u=q[front++],e=first[u];~e;e=edge[e].nxt)
			if(edge[e^1].cap && !~dis[v=edge[e].to])dis[q[rear++]=v]=dis[u]+1;
	return dis[S]!=-1;
}

int dfs(int u,int flow){
	if(u==T)return flow;
	int used = 0,d,v;
	for (int &e=cur[u];~e;e=edge[e].nxt){
		if(edge[e].cap && dis[v=edge[e].to]==dis[u]-1 && (d = dfs(v,min(flow-used,edge[e].cap))))
			edge[e].cap -= d,edge[e^1].cap += d,used += d;
		if(used == flow) break;
	}
	if(!used)dis[u]=-1;
	return used;
}

int dinic(){
	int ans = 0;
	for(;bfs();ans+=dfs(S,inf))
		rep(i,S,T+1) cur[i] = first[i];
	return ans;
}

int m,s;
int main(){
	int kase = read();
	while(kase--){
		mem(first,-1);nume = 0;
		n = read(),m = read(),s = read();
		while(m--){
			int a = read(),b = read(),c = read();
			Addedge(a+n,b,c);//ë´Ò»Ìõ±ß 
		}
		for (int i=1;i<=n;i++){
			int x = read();
			Addedge(S,i,x);
		}
		for (int i=1;i<=n;i++){
			int x = read();
			Addedge(i,n+i,x);
		}
		Addedge(s+n,T,inf);
		printf("%d\n",dinic());
	}
	return 0;
}
