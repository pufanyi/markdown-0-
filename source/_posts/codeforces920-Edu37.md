---
title: codeforces920-Edu37
tags:
 - codeforces
---

[Educational Codeforces Round 37 (Rated for Div. 2)](http://codeforces.com/contest/920)

B题题意杀。

E题就是BZOJ1098，F题大概类似于BZOJ3211

<!--more-->

#### A. Water The Garden

​	得到左边和右边哪边浇水，再判断一下

#### B. Tea Queue

​	模拟，细节见代码。

```c++
int l[1005],r[1005];
int ans[1005];
int n,q[1005],front,rear;
void solve(){
	front=rear=0;
	n = read();
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
	}
	mem(ans,0);
	for(int Time=1,j=1;Time<=5000;Time++){
		while(j<=n&&l[j]==Time) q[rear++] = j,j++;
		if(front<rear) ans[q[front++]] = Time; //先判断！
		while(front<rear && r[q[front]] <= Time) front++;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	puts("");
}
int main(){
	int T = read();
	while(T--) solve();
	return 0;
}

```

#### C. Swap Adjacent Elements

​	类似A题目，得到每个数字最左到多少，最右到多少，判断是否可以回到应该的额位置。

```c++
#define N 200050
#define M -1
int L[N],R[N],a[N],n,f[N];
int main(){
	n = read();
	for (int i=1;i<=n;i++) a[i] = read();
	for(int i=1;i<=n;i++) L[a[i]]=R[a[i]]=i;
	for(int i=1;i<=n-1;i++){
		int x;
		x=gc();
		while(x!='1'&&x!='0')x=gc();
		if(x=='1') f[i]=true;
	}
	L[1] = 1;
	for(int i=1;i<=n-1;i++){
		if(f[i])
			L[a[i+1]] = L[a[i]];
		else
			L[a[i+1]] = i+1;
	}
	R[n] = n;
	for(int i=n-1;i>=1;i--){
		if(f[i])
			R[a[i]] = R[a[i+1]];
		else
			R[a[i]] = i;
	}
	bool flag = true;
	for(int i=1;i<=n;i++)
		if(!(L[i]<=i&&i<=R[i])) flag = false;
	if(flag)
		puts("YES"); else
		puts("NO");
	return 0;
}
```

#### D. Tanks

​	一个类似贪心的做法

​	答案可行，也就是可以找出一些$a[i]$，使得 它们和对k取模与V对k取模的值是相等的，并且$\sum a[i]$ >= V

​	这样我们可以用背包来（因为每一个数最多只能用一次）

​	同时计算出是哪些加起来，讨论一下一些空的情况即可。

```c++
//代码改自D题第一个提交
#define N 5005
int a[N],n,k,v,dp[N][N],pre[N][N];
int main(){
	n = read() ,k = read(),v = read();
	rep(i,1,n+1) a[i]=read();
	int sum = 0;
	rep(i,1,n+1)sum+=a[i];
	if(sum<v){
		puts("NO");
		return 0;
	}
	dp[0][0]=true;
	rep(i,1,n+1){
		int x = a[i]%k;
		rep(j,0,k){
			if(!dp[i-1][j]) continue;
			dp[i][j]=true;
			pre[i][j] = false;
			
			dp[i][(j+x)%k] = true;
			pre[i][(j+x)%k] = true;
		}
	}
	if(!dp[n][v%k]){
		puts("NO");
		return 0;
	}
	vector<int> V[2];
	int _v = v%k;
	for(int i=n;i>=1;i--){
		int x=a[i]%k;
		if(pre[i][_v]){
			V[1].pb(i);
			_v = (_v - x + k) % k;
		} else
			V[0].pb(i);
	}
	sort(V[0].begin(),V[0].end());
	sort(V[1].begin(),V[1].end());
	puts("YES");
	if(!V[0].empty())
		for(int i=1;i<V[0].size();i++)
			printf("%d %d %d\n",100000,V[0][i],V[0][0]);
	if(!V[1].empty())
		for(int i=1;i<V[1].size();i++)
			printf("%d %d %d\n",100000,V[1][i],V[1][0]);
	sum = 0;
	for(int i=0;i<V[1].size();i++) sum+=a[V[1][i]];
	int p0,p1;
	if(V[0].empty()) p0 = V[1][1],p1 = V[1][0]; else
	if(V[1].empty()) p0 = V[0][0],p1 = V[0][1]; else
					 p0 = V[0][0],p1 = V[1][0];
	if(sum > v)
		if((sum-v)/k)printf("%d %d %d\n",(sum-v)/k,p1,p0);
	if(sum < v)
		if((v-sum)/k)printf("%d %d %d\n",(v-sum)/k,p0,p1);
	return 0;
}
```

#### E. Connected Components?

​	详见http://www.lydsy.com/JudgeOnline/problem.php?id=1098

#### F. SUM and REPLACE

​	注意到这个D(i)没有几下就会变成2或者1的。

​	所以直接暴力对不是2和1的进行求值，用树状数组得到区间和，用一个并查集来维护链表。

```c++
#define N 300099
#define M 300099
ll _D[1000009];
ll D(int x){
	if(_D[x]!=-1) return _D[x];
	_D[x] = 0;
	for(int i=1;i*i<=x;i++){
		if(x%i) continue;
		if(i*i==x) _D[x]++; else _D[x]+=2;
	}
	return _D[x];
}
ll n,m,a[N];
ll fa[N];
ll c[N];

ll find(ll x){
	return (x==fa[x])?x:fa[x]=find(fa[x]);
}

void add(ll x,ll v){
	for(;x<=n;x+=(x&-x))c[x]+=v;
}

ll get(ll x){
	ll ans = 0;
	for(;x;x-=(x&-x))ans+=c[x];
	return ans;
}

int main(){
	mem(_D,-1);
	n = read(),m = read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n+1;i++) if(a[i]==1||a[i]==2) fa[i]=i+1; else fa[i] = i;
	mem(c,0);
	for(int i=1;i<=n;i++)add(i,a[i]);
	while(m--){
		int t = read(),l = read(),r = read();
		if(t==1){
			int i = fa[l];
			while(i<=r){
				add(i,D(a[i])-a[i]);
				a[i] = D(a[i]);
				if(a[i] == 2 || a[i] == 1) fa[i] = i+1;
				i = find(i+1);
			}
		} else{
			printf("%I64d\n",get(r) - get(l-1));
		}
	}
	return 0;
}

```

#### G. List Of Integers

​	先知道一个简单的问题，已知n,m求1~n中与m互质的数有多少。

​	我们可以把n分解质因数然后容斥。

​	注意到$2*3*5*7*11*13*17*19$已经大于1e6了。

​	计算的复杂度是$O(sqrt(n))$预处理 + $O(256)$计算

​	对于每一个询问，我们考虑二分一个答案，注意到奇数和偶数互质，所以二分的区间是$[x+1,1e7]$

​	然后我们计算是否可行，再相应调整，

```c++
int f[233],num;
ll calc(ll n){
	ll ans = 0;
	for(int i=0;i<(1<<num);i++){
		int cnt = 0;
		ll t = 1;
		for(int j=0;j<num;j++){
			if((i>>j)&1){
				t = t * f[j];
				cnt++;
			}
		}
		if(cnt&1)
			ans -= n/t;
		else
			ans += n/t;
	}
	return ans;
}//求与n互质的数有多少 
void solve(){
	ll x = read(),p = read(),k = read();
	num = 0;
	ll i;
	for(i=2;i*i<=p;i++){
		if(p%i) continue;
		f[num++] = i;
		while(p%i==0) p/=i;
	} 
	if(p!=1) f[num++] = p;
	ll pre = calc(x);
	ll l = x+1,r = 1e9,ans=-1;
	while(l<=r){
		ll mid = (l+r)>>1;
		if(calc(mid) - pre >= k){
			ans = mid;
			r = mid - 1;
		} else
			l = mid + 1;
	}
	printf("%I64d\n",ans);
}
int main(){
	int T = read();
	while(T--) solve();
	return 0;
}
```

#### 后记

​	这场没人打呀。

